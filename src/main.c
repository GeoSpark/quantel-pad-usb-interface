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
#include "hid.h"
#include "cdc.h"
#include "commands.h"
#include "flash_config.h"
#include "quantel.h"

#include "bsp/board_api.h"
#include "tusb.h"
#include "pico/bootrom.h"

typedef struct {
    keyboards_t keyboard;
} hw_config_t;


int main(void) {
    board_init();

    // init device stack on configured roothub port
    tusb_rhport_init_t dev_init = {
        .role = TUSB_ROLE_DEVICE,
        .speed = TUSB_SPEED_AUTO
      };

    tusb_init(BOARD_TUD_RHPORT, &dev_init);

    if (board_init_after_tusb) {
        board_init_after_tusb();
    }

    setup_uart();

    hw_config_t config = {.keyboard = KBD_AKE079339};

    if (!read_config(&config, sizeof(hw_config_t))) {
        write_config(&config, sizeof(hw_config_t));
    }

    set_keyboard(config.keyboard);

    uint8_t buffer[64];

    board_led_write(true);

    // ReSharper disable once CppDFAEndlessLoop
    while (1) {
        // Put the board into BOOTSEL mode when we press the button.
        if (board_button_read()) {
            reset_usb_boot(0, 0);
        }

        tud_task();
        const command_state_t state = get_command_state();
        uint8_t len = 0;

        if (state.send_mode == FROM_PAD) {
            board_led_write(true);
            len = read_from_pad(buffer, 64);
        } else {
            board_led_write(false);
            len = read_from_cdc(buffer, 64);
        }

        if (len > 0) {
            if (state.pb_output) {
                send_to_pb(buffer, len);
            }

            if (state.hid_output) {
                send_to_hid(buffer, len);
            }

            if (state.cdc_output) {
                send_to_cdc(buffer, len);
            }
        }
    }
}
