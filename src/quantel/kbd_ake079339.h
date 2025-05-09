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

#ifndef KBD_AKE079339
#define KBD_AKE079339

#include "class/hid/hid.h"

// Keycode mapping for the Access Keyboards Ltd AKE079339/3 keyboard

enum KEYCODE_AKE079339 {
    AKE079339_KEY_DOWN = 0x00,
    AKE079339_KEY_ESCAPE = 0x01,
    AKE079339_KEY_1 = 0x02,
    AKE079339_KEY_2 = 0x03,
    AKE079339_KEY_3 = 0x04,
    AKE079339_KEY_4 = 0x05,
    AKE079339_KEY_5 = 0x06,
    AKE079339_KEY_6 = 0x07,
    AKE079339_KEY_7 = 0x08,
    AKE079339_KEY_8 = 0x09,
    AKE079339_KEY_9 = 0x0A,
    AKE079339_KEY_0 = 0x0B,
    AKE079339_KEY_MINUS = 0x0C,
    AKE079339_KEY_EQUALS = 0x0D,
    AKE079339_KEY_DELETE = 0x0E,
    AKE079339_KEY_TAB = 0x0F,
    AKE079339_KEY_Q = 0x10,
    AKE079339_KEY_W = 0x11,
    AKE079339_KEY_E = 0x12,
    AKE079339_KEY_R = 0x13,
    AKE079339_KEY_T = 0x14,
    AKE079339_KEY_Y = 0x15,
    AKE079339_KEY_U = 0x16,
    AKE079339_KEY_I = 0x17,
    AKE079339_KEY_O = 0x18,
    AKE079339_KEY_P = 0x19,
    AKE079339_KEY_BRACKET_LEFT = 0x1A,
    AKE079339_KEY_BRACKET_RIGHT = 0x1B,
    AKE079339_KEY_CONTROL = 0x1D,
    AKE079339_KEY_A = 0x1E,
    AKE079339_KEY_S = 0x1F,
    AKE079339_KEY_D = 0x20,
    AKE079339_KEY_F = 0x21,
    AKE079339_KEY_G = 0x22,
    AKE079339_KEY_H = 0x23,
    AKE079339_KEY_J = 0x24,
    AKE079339_KEY_K = 0x25,
    AKE079339_KEY_L = 0x26,
    AKE079339_KEY_SEMICOLON = 0x27,
    AKE079339_KEY_APOSTROPHE = 0x28,
    AKE079339_KEY_SHIFT_LEFT = 0x2A,
    AKE079339_KEY_NUMBER_SIGN = 0x2B,
    AKE079339_KEY_Z = 0x2C,
    AKE079339_KEY_BLANK = 0x2D,
    AKE079339_KEY_C = 0x2E,
    AKE079339_KEY_V = 0x2F,
    AKE079339_KEY_B = 0x30,
    AKE079339_KEY_N = 0x31,
    AKE079339_KEY_M = 0x32,
    AKE079339_KEY_COMMA = 0x33,
    AKE079339_KEY_PERIOD = 0x34,
    AKE079339_KEY_SLASH = 0x35,
    AKE079339_KEY_SHIFT_RIGHT = 0x36,
    AKE079339_KEY_ALT = 0x38,
    AKE079339_KEY_SPACE = 0x39,
    AKE079339_KEY_CAPSLOCK = 0x3A,
    AKE079339_KEY_X = 0x55,
    AKE079339_KEY_BACKSLASH = 0x56,
    AKE079339_KEY_DO = 0x60,
    AKE079339_KEY_CONT = 0x61,
    AKE079339_KEY_REC = 0x62,
    AKE079339_KEY_INS = 0x63,
    AKE079339_KEY_HELP = 0x64,
    AKE079339_KEY_M1 = 0x65,
    AKE079339_KEY_M2 = 0x66,
    AKE079339_KEY_M3 = 0x67,
    AKE079339_KEY_M4 = 0x68,
    AKE079339_KEY_M5 = 0x69,
    AKE079339_KEY_M6 = 0x6A,
    AKE079339_KEY_M7 = 0x6B,
    AKE079339_KEY_M8 = 0x6C,
    AKE079339_KEY_M9 = 0x6D,
    AKE079339_KEY_M10 = 0x6E,
    AKE079339_KEY_GRAVE = 0x70,
    AKE079339_KEY_RETURN = 0x71,
    AKE079339_KEY_SEL = 0x75,
    AKE079339_KEY_UP = 0x76,
    AKE079339_KEY_LEFT = 0x77,
    AKE079339_KEY_RIGHT = 0x78
};


#define KEY_UNDEFINED (0x03 | 0xF000)

