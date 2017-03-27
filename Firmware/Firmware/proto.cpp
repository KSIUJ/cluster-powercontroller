/*
 * error_codes.cpp
 *
 * Created: 2017-03-27 16:37:01
 *  Author: Adam
 */ 

#include "proto.h"

const char * ErrorCodes::OK = "00 OK\r\n";
const char * ErrorCodes::HELLO = "01 HELLO\r\n";
const char * ErrorCodes::DONE = "02 DONE\r\n";
const char * ErrorCodes::CLIENT_ERROR = "10 CLIENT ERROR\r\n";
const char * ErrorCodes::UNKNOWN_COMMAND = "11 UNKNOWN COMMAND\r\n";
const char * ErrorCodes::INVALID_ARGS = "12 INVALID ARGS\r\n";
const char * ErrorCodes::INVALID_CHECKSUM = "13 INVALID CHECKSUM\r\n";
const char * ErrorCodes::DEVICE_BUSY = "14 DEVICE BUSY\r\n";
const char * ErrorCodes::COMMAND_TOO_LONG = "15 Command too long\r\n";
const char * ErrorCodes::FIRMWARE_ERROR = "20 FIRMWARE ERROR\r\n";
const char * ErrorCodes::BUFFER_OVERFLOW = "21 BUFFER OVERFLOW\r\n";
const char * ErrorCodes::HARDWARE_ERROR = "30 HARDWARE ERROR\r\n";
const char * ErrorCodes::WATCHDOG_RESTART = "31 WATCHDOG RESTART\r\n";
const char * ErrorCodes::BROWNOUT = "32 BROWNOUT RESTART\r\n";

const char * Commands::PING = "PING";
const char * Commands::POWER_ON = "PWON";
const char * Commands::HALT = "HALT";
const char * Commands::RESET_CONTROLLER = "RSTC";
