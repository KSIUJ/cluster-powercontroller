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

int main(void)
{
	initUSART();
	
	DDRB = 1;
	
	sei();
	
	usart.tx.insertString("KSI controller v0.0.1\r\n");
	
    while (1) {
		sendUSART();
		_delay_ms(10);
		if(!usart.rx.isEmpty()) {
			uint8_t x = usart.rx.pop();
			if(x=='1') {
				PORTB = 1;
				usart.tx.insertString("enable\r\n");
			}
			else {
				PORTB = 0;
				usart.tx.insertString("disable\r\n");
			}
		}
    }
}

