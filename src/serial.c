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

#include "config.h"
#include "serial.h"
#include "quantel/quantel.h"

#include <stdbool.h>
#include <string.h>

#include "time.h"

#include "hardware/gpio.h"
#include "hardware/uart.h"

#define UART_PAD uart0
#define UART_PAD_TX 0
#define UART_PAD_RX 1

#define UART_PB uart1
#define UART_PB_TX 4
#define UART_PB_RX 5

volatile bool send_packet = false;
uint8_t send_buf[QUANTEL_PACKET_SIZE];

// status_t status;
// pen_data_t pen_data;
// uint8_t keycode;
// volatile bool valid = false;

// void on_rx_pad() {
//     valid = false;
//
//     while (uart_is_readable(UART_PAD) && !valid) {
//         valid = handle_packet(uart_getc(UART_PAD), &status, &pen_data, &keycode);
//     }
// }

void setup_uart() {
    // UART0 for receiving data from the PAD
    uart_init(UART_PAD, RS422_BAUD);
    gpio_set_function(UART_PAD_TX, GPIO_FUNC_UART);
    gpio_set_function(UART_PAD_RX, GPIO_FUNC_UART);
    uart_set_hw_flow(UART_PAD, false, false);
    uart_set_format(UART_PAD, 8, 1, UART_PARITY_NONE);
    // uart_set_fifo_enabled(UART_PAD, true);
    // irq_set_exclusive_handler(UART0_IRQ, on_rx_pad);
    // irq_set_enabled(UART0_IRQ, true);
    // uart_set_irq_enables(UART_PAD, true, false);

    // UART1 for sending data to the PB
    uart_init(UART_PB, RS422_BAUD);
    gpio_set_function(UART_PB_TX, GPIO_FUNC_UART);
    gpio_set_function(UART_PB_RX, GPIO_FUNC_UART);
    uart_set_hw_flow(UART_PB, false, false);
    uart_set_format(UART_PB, 8, 1, UART_PARITY_NONE);
    // uart_set_fifo_enabled(UART_PB, true);
    // irq_set_enabled(UART1_IRQ, false);
}

void send_to_pb(uint8_t data) {
    uart_putc(UART_PB, data);
}
