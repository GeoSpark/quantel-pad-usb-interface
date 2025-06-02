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

#include "flash_config.h"

#include <string.h>
#include <hardware/sync.h>
#include <hardware/flash.h>

// Set the target offset to the last sector of flash.
#define FLASH_TARGET_OFFSET (PICO_FLASH_SIZE_BYTES - FLASH_SECTOR_SIZE)
#define CONFIG_FLASH_TARGET (XIP_BASE + FLASH_TARGET_OFFSET)
#define PAGE_COUNT (FLASH_SECTOR_SIZE / FLASH_PAGE_SIZE)
#define SENTINEL_VALUE 0xA5

typedef struct {
    uint8_t sentinel;  // must be SENTINEL_VALUE
    uint8_t data[FLASH_PAGE_SIZE - 1];
} config_page_t;

const config_page_t* get_config_pages() {
    return (const config_page_t*)CONFIG_FLASH_TARGET;
}

int8_t find_latest_config_index() {
    const config_page_t* pages = get_config_pages();

    for (int i = 0; i < PAGE_COUNT; ++i) {
        if (pages[i].sentinel != SENTINEL_VALUE) {
            return i - 1;  // previous one was the last valid
        }
    }

    return PAGE_COUNT - 1;  // all are valid
}

bool read_config(void* out_data, size_t len) {
    const int8_t index = find_latest_config_index();

    if (index < 0) {
        return false;  // No valid config
    }

    const config_page_t* pages = get_config_pages();
    memcpy(out_data, pages[index].data, len);

    return true;
}

bool write_config(const void* new_data, size_t len) {
    if (len > FLASH_PAGE_SIZE - 1) {
        // Too big.
        return false;
    }

    const int8_t index = find_latest_config_index();
    int next_index = index + 1;

    if (next_index >= PAGE_COUNT) {
        // Erase sector
        const uint32_t ints = save_and_disable_interrupts();
        flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
        restore_interrupts(ints);
        next_index = 0;
    }

    uint8_t page_data[FLASH_PAGE_SIZE] = {0xFF};
    page_data[0] = SENTINEL_VALUE;
    memcpy(&page_data[1], new_data, len);

    const uint32_t ints = save_and_disable_interrupts();
    flash_range_program(FLASH_TARGET_OFFSET + next_index * FLASH_PAGE_SIZE,
                        page_data, FLASH_PAGE_SIZE);
    restore_interrupts(ints);

    return true;
}
