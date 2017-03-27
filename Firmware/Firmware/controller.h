/*
* Controller.h
*
* Created: 2017-03-27 18:54:33
* Author: Adam
*/


#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <stdint.h>

class Controller {
private:
	bool busy;
	uint32_t start;
	uint32_t lenght;
public:
	Controller();
	void setOutputs(uint32_t data, uint16_t pulseLenght);
	bool isBusy();
	void worker();
	void clear();
}; //Controller

extern Controller controller;

#endif //__CONTROLLER_H__
