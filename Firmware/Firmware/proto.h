/*
 * error_codes.h
 *
 * Created: 2017-03-27 15:20:58
 *  Author: Adam
 */ 


#ifndef PROTO_H_
#define PROTO_H_

struct ErrorCodes {
	static const char * OK;
	static const char * HELLO;
	static const char * DONE;
	static const char * CLIENT_ERROR;
	static const char * UNKNOWN_COMMAND;
	static const char * INVALID_ARGS;
	static const char * INVALID_CHECKSUM;
	static const char * DEVICE_BUSY;
	static const char * COMMAND_TOO_LONG;
	static const char * FIRMWARE_ERROR;
	static const char * BUFFER_OVERFLOW;
	static const char * HARDWARE_ERROR;
	static const char * WATCHDOG_RESTART;
	static const char * BROWNOUT;
};

struct Commands {
	static const char * PING;
	static const char * POWER_ON;
	static const char * HALT;
	static const char * RESET_CONTROLLER;
};

#endif /* PROTO_H_ */