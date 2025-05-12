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

#include <string.h>

#include "serial.h"
#include "usb/usb_descriptors.h"
#include "usb/usb_quantel.h"

#include "bsp/board_api.h"
#include "tusb.h"
#include "pico/bootrom.h"

hid_quantel_tablet_report_t tablet;
hid_quantel_rat_report_t rat;
hid_keyboard_report_t keyboard;

void hid_task(void);

/*------------- MAIN -------------*/
int main(void) {
    board_init();

    // init device stack on configured roothub port
    tud_init(BOARD_TUD_RHPORT);

    if (board_init_after_tusb) {
        board_init_after_tusb();
    }
    board_led_write(false);
    setup_uart();

#if SIMULATED_INPUT
    add_repeating_timer_ms(10, repeating_timer_callback, NULL, NULL);
#endif

    // ReSharper disable once CppDFAEndlessLoop
    while (1) {
        board_led_write(false);
        // Put the board into BOOTSEL mode when we press the button.
        if (board_button_read()) {
            reset_usb_boot(0, 0);
        }

        // send_packet_task();
        // board_led_write(true);
        tud_task();
        // hid_task();
    }
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void) {
}

// Invoked when device is unmounted
void tud_umount_cb(void) {
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(const bool remote_wakeup_en) {
}

// Invoked when usb bus is resumed
void tud_resume_cb(void) {
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

static void send_hid_report(const uint8_t report_id) {
    // skip if hid is not ready yet
    if (!tud_hid_ready()) {
        return;
    }

    switch (report_id) {
        case REPORT_ID_TABLET:
            tud_hid_report(REPORT_ID_TABLET, &tablet, sizeof(hid_quantel_tablet_report_t));
            break;

        case REPORT_ID_KEYBOARD:
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, keyboard.modifier, keyboard.keycode);
            break;

        case REPORT_ID_RAT:
            tud_hid_report(REPORT_ID_RAT, &rat, sizeof(hid_quantel_rat_report_t));
            break;

        default:
            break;
    }
}

// tud_hid_report_complete_cb() is used to send the next report after previous one is complete.
void hid_task(void) {
    if (!get_next_packet(&tablet, &rat, &keyboard)) {
        return;
    }
    // Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
    send_hid_report(REPORT_ID_KEYBOARD);
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(const uint8_t instance, uint8_t const* report, const uint16_t len) {
    (void) instance;
    (void) len;

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
    // TODO not Implemented
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
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) bufsize;
    //
    // if (report_type == HID_REPORT_TYPE_OUTPUT) {
    //     // Set keyboard LED e.g Capslock, Numlock etc...
    //     if (report_id == REPORT_ID_KEYBOARD) {
    //         // bufsize should be (at least) 1
    //         if (bufsize < 1) return;
    //
    //         uint8_t const kbd_leds = buffer[0];
    //
    //         if (kbd_leds & KEYBOARD_LED_CAPSLOCK) {
    //             // Capslock On: disable blink, turn led on
    //             blink_interval_ms = 0;
    //             board_led_write(true);
    //         } else {
    //             // Caplocks Off: back to normal blink
    //             board_led_write(false);
    //             blink_interval_ms = BLINK_MOUNTED;
    //         }
    //     }
    // }
}

// void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts) {
//     (void) itf;
//     (void) rts;
//
//     if (dtr) {
//         tud_cdc_write_str("Connected\n");
//     }
// }
