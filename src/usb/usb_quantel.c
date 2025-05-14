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
#include "../serial.h"
#include "usb_descriptors.h"
#include "bsp/board_api.h"
#include "class/hid/hid.h"

#define MAX_KEY_ROLLOVER 6

uint8_t modifier_keys = 0;
uint8_t key_rollover[MAX_KEY_ROLLOVER] = {
    HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE
};
status_t status;
pen_data_t pen_data;
uint8_t keycode;

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

bool parse_packet(uint8_t data, hid_quantel_tablet_report_t* tablet, hid_quantel_rat_report_t* rat,
                     hid_keyboard_report_t* keyboard) {

    if (!handle_packet(data, &status, &pen_data, &keycode)) {
        return false;
    }

    // Accounts for tip switch and tip proximity.
    tablet->flags = (pen_data.pressure > 0) | (status.has_pen_data << 1);
    tablet->x = (int16_t)(status.has_pen_data ? pen_data.x : 0);
    tablet->y = (int16_t)(status.has_pen_data ? pen_data.y : 0);
    tablet->tip_pressure = pen_data.pressure;

    // board_led_write(tablet->flags & 0x02);

    rat->button_1 = status.button_1;
    rat->button_2 = status.button_2;
    rat->button_3 = status.button_3;
    rat->button_4 = status.button_4;
    rat->button_5 = status.button_5;
    rat->x = (int8_t)(status.joystick_right - status.joystick_left);
    rat->y = (int8_t)(status.joystick_down - status.joystick_up);

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

    return true;
}
