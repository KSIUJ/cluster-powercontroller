/*
 * time.cpp
 *
 * Created: 2017-03-26 23:21:43
 *  Author: Adam
 */ 

#include "time.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint32_t _milis = 0;

uint32_t milis() {
	return _milis;
}

void initTime() {
	TCCR0A = (1<<WGM01);
	OCR0A = 250;
	TCCR0B = (1<<CS00) | (1<<CS01);
	TIMSK0 = (1<<OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
	_milis++;
}