// Maps AKE079339 keycodes to their USB HID equivalent, or as close as seems to make sense.
// See page 53 of https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf for details.
// Note: Not all values map to keys, so "Keyboard ErrorUndefined" is used for keys that don't exist on the keyboard,
// so this array can be used as a simple 7-bit LUT.
const uint8_t USB_HID_MAPPING_AKE079339[] = {
    HID_KEY_ARROW_DOWN,     //     AKE079339_KEY_DOWN
    HID_KEY_ESCAPE,         //     AKE079339_KEY_ESCAPE
    HID_KEY_1,              //     AKE079339_KEY_1
    HID_KEY_2,              //     AKE079339_KEY_2
    HID_KEY_3,              //     AKE079339_KEY_3
    HID_KEY_4,              //     AKE079339_KEY_4
    HID_KEY_5,              //     AKE079339_KEY_5
    HID_KEY_6,              //     AKE079339_KEY_6
    HID_KEY_7,              //     AKE079339_KEY_7
    HID_KEY_8,              //     AKE079339_KEY_8
    HID_KEY_9,              //     AKE079339_KEY_9
    HID_KEY_0,              //     AKE079339_KEY_0
    HID_KEY_MINUS,          //     AKE079339_KEY_MINUS
    HID_KEY_EQUAL,          //     AKE079339_KEY_EQUALS
    HID_KEY_DELETE,         //     AKE079339_KEY_DELETE
    HID_KEY_TAB,            //     AKE079339_KEY_TAB
    HID_KEY_Q,              //     AKE079339_KEY_Q
    HID_KEY_W,              //     AKE079339_KEY_W
    HID_KEY_E,              //     AKE079339_KEY_E
    HID_KEY_R,              //     AKE079339_KEY_R
    HID_KEY_T,              //     AKE079339_KEY_T
    HID_KEY_Y,              //     AKE079339_KEY_Y
    HID_KEY_U,              //     AKE079339_KEY_U
    HID_KEY_I,              //     AKE079339_KEY_I
    HID_KEY_O,              //     AKE079339_KEY_O
    HID_KEY_P,              //     AKE079339_KEY_P
    HID_KEY_BRACKET_LEFT,   //     AKE079339_KEY_BRACKET_LEFT
    HID_KEY_BRACKET_RIGHT,  //     AKE079339_KEY_BRACKET_RIGHT
    HID_KEY_NONE,           //
    HID_KEY_CONTROL_LEFT,   //     AKE079339_KEY_CONTROL
    HID_KEY_A,              //     AKE079339_KEY_A
    HID_KEY_S,              //     AKE079339_KEY_S
    HID_KEY_D,              //     AKE079339_KEY_D
    HID_KEY_F,              //     AKE079339_KEY_F
    HID_KEY_G,              //     AKE079339_KEY_G
    HID_KEY_H,              //     AKE079339_KEY_H
    HID_KEY_J,              //     AKE079339_KEY_J
    HID_KEY_K,              //     AKE079339_KEY_K
    HID_KEY_L,              //     AKE079339_KEY_L
    HID_KEY_SEMICOLON,      //     AKE079339_KEY_SEMICOLON
    HID_KEY_APOSTROPHE,     //     AKE079339_KEY_APOSTROPHE
    HID_KEY_NONE,           //
    HID_KEY_SHIFT_LEFT,     //     AKE079339_KEY_SHIFT_LEFT
    HID_KEY_EUROPE_1,       //     AKE079339_KEY_NUMBER_SIGN
    HID_KEY_Z,              //     AKE079339_KEY_Z
    HID_KEY_GUI_RIGHT,      //     AKE079339_KEY_BLANK (USB HID "Keyboard Right GUI")
    HID_KEY_C,              //     AKE079339_KEY_C
    HID_KEY_V,              //     AKE079339_KEY_V
    HID_KEY_B,              //     AKE079339_KEY_B
    HID_KEY_N,              //     AKE079339_KEY_N
    HID_KEY_M,              //     AKE079339_KEY_M
    HID_KEY_COMMA,          //     AKE079339_KEY_COMMA
    HID_KEY_PERIOD,         //     AKE079339_KEY_PERIOD
    HID_KEY_SLASH,          //     AKE079339_KEY_SLASH
    HID_KEY_SHIFT_RIGHT,    //     AKE079339_KEY_SHIFT_RIGHT
    HID_KEY_NONE,           //
    HID_KEY_ALT_LEFT,       //     AKE079339_KEY_ALT
    HID_KEY_SPACE,          //     AKE079339_KEY_SPACE
    HID_KEY_CAPS_LOCK,      //     AKE079339_KEY_CAPSLOCK
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_X,              //     AKE079339_KEY_X
    HID_KEY_BACKSLASH,      //     AKE079339_KEY_BACKSLASH
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_EXECUTE,        //     AKE079339_KEY_DO   (USB HID "Keyboard Execute")
    HID_KEY_SCROLL_LOCK,    //     AKE079339_KEY_CONT (USB HID "Keyboard Scroll Lock")
    HID_KEY_PRINT_SCREEN,   //     AKE079339_KEY_REC  (USB HID "Keyboard PrintScreen")
    HID_KEY_INSERT,         //     AKE079339_KEY_INS
    HID_KEY_HELP,           //     AKE079339_KEY_HELP (USB HID "Keyboard Help")
    HID_KEY_F1,             //     AKE079339_KEY_M1
    HID_KEY_F2,             //     AKE079339_KEY_M2
    HID_KEY_F3,             //     AKE079339_KEY_M3
    HID_KEY_F4,             //     AKE079339_KEY_M4
    HID_KEY_F5,             //     AKE079339_KEY_M5
    HID_KEY_F6,             //     AKE079339_KEY_M6
    HID_KEY_F7,             //     AKE079339_KEY_M7
    HID_KEY_F8,             //     AKE079339_KEY_M8
    HID_KEY_F9,             //     AKE079339_KEY_M9
    HID_KEY_F10,            //     AKE079339_KEY_M10
    HID_KEY_NONE,           //
    HID_KEY_GRAVE,          //     AKE079339_KEY_GRAVE
    HID_KEY_ENTER,          //     AKE079339_KEY_RETURN
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_SELECT,         //     AKE079339_KEY_SEL  (USB HID "Keyboard Select")
    HID_KEY_ARROW_UP,       //     AKE079339_KEY_UP
    HID_KEY_ARROW_LEFT,     //     AKE079339_KEY_LEFT
    HID_KEY_ARROW_RIGHT,    //     AKE079339_KEY_RIGHT
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE,           //
    HID_KEY_NONE            //
};

#endif
