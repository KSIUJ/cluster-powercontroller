/* 
* Interpreter.cpp
*
* Created: 2017-03-27 14:51:27
* Author: Adam
*/


#include "Interpreter.h"

#include "usart.h"
#include "proto.h"
#include <string.h>

void interpreter(char * command) {
	if(strncmp(Commands::PING, command, 4) == 0) {
		usart.tx.insert(ErrorCodes::OK);
	} else if(strncmp(Commands::POWER_ON, command, 4) == 0) {
		
	} else if(strncmp(Commands::HALT, command, 4) == 0) {
	
	} else if(strncmp(Commands::RESET_CONTROLLER, command, 4) == 0) {
	
	} else {
		usart.tx.insert(ErrorCodes::UNKNOWN_COMMAND);
	}
}