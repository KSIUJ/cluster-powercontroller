/*
 * Firmware.cpp
 *
 * Created: 2017-03-03 20:23:59
 * Author : Adam
 */ 

#include "usart.h"
#include "shift_regs.h"
#include "time.h"

#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void) {
	initTime();
	initUSART();
	initRegs();
	
	DDRB |= (1<<PORTB1);
	
	sei();	
	
	usart.tx.insertString("KSI controller v0.0.1\r\n");
	
    while (1) {
		sendUSART();

		if(!usart.rx.isEmpty()) {
			uint8_t x = usart.rx.pop();
			if(x=='1') {
				PORTB |= 1;
				usart.tx.insertString("enable\r\n");
				setRegs(0);
				
			}
			else {
				PORTB ^= 1;
				usart.tx.insertString("disable\r\n");
				setRegs(0xFFFFFFFF);
			}
		}
    }
}

