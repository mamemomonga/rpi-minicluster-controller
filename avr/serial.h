#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <avr/io.h>
#include <stdio.h>

typedef void (* T_USART_RECIEVE)(char);

void serial_init(T_USART_RECIEVE fp_ur);
int uart_putchar(char c, FILE *stream);

#endif

