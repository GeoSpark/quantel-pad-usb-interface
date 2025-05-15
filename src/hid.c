/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2025 John Donovan (geospark.co.uk)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "serial.h"
#include "usb/usb_descriptors.h"
#include "usb/usb_quantel.h"

#include "bsp/board_api.h"
#include "tusb.h"

hid_quantel_tablet_report_t tablet;
hid_quantel_rat_report_t rat;
hid_keyboard_report_t keyboard;
send_mode_t _send_mode;


static void send_hid_report(const uint8_t report_id) {
    if (!tud_hid_ready()) {
        return;
    }

    switch (report_id) {
        case REPORT_ID_TABLET:
            tud_hid_report(REPORT_ID_TABLET, &tablet, sizeof(hid_quantel_tablet_report_t));
            break;

        case REPORT_ID_KEYBOARD:
            board_led_write(true);
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, keyboard.modifier, keyboard.keycode);
            break;

        case REPORT_ID_RAT:
            tud_hid_report(REPORT_ID_RAT, &rat, sizeof(hid_quantel_rat_report_t));
            break;

        default:
            break;
    }
}

void process_command(send_mode_t* send_mode) {
    *send_mode = _send_mode;
}

void send_to_hid(uint8_t* serial_buffer, uint8_t len) {
    for (uint8_t i = 0; i < len; i++) {
        if (parse_packet(serial_buffer[i], &tablet, &rat, &keyboard)) {
            // Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
            send_hid_report(REPORT_ID_KEYBOARD);
        }
    }
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(const uint8_t instance, uint8_t const* report, const uint16_t /*len*/) {
    const uint8_t next_report_id = report[0] + 1u;

    if (next_report_id < REPORT_ID_COUNT) {
        send_hid_report(next_report_id);
    }
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer,
                               uint16_t reqlen) {
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;

    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer,
                           uint16_t bufsize) {
    (void) instance;
    (void) bufsize;

    if (report_type == HID_REPORT_TYPE_OUTPUT && report_id == REPORT_ID_COMMAND) {
        if (buffer[0] == 0x00) {
            _send_mode = FROM_PAD;
        } else if (buffer[0] == 0x01) {
            _send_mode = FROM_USB;
        }
    }
}
