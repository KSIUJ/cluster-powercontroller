/*
* Firmware.cpp
*
* Created: 2017-03-03 20:23:59
* Author : Adam
*/

#include "usart.h"
#include "shift_regs.h"
#include "time.h"
#include "proto.h"
#include "interpreter.h"
#include "controller.h"
#include <avr/io.h>
#include <avr/wdt.h>

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t resetSource __attribute__((section(".noinit")));
void wdtPreInit() __attribute__
((naked)) __attribute__((section(".init3")));

void wdtPreInit() {
	resetSource = MCUSR;
	MCUSR = 0;
	wdt_disable();
}

int main(void) {
	initTime();
	initUSART();
	initRegs();

	DDRB |= (1 << PORTB1);
	sei();

	usart.tx.insert("KSI controller v1.0.0\r\n");
	if(resetSource & (1 << WDRF)) usart.tx.insert(ErrorCodes::WATCHDOG_RESTART);
	else if((resetSource & (1 << PORF)) || (resetSource & (1 << EXTRF))) usart.tx.insert(ErrorCodes::HELLO);
	else if(resetSource & (1 << BORF)) usart.tx.insert(ErrorCodes::BROWNOUT);
	else usart.tx.insert(ErrorCodes::HARDWARE_ERROR); //Should not happen

	char command[65];

	wdt_enable(WDTO_120MS);
	SLED_ON();

	while(true) {
		sendUSART();
		controller.worker();

		if(!usart.rx.isEmpty()) {
			if(usart.rx.isFULL()) {
				usart.rx.clear();
				usart.tx.insert(ErrorCodes::BUFFER_OVERFLOW);
				continue;
			}

			if(usart.rx.linesInBufffer() > 0) {
				bool lineEnd = false;
				uint8_t i = 0;
				for(; i < 64; i++) {
					command[i] = usart.rx.pop();
					if(command[i] == '\n') {
						command[i + 1] = '\0';
						lineEnd = true;
						break;
					}
				}
				if(lineEnd) interpreter(command);
				else {
					while(usart.rx.linesInBufffer() > 0) usart.rx.pop();
					usart.tx.insert(ErrorCodes::COMMAND_TOO_LONG);
				}
			}

		}

		wdt_reset();
	}
}
