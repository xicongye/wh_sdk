#include "platform.h"

static volatile uint8_t *uart;

void ns16550a_uart_init() {
    uart = (uint8_t *)(void *)NS16550A_UART0_CTRL_ADDR;
    uint32_t uart_freq = UART0_CLOCK_FREQ;
    uint32_t baud_rate = UART0_BAUD_RATE;
    uint32_t divisor = uart_freq / (16 * baud_rate);
    uart[UART_LCR] = UART_LCR_DLAB;
    uart[UART_DLL] = divisor & 0xff;
    uart[UART_DLM] = (divisor >> 8) & 0xff;
    uart[UART_LCR] = UART_LCR_PODD | UART_LCR_8BIT;
}

int ns16550a_putchar(int ch) {
    while ((uart[UART_LSR] & UART_LSR_RI) == 0)
        ;
    return uart[UART_THR] = ch & 0xff;
}


