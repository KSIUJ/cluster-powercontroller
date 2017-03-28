/*
* Controller.cpp
*
* Created: 2017-03-27 18:54:33
* Author: Adam
*/

#include "controller.h"
#include "shift_regs.h"
#include "time.h"
#include "usart.h"
#include "proto.h"

const uint8_t portMap[32] = {
	1, 2, 3, 4, 5, 6, 7, 0,
	8, 15, 14, 13, 12, 11, 10, 9,
	16, 23, 22, 21, 20, 19, 18, 17,
	25, 26, 27, 28, 29, 30, 31, 24	
};

Controller::Controller() : busy(false) {
}

bool Controller::isBusy() {
	return busy;
}

void Controller::setOutputs(uint32_t data, uint16_t pulseLenght) {
	if(isBusy()) {
		usart.tx.insert(ErrorCodes::DEVICE_BUSY);
		return;
	}
	start = milis();
	lenght = pulseLenght;
	uint32_t ports = 0;
	for(uint8_t i = 0; i < 32; i++) {
		if(data & (1 << i)) 
		ports |= ((uint32_t)1 << portMap[i]);
	}
	setRegs(~ports);
	busy = true;
	SLED_OFF();
}

void Controller::clear() {
	setRegs(0xFFFFFFFF);
	busy = false;
}

void Controller::worker() {
	if(busy && milis() - start > lenght) {
		clear();
		usart.tx.insert(ErrorCodes::DONE);
		SLED_ON();
	}
}

Controller controller;
