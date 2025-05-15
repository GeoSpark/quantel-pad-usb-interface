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

#include "commands.h"

#include <string.h>

// Must be equal to or less than CFG_TUD_HID_EP_BUFSIZE in length which is defined in usb/tusb_config.h
#define CMD_INPUT_PAD      "INPUT PAD"
#define CMD_INPUT_USB      "INPUT USB"
#define CMD_OUTPUT_PB_ON   "OUTPUT PB ON"
#define CMD_OUTPUT_PB_OFF  "OUTPUT PB OFF"
#define CMD_OUTPUT_HID_ON  "OUTPUT HID ON"
#define CMD_OUTPUT_HID_OFF "OUTPUT HID OFF"
#define CMD_OUTPUT_CDC_ON  "OUTPUT CDC ON"
#define CMD_OUTPUT_CDC_OFF "OUTPUT CDC OFF"

command_state_t command_state = {
    .send_mode = FROM_PAD,
    .pb_output = true,
    .hid_output = true,
    .cdc_output = true,
};

// Parse commands coming in from the HID IO interface. Commands are case insensitive.
void parse_command(uint8_t const* data, uint8_t len) {
    if (strncasecmp(CMD_INPUT_PAD, (char*)data, len) == 0) {
        command_state.send_mode = FROM_PAD;
    } else if (strncasecmp(CMD_INPUT_USB, (char*)data, len) == 0) {
        command_state.send_mode = FROM_USB;
    } else if (strncasecmp(CMD_OUTPUT_PB_ON, (char*)data, len) == 0) {
        command_state.pb_output = true;
    } else if (strncasecmp(CMD_OUTPUT_PB_OFF, (char*)data, len) == 0) {
        command_state.pb_output = false;
    } else if (strncasecmp(CMD_OUTPUT_HID_ON, (char*)data, len) == 0) {
        command_state.hid_output = true;
    } else if (strncasecmp(CMD_OUTPUT_HID_OFF, (char*)data, len) == 0) {
        command_state.hid_output = false;
    } else if (strncasecmp(CMD_OUTPUT_CDC_ON, (char*)data, len) == 0) {
        command_state.cdc_output = true;
    } else if (strncasecmp(CMD_OUTPUT_CDC_OFF, (char*)data, len) == 0) {
        command_state.cdc_output = false;
    }
}

command_state_t get_command_state() {
    return command_state;
}
