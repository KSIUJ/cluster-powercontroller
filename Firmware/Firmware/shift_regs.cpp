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

#define DS_LOW()  DS_PORT&=~(1<<DS_PIN)
#define DS_HIGH() DS_PORT|=(1<<DS_PIN)
#define ST_CP_LOW()  ST_CP_PORT&=~(1<<ST_CP_PIN)
#define ST_CP_HIGH() ST_CP_PORT|=(1<<ST_CP_PIN)
#define SH_CP_LOW()  SH_CP_PORT&=~(1<<SH_CP_PIN)
#define SH_CP_HIGH() SH_CP_PORT|=(1<<SH_CP_PIN)

void initRegs() {
	DDRB |= (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB5);
	PORTB |= (1 << PORTB1);
	setRegs(0xFFFFFFFF);
}

void regSendByte(uint8_t data) {
	SH_CP_LOW();
	for(uint8_t i = 0; i < 8; i++) {
		if(data & (1 << i)) DS_HIGH();
		else DS_LOW();

		SH_CP_HIGH();
		SH_CP_LOW();
	}

}

union regData {
	uint32_t data;
	uint8_t regs[4];
};

void setRegs(uint32_t data) {
	regData x;
	x.data = data;
	ST_CP_LOW();
	for(uint8_t i = 0; i < 4; i++) {
		regSendByte(x.regs[i]);
	}
	ST_CP_HIGH();
}
