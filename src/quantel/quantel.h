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

#ifndef QUANTEL_H
#define QUANTEL_H

#include <stdbool.h>
#include <stdint.h>

#define QUANTEL_PACKET_SIZE 9

typedef struct {
    uint8_t packet_start: 1; // Always 1
    uint8_t has_keycode: 1;
    uint8_t has_pen_data: 1;
    uint8_t unknown1: 1;
    uint8_t joystick_down: 1;
    uint8_t joystick_up: 1;
    uint8_t joystick_right: 1;
    uint8_t joystick_left: 1;
    uint8_t byte_marker: 1; // Always 0
    uint8_t button_5: 1;
    uint8_t unknown2: 1;
    uint8_t key_up: 1;
    uint8_t button_4: 1;
    uint8_t button_3: 1;
    uint8_t button_2: 1;
    uint8_t button_1: 1;
} status_t;

typedef struct {
    int16_t x;
    int16_t y;
    uint8_t pressure;
} pen_data_t;

bool handle_packet(uint8_t data, status_t* status, pen_data_t* pen_data, uint8_t* keycode);
uint8_t map_keycode(uint8_t keycode);

#endif //QUANTEL_H
