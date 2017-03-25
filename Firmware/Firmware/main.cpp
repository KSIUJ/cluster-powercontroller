/*
 * Firmware.cpp
 *
 * Created: 2017-03-03 20:23:59
 * Author : Adam
 */ 

#include "usart.h"

#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#define DS_PORT    PORTB
#define DS_PIN     3
#define ST_CP_PORT PORTB
#define ST_CP_PIN  2
#define SH_CP_PORT PORTB
#define SH_CP_PIN  5

#define DS_low()  DS_PORT&=~_BV(DS_PIN)
#define DS_high() DS_PORT|=_BV(DS_PIN)
#define ST_CP_low()  ST_CP_PORT&=~_BV(ST_CP_PIN)
#define ST_CP_high() ST_CP_PORT|=_BV(ST_CP_PIN)
#define SH_CP_low()  SH_CP_PORT&=~_BV(SH_CP_PIN)
#define SH_CP_high() SH_CP_PORT|=_BV(SH_CP_PIN)

void output_led_state(unsigned char __led_state)
{
	SH_CP_low();
	ST_CP_low();
	for (int i=0;i<8;i++)
	{
		if (bit_is_set(__led_state, i)) DS_high();
		else DS_low();
		
		SH_CP_high();
		SH_CP_low();
	}
	ST_CP_high();
}


int main(void) {
	initUSART();
	
	DDRB = (1<<PORTB1) | (1<<PORTB0) | (1<<PORTB2) | (1<<PORTB3) | (1<<PORTB5);
	PORTB = (1<<PORTB1);
	//_delay_ms(1);
	
	output_led_state(0xff);
	output_led_state(0xff);
	output_led_state(0xff);
	output_led_state(0xff);
	
	sei();	
	
	usart.tx.insertString("KSI controller v0.0.1\r\n");
	
    while (1) {
		sendUSART();

		if(!usart.rx.isEmpty()) {
			uint8_t x = usart.rx.pop();
			if(x=='1') {
				PORTB |= 1;
				usart.tx.insertString("enable\r\n");
						output_led_state(0x0);
						output_led_state(0x0);
						output_led_state(0x0);
						output_led_state(0x0);
				
			}
			else {
				PORTB ^= 1;
				usart.tx.insertString("disable\r\n");
					output_led_state(0xff);
					output_led_state(0xff);
					output_led_state(0xff);
					output_led_state(0xff);
			}
		}
    }
}

