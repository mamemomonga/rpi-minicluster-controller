#include "main.h"

// 復帰しないスリープ(リセットで復帰)
#define ENTER_SLEEP { \
	set_sleep_mode(SLEEP_MODE_PWR_DOWN); \
	sleep_enable(); \
	sleep_cpu(); \
   	_delay_ms(500); \
}

void usart_recieve(char buf) {
	// printf("recieve: %c\r\n\r\n",buf);
	switch(buf) {

		case '1':
			printf("*** SWITCH Pi1 ***\r\n\r\n");
			do_switch(1);
			break;

		case '2':
			printf("*** SWITCH Pi2 ***\r\n\r\n");
			do_switch(2);
			break;

		case '3':
			printf("*** SWITCH Pi3 ***\r\n\r\n");
			do_switch(3);
			break;

		case '4':
			printf("*** SWITCH Pi4 ***\r\n\r\n");
			do_switch(4);
			break;

		case 'q':
			printf("*** RESET Pi1 ***\r\n\r\n");
			do_fast_blink_dual(1);
			do_reset(1);
			do_switch(1);
			break;

		case 'w':
			printf("*** RESET Pi2 ***\r\n\r\n");
			do_fast_blink_dual(2);
			do_reset(2);
			do_switch(2);
			break;

		case 'e':
			printf("*** RESET Pi3 ***\r\n\r\n");
			do_fast_blink_dual(3);
			do_reset(3);
			do_switch(3);
			break;

		case 'r':
			printf("*** RESET Pi4 ***\r\n\r\n");
			do_fast_blink_dual(4);
			do_reset(4);
			do_switch(4);
			break;

		default:
			show_message();
			break;

	}
}

void do_switch(uint8_t target) {
	SER_AVR_DIS;
	switch(target) {
		case 1:
			SER_RP1_ENA;
			LED_RP1_H;
			break;
		case 2:
			SER_RP2_ENA;
			LED_RP2_H;
			break;
		case 3:
			SER_RP3_ENA;
			LED_RP3_H;
			break;
		case 4:
			SER_RP4_ENA;
			LED_RP4_H;
			break;
	}
	LED_ACT_L;
	ENTER_SLEEP;
}

void do_fast_blink_dual(uint8_t target) {
	switch(target) {
		case 1:
			LED_ACT_H;
			LED_RP1_H;
			for(uint8_t i=0; i<50; i++){
				_delay_ms(40);
				LED_ACT_T;
				LED_RP1_T;
			}
			LED_ACT_L;
			LED_RP1_L;
			break;
		case 2:
			LED_ACT_H;
			LED_RP2_H;
			for(uint8_t i=0; i<50; i++){
				_delay_ms(40);
				LED_ACT_T;
				LED_RP2_T;
			}
			LED_ACT_L;
			LED_RP2_L;
			break;
		case 3:
			LED_ACT_H;
			LED_RP3_H;
			for(uint8_t i=0; i<50; i++){
				_delay_ms(40);
				LED_ACT_T;
				LED_RP3_T;
			}
			LED_ACT_L;
			LED_RP3_L;
			break;
		case 4:
			LED_ACT_H;
			LED_RP4_H;
			for(uint8_t i=0; i<50; i++){
				_delay_ms(40);
				LED_ACT_T;
				LED_RP4_T;
			}
			LED_ACT_L;
			LED_RP4_L;
			break;
	}
}

void do_reset(uint8_t target) {
	switch(target) {
		case 1:
			RST_RP1_H;
			_delay_ms(100);
			RST_RP1_L;
			break;
		case 2:
			RST_RP2_H;
			_delay_ms(100);
			RST_RP2_L;
			break;
		case 3:
			RST_RP3_H;
			_delay_ms(100);
			RST_RP3_L;
			break;
		case 4:
			RST_RP4_H;
			_delay_ms(100);
			RST_RP4_L;
			break;
	}
	_delay_ms(500);
}


void show_message(void) {
	cli();
	printf_P(PSTR("\r\n"));
	printf_P(PSTR("--- PiController ---\r\n"));
	printf_P(PSTR("SERIAL: 1:Pi1, 2:Pi2, 3:Pi3 4:Pi4\r\n"));
	printf_P(PSTR("RESET:  q:Pi1, w:Pi2, e:Pi3 r:Pi4\r\n"));
	sei();
}

int main(void) {

	serial_init(usart_recieve);
	cli();

	LED_ACT_DIR;
	LED_RP1_DIR;
	LED_RP2_DIR;
	LED_RP3_DIR;
	LED_RP4_DIR;

	SER_AVR_DIR;
	SER_RP1_DIR;
	SER_RP2_DIR;
	SER_RP3_DIR;
	SER_RP4_DIR;

	RST_EN_DIR;
	RST_RP1_DIR;
	RST_RP2_DIR;
	RST_RP3_DIR;
	RST_RP4_DIR;

	RST_EN_DIS;
	RST_RP1_L;
	RST_RP2_L;
	RST_RP3_L;
	RST_RP4_L;

	LED_ACT_L;
	LED_RP1_L;
	LED_RP2_L;
	LED_RP3_L;
	LED_RP4_L;

	SER_AVR_DIS;
	SER_RP1_DIS;
	SER_RP2_DIS;
	SER_RP3_DIS;
	SER_RP4_DIS;

	SER_AVR_ENA;
	RST_EN_ENA;

	for(uint8_t i=0; i<20; i++){
		_delay_ms(30);
		LED_ACT_T;
	}
	LED_ACT_H;
	_delay_ms(100);

	show_message();
	for(;;){
		_delay_ms(500);
		LED_ACT_T;
	}
}

