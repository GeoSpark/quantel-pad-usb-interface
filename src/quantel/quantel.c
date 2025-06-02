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

#include "quantel.h"
#include "kbd_ake079339.h"
#include "kbd_ake0793091.h"

typedef enum {
    PACKET_STATE_STATUS,
    PACKET_STATE_BUTTONS,
    PACKET_STATE_KEY_CODE,
    PACKET_STATE_PEN_X_MSB,
    PACKET_STATE_PEN_X_LSB,
    PACKET_STATE_PEN_Y_MSB,
    PACKET_STATE_PEN_Y_LSB,
    PACKET_STATE_PEN_PRESSURE,
    PACKET_STATE_CHECKSUM,
    PACKET_STATE_IDLE = 255
} PACKET_STATE;

PACKET_STATE current_state = PACKET_STATE_IDLE;
uint8_t checksum;
keyboards_t current_keyboard = KBD_AKE079339;

void map_keycode(const uint8_t keycode, uint8_t* usb_key, uint8_t* usb_modifier) {
    if (current_keyboard == KBD_AKE079339) {
        const uint8_t key = USB_HID_MAPPING_AKE079339[keycode];

        if (key >= HID_KEY_CONTROL_LEFT && key <= HID_KEY_GUI_RIGHT) {
            *usb_modifier = key;
            *usb_key = HID_KEY_NONE;
        } else {
            *usb_modifier = HID_KEY_NONE;
            *usb_key = key;
        }
    } else if (current_keyboard == KBD_AKE0793091) {
        const combined_key_t keys = USB_HID_MAPPING_AKE0793091[keycode];
        *usb_modifier = keys.modifier_key;
        *usb_key = keys.keycode;
    }
}

void set_keyboard(keyboards_t keyboard) {
    current_keyboard = keyboard;
}

keyboards_t get_keyboard() {
    return current_keyboard;
}

// Set up a simple state machine. When the function returns true we have received a valid packet.
bool handle_packet(const uint8_t data, status_t* status, pen_data_t* pen_data, uint8_t* keycode) {
    // If the top bit is set, then we're starting a new packet.
    // This means if we start parsing part-way through a packet, we wait until we get a positive start.
    // If a new packet is started before the previous one was finished (such as an interruption to the serial line),
    // we drop the partial packet and start again in a known fresh state.
    if (data & 0x80) {
        current_state = PACKET_STATE_STATUS;
        checksum = 0;
        *keycode = 0;
        pen_data->x = 0;
        pen_data->y = 0;
        pen_data->pressure = 0;
        status->packet_start = 0;
        status->has_keycode = 0;
        status->has_pen_data = 0;
        status->unknown1 = 0;
        status->joystick_down = 0;
        status->joystick_up = 0;
        status->joystick_right = 0;
        status->joystick_left = 0;
        status->byte_marker = 0;
        status->button_5 = 0;
        status->unknown2 = 0;
        status->key_up = 0;
        status->button_4 = 0;
        status->button_3 = 0;
        status->button_2 = 0;
        status->button_1 = 0;
    }

    if (current_state == PACKET_STATE_IDLE) {
        return false;
    }

    switch (current_state) {
        case PACKET_STATE_STATUS:
            status->packet_start = (data & 0x80) >> 7;
            status->has_keycode = (data & 0x40) >> 6;
            status->has_pen_data = (data & 0x20) >> 5;
            status->unknown1 = (data & 0x10) >> 4;
            status->joystick_down = (data & 0x08) >> 3;
            status->joystick_up = (data & 0x04) >> 2;
            status->joystick_right = (data & 0x02) >> 1;
            status->joystick_left = (data & 0x01);
            current_state = PACKET_STATE_BUTTONS;
            break;

        case PACKET_STATE_BUTTONS:
            status->byte_marker = (data & 0x80) >> 7;
            status->button_5 = (data & 0x40) >> 6;
            status->unknown2 = (data & 0x20) >> 5;
            status->key_up = (data & 0x10) >> 4;
            status->button_4 = (data & 0x08) >> 3;
            status->button_3 = (data & 0x04) >> 2;
            status->button_2 = (data & 0x02) >> 1;
            status->button_1 = (data & 0x01);
            current_state = PACKET_STATE_KEY_CODE;
            break;

        case PACKET_STATE_KEY_CODE:
            if (status->has_keycode) {
                *keycode = data;
            } else {
                // Pen pressure MSb is stored in bit 6.
                pen_data->pressure = (data & 0x40) << 1;
            }
            current_state = PACKET_STATE_PEN_X_MSB;
            break;

        case PACKET_STATE_PEN_X_MSB:
            // Twiddle bits to extend the sign.
            // The pen position is a 14 bit signed quantity, so to get the correct sign, we need to do some magic
            // to extend the sign to the full 16 bits.
            pen_data->x = data << 7; // NOLINT(*-narrowing-conversions)
            if (data & 0x40) {
                pen_data->x |= (int16_t)0xc000;
            }
            current_state = PACKET_STATE_PEN_X_LSB;
            break;

        case PACKET_STATE_PEN_X_LSB:
            pen_data->x |= data; // NOLINT(*-narrowing-conversions)
            current_state = PACKET_STATE_PEN_Y_MSB;
            break;

        case PACKET_STATE_PEN_Y_MSB:
            // Twiddle bits to extend the sign.
            pen_data->y = data << 7; // NOLINT(*-narrowing-conversions)
            if (data & 0x40) {
                pen_data->y |= (int16_t)0xc000;
            }
            current_state = PACKET_STATE_PEN_Y_LSB;
            break;

        case PACKET_STATE_PEN_Y_LSB:
            pen_data->y |= data; // NOLINT(*-narrowing-conversions)
            current_state = PACKET_STATE_PEN_PRESSURE;
            break;

        case PACKET_STATE_PEN_PRESSURE:
            pen_data->pressure |= data; // NOLINT(*-narrowing-conversions)
            current_state = PACKET_STATE_CHECKSUM;
            break;

        case PACKET_STATE_CHECKSUM:
            current_state = PACKET_STATE_IDLE;

            if ((checksum & 0x7f) == data) {
                return true;
            }
            break;

        default:
            break;
    }

    checksum ^= data;

    return false;
}
