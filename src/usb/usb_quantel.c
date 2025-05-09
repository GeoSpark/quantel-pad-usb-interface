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

#include "../quantel/quantel.h"
#include "usb_descriptors.h"
#include "bsp/board_api.h"
#include "class/hid/hid.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"

#include <string.h>

#define SIMULATED_INPUT 1

#if SIMULATED_INPUT
#include "pico/time.h"
#include "test_data2.h"
#endif

#define MAX_KEY_ROLLOVER 6

uint8_t modifier_keys = 0;
uint8_t key_rollover[MAX_KEY_ROLLOVER] = {
    HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE
};
status_t status;
pen_data_t pen_data;
uint8_t keycode;

#if SIMULATED_INPUT
void get_simulated_packet() {
    bool valid = false;
    static size_t index = 0;

    while (!valid) {
        for (uint8_t i = 0; i < QUANTEL_PACKET_SIZE; i++) {
            valid = handle_packet(test_data[index][i], &status, &pen_data, &keycode);
        }

        index = (index + 1) % (sizeof(test_data) / QUANTEL_PACKET_SIZE);
    }

    sleep_ms(10);
}
#endif

void get_uart_packet() {
    bool valid = false;

    while (uart_is_readable(uart1) && !valid) {
        valid = handle_packet(uart_getc(uart1), &status, &pen_data, &keycode);
    }
}

void handle_key_state(const uint8_t keycode, const bool key_up) {
    const uint8_t usb_keycode = map_keycode(keycode);

    if (usb_keycode >= HID_KEY_CONTROL_LEFT && usb_keycode <= HID_KEY_GUI_RIGHT) {
        const uint8_t usb_modifier_key = usb_keycode - HID_KEY_CONTROL_LEFT;

        if (key_up) {
            modifier_keys &= ~(1 << usb_modifier_key);
        } else {
            modifier_keys |= 1 << usb_modifier_key;
        }

        return;
    }

    if (key_up) {
        for (uint8_t i = 0; i < MAX_KEY_ROLLOVER; i++) {
            if (key_rollover[i] == usb_keycode) {
                key_rollover[i] = HID_KEY_NONE;
                break;
            }
        }
    } else {
        for (uint8_t i = 0; i < MAX_KEY_ROLLOVER; i++) {
            if (key_rollover[i] == HID_KEY_NONE) {
                key_rollover[i] = usb_keycode;
                break;
            }
        }
    }
}

void get_next_packet(hid_quantel_tablet_report_t* tablet, hid_quantel_rat_report_t* rat,
                     hid_keyboard_report_t* keyboard) {
#if SIMULATED_INPUT
    get_simulated_packet();
#else
    get_uart_packet();
#endif

    // Accounts for tip switch and tip proximity.
    tablet->flags = (pen_data.pressure > 0) | (status.has_pen_data << 1);
    tablet->x = status.has_pen_data ? pen_data.x : 0;
    tablet->y = status.has_pen_data ? pen_data.y : 0;
    tablet->tip_pressure = pen_data.pressure;

    board_led_write(tablet->flags & 0x02);

    rat->button_1 = status.button_1;
    rat->button_2 = status.button_2;
    rat->button_3 = status.button_3;
    rat->button_4 = status.button_4;
    rat->button_5 = status.button_5;
    rat->x = status.joystick_right - status.joystick_left;
    rat->y = status.joystick_down - status.joystick_up;

    if (status.has_keycode) {
        handle_key_state(keycode, status.key_up);
    }

    keyboard->modifier = modifier_keys;
    keyboard->keycode[0] = key_rollover[0];
    keyboard->keycode[1] = key_rollover[1];
    keyboard->keycode[2] = key_rollover[2];
    keyboard->keycode[3] = key_rollover[3];
    keyboard->keycode[4] = key_rollover[4];
    keyboard->keycode[5] = key_rollover[5];
}
