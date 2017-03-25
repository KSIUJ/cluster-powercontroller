/*
 * usart.cpp
 *
 * Created: 2016-08-21 15:06:01
 *  Author: Adam
 */ 

#include "usart.h"

#include <avr/io.h>
#include <avr/interrupt.h>

USART usart(250, 250);

void initUSART() {
	UBRR0 = /*0x067;*/ 0x0000;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<TXCIE0) | (1<<RXCIE0);
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
	usart.isBusy = false;
}

void sendUSART() {
	if(usart.isBusy) return;
	if(!usart.tx.isEmpty()) {
		usart.isBusy = true;
		UDR0 = usart.tx.pop();
	}
}

ISR(USART_TX_vect) {
	if(!usart.tx.isEmpty()) UDR0 = usart.tx.pop();
	else usart.isBusy = false;
}

ISR(USART_RX_vect) {
	usart.rx.insert(UDR0);
}
