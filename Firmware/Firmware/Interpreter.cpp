/*
* Interpreter.cpp
*
* Created: 2017-03-27 14:51:27
* Author: Adam
*/


#include "interpreter.h"

#include "usart.h"
#include "proto.h"
#include "Controller.h"
#include <string.h>


int8_t hex2int(const char hex) {
	if(hex >= '0' && hex <= '9') return hex - '0';
	if(hex >= 'A' && hex <= 'F') return hex - 'A' + 10;
	if(hex >= 'a' && hex <= 'f') return hex - 'a' + 10;
	return -1;
}

bool testChecksum(char *command) {
	int8_t sum = 0;
	uint8_t i = 0;
	for(; i < 62; i++) {
		if(command[i + 2] == '\n' || command[i + 3] == '\n') break;
		sum ^= command[i];
	}
	if(sum == hex2int(command[i]) * 16 + hex2int(command[i + 1])) return true;
	usart.tx.insert(ErrorCodes::INVALID_CHECKSUM);
	return false;
}

void interpreter(char *command) {
	if(command[0] == '\0' || command[1] == '\0' || command[2] == '\0') {
		usart.tx.insert(ErrorCodes::UNKNOWN_COMMAND);
	}
	else if(strncmp(Commands::PING, command, 4) == 0) {
		usart.tx.insert(ErrorCodes::OK);
	}
	else if(strncmp(Commands::POWER_ON, command, 4) == 0 || strncmp(Commands::HALT, command, 4) == 0) {
		//if(testChecksum(command)) return; //TODO: enable this
		uint32_t value = 0;
		for(uint8_t i = 4; i < 12; i++) {
			int8_t x = hex2int(command[i]);
			if(x < 0) {
				usart.tx.insert(ErrorCodes::INVALID_ARGS);
				return;
			}
			value <<= 4;
			value |= x;
		}
		usart.tx.insert(ErrorCodes::OK);
		if(strncmp(Commands::POWER_ON, command, 4) == 0) controller.setOutputs(value, 500);
		else controller.setOutputs(value, 5500);
	}
	else if(strncmp(Commands::RESET_CONTROLLER, command, 4) == 0) {
		usart.tx.insert(ErrorCodes::OK);
		sendUSART();
		while(true) {
		} //Trigger watchdog
	}
	else {
		usart.tx.insert(ErrorCodes::UNKNOWN_COMMAND);
	}
}
