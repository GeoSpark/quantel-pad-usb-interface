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

#include "cdc.h"
#include "serial.h"

#include "tusb.h"
#include "pico/bootrom.h"

// Write data coming in from the PAD to the USB serial interface.
void cdc_write_packet(uint8_t* packet, uint8_t len) {
    if (!tud_cdc_n_available(0)) {
        return;
    }

    tud_cdc_n_write(0, packet, len);
    tud_cdc_n_write_flush(0);
}

// Write data coming in from the USB serial interface to the Paintbox.
void cdc_task() {
    if (!tud_cdc_n_available(0)) {
        return;
    }

    uint8_t buf[64];

    const uint8_t count = tud_cdc_n_read(0, buf, sizeof(buf));
    send_to_pb(buf, count);
}

// Invoked when CDC line state changed e.g connected/disconnected
// Use to reset to DFU when disconnect with 1200 bps
void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool /*rts*/) {
    // DTR = false is counted as disconnected
    if (!dtr) {
        // touch1200 only with first CDC instance (Serial)
        if (itf == 0) {
            cdc_line_coding_t coding;
            tud_cdc_get_line_coding(&coding);
            if (coding.bit_rate == 1200) {
                reset_usb_boot(0, 0);
            }
        }
    }
}
