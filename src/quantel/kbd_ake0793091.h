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

#ifndef KBD_AKE0793091_H
#define KBD_AKE0793091_H

#include "class/hid/hid.h"

// Keycode mapping for the Access Keyboards Ltd AKE0793091 keyboard

enum KEYCODE_AKE0793091 {
    AKE0793091_KEY_LEFT = 0x08,
    AKE0793091_KEY_RIGHT = 0x09,
    AKE0793091_KEY_DOWN = 0x0A,
    AKE0793091_KEY_UP = 0x0B,
};


const uint8_t USB_HID_MAPPING_AKE0793091[] = {
    HID_KEY_NONE,
    HID_KEY_NONE,
    HID_KEY_NONE,
    HID_KEY_NONE,
    HID_KEY_NONE,
    HID_KEY_NONE,
    HID_KEY_NONE,
    HID_KEY_NONE,
    HID_KEY_ARROW_LEFT,      //     AKE0793091_KEY_LEFT
    HID_KEY_ARROW_RIGHT,     //     AKE0793091_KEY_RIGHT
    HID_KEY_ARROW_DOWN,      //     AKE0793091_KEY_DOWN
    HID_KEY_ARROW_UP,        //     AKE0793091_KEY_UP
};

#endif //KBD_AKE0793091_H
