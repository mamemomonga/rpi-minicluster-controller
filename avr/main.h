#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "serial.h"

int main(void);
void usart_recieve(char);
void do_switch(uint8_t);
void do_fast_blink_dual(uint8_t);
void do_reset(uint8_t);
void show_message(void);

// LED
#define LED_ACT_DIR DDRB  |=  _BV(PB5)
#define LED_ACT_H   PORTB |=  _BV(PB5)
#define LED_ACT_L   PORTB &=~ _BV(PB5)
#define LED_ACT_T   PORTB ^=  _BV(PB5)

#define LED_RP1_DIR DDRB  |=  _BV(PB4)
#define LED_RP1_H   PORTB |=  _BV(PB4)
#define LED_RP1_L   PORTB &=~ _BV(PB4)
#define LED_RP1_T   PORTB ^=  _BV(PB4)

#define LED_RP2_DIR DDRB  |=  _BV(PB3)
#define LED_RP2_H   PORTB |=  _BV(PB3)
#define LED_RP2_L   PORTB &=~ _BV(PB3)
#define LED_RP2_T   PORTB ^=  _BV(PB3)

#define LED_RP3_DIR DDRB  |=  _BV(PB2)
#define LED_RP3_H   PORTB |=  _BV(PB2)
#define LED_RP3_L   PORTB &=~ _BV(PB2)
#define LED_RP3_T   PORTB ^=  _BV(PB2)

#define LED_RP4_DIR DDRB  |=  _BV(PB1)
#define LED_RP4_H   PORTB |=  _BV(PB1)
#define LED_RP4_L   PORTB &=~ _BV(PB1)
#define LED_RP4_T   PORTB ^=  _BV(PB1)

// Serial Output Enable(負論理)
#define SER_AVR_DIR DDRC  |=  _BV(PC5)
#define SER_AVR_ENA PORTC &=~ _BV(PC5)
#define SER_AVR_DIS PORTC |=  _BV(PC5)

#define SER_RP1_DIR DDRC  |=  _BV(PC4)
#define SER_RP1_ENA PORTC &=~ _BV(PC4)
#define SER_RP1_DIS PORTC |=  _BV(PC4)

#define SER_RP2_DIR DDRC  |=  _BV(PC3)
#define SER_RP2_ENA PORTC &=~ _BV(PC3)
#define SER_RP2_DIS PORTC |=  _BV(PC3)

#define SER_RP3_DIR DDRC  |=  _BV(PC2)
#define SER_RP3_ENA PORTC &=~ _BV(PC2)
#define SER_RP3_DIS PORTC |=  _BV(PC2)

#define SER_RP4_DIR DDRC |=   _BV(PC1)
#define SER_RP4_ENA PORTC &=~ _BV(PC1)
#define SER_RP4_DIS PORTC |=  _BV(PC1)

// Reset(正論理)
#define RST_EN_DIR DDRD  |=  _BV(PD4)
#define RST_EN_ENA PORTD |=  _BV(PD4)
#define RST_EN_DIS PORTD &=~ _BV(PD4)

#define RST_RP1_DIR DDRD  |=  _BV(PD7)
#define RST_RP1_H   PORTD |=  _BV(PD7)
#define RST_RP1_L   PORTD &=~ _BV(PD7)

#define RST_RP2_DIR DDRB  |=  _BV(PB0)
#define RST_RP2_H   PORTB |=  _BV(PB0)
#define RST_RP2_L   PORTB &=~ _BV(PB0)

#define RST_RP3_DIR DDRD  |=  _BV(PD5)
#define RST_RP3_H   PORTD |=  _BV(PD5)
#define RST_RP3_L   PORTD &=~ _BV(PD5)

#define RST_RP4_DIR DDRD  |=  _BV(PD6)
#define RST_RP4_H   PORTD |=  _BV(PD6)
#define RST_RP4_L   PORTD &=~ _BV(PD6)

#endif

