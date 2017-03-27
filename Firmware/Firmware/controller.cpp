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
	setRegs(data);
	busy = true;
}

void Controller::clear() {
	setRegs(0xFFFFFFFF);
	busy = false;
}

void Controller::worker() {
	if(busy && milis() - start > lenght) {
		clear();
		usart.tx.insert(ErrorCodes::DONE);
	}
}

Controller controller;
