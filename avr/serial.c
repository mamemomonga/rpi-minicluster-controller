#include "serial.h"
#include <stdio.h>
#include <avr/interrupt.h>

static FILE usart_serialstream;
static T_USART_RECIEVE fp_usart_recieve;

static void usart_recieve_default(char buf);

ISR(USART_RX_vect) {
	if(bit_is_clear(UCSR0A,FE0)){ // フレームエラーなし
		char buf=UDR0;
		fp_usart_recieve(buf);
	}
}

void serial_init(T_USART_RECIEVE fp_ur) {

	// CPUFreq: 14.745600MHz, Baud: 115200bps
	UBRR0H = 0;
	UBRR0L = 15;
	UCSR0A |= (1<<U2X0);

	// USART control and status register n B
	// RXCIEn: RX割り込み有効(USART_RXC_vect)
	// RXENn:  RX有効
	// TXENn:  TX有効
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);

	// USART control and status register n C
	// UCSZn0, UCSZn1, UCSZn2: Character size
	// 0,1,1 = 8bit
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);

	// stdoutをシリアルに設定
	FILE* stream=&usart_serialstream;
	stdout=stream;
	*stream=(FILE)FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

	// シリアル入力時のコールバック
	if(fp_ur==NULL) {
		fp_usart_recieve=usart_recieve_default;
	} else {
		fp_usart_recieve=fp_ur;
	}

}

static void usart_recieve_default(char buf) {}

int uart_putchar(char c, FILE *stream) {
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
	return 0;
}

