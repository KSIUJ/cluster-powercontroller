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

void interpreter(char * command) {
	if(strncmp(Commands::PING, command, 4) == 0) {
		usart.tx.insert(ErrorCodes::OK);
	} else if(strncmp(Commands::POWER_ON, command, 4) == 0 || strncmp(Commands::HALT, command, 4) == 0) {
		uint32_t value = 0;
		for(int i = 4; i < 12; i++) {
			int8_t x = hex2int(command[i]);
			if(x < 0) {
				usart.tx.insert(ErrorCodes::INVALID_ARGS);
				return;
			}
			value *= 16;
			value += x;
		}
		usart.tx.insert(ErrorCodes::OK);
		if(strncmp(Commands::POWER_ON, command, 4) == 0) controller.setOutputs(value, 500);
		else controller.setOutputs(value, 5000);
	} else if(strncmp(Commands::RESET_CONTROLLER, command, 4) == 0) {
		while(true) {} //Trigger watchdog
	} else {
		usart.tx.insert(ErrorCodes::UNKNOWN_COMMAND);
	}
}