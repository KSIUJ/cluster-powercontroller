/*
 * shift_regs.cpp
 *
 * Created: 2017-03-25 23:21:43
 *  Author: Adam
 */ 

#include "shift_regs.h"
#include <avr/io.h>

#define DS_PORT    PORTB
#define DS_PIN     3
#define ST_CP_PORT PORTB
#define ST_CP_PIN  2
#define SH_CP_PORT PORTB
#define SH_CP_PIN  5

#define DS_low()  DS_PORT&=~(1<<DS_PIN)
#define DS_high() DS_PORT|=(1<<DS_PIN)
#define ST_CP_low()  ST_CP_PORT&=~(1<<ST_CP_PIN)
#define ST_CP_high() ST_CP_PORT|=(1<<ST_CP_PIN)
#define SH_CP_low()  SH_CP_PORT&=~(1<<SH_CP_PIN)
#define SH_CP_high() SH_CP_PORT|=(1<<SH_CP_PIN)

void initRegs() {
	DDRB |= (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB3) | (1<<PORTB5);
	PORTB |= (1<<PORTB1);
	setRegs(0xFFFFFFFF);
}

void regSendByte(uint8_t data) {
	SH_CP_low();
	ST_CP_low();
	for (uint8_t i=0;i<8;i++)
	{
		if (data & (1<<i)) DS_high();
		else DS_low();
		
		SH_CP_high();
		SH_CP_low();
	}
	ST_CP_high();
}

union regData {
	uint32_t data;
	uint8_t regs[4];
};

void setRegs(uint32_t data) {
	regData x;
	x.data = data;
	for(uint8_t i = 0; i<4; i++) {
		regSendByte(x.regs[i]);
	}
}
