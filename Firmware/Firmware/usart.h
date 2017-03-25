/*
 * usart.h
 *
 * Created: 2016-08-20 22:12:35
 *  Author: Adam
 */ 


#ifndef USART_H_
#define USART_H_

#include "FIFO.h"

struct USART {
	FIFO rx, tx;
	volatile bool isBusy;
	USART(uint8_t RXbuff, uint8_t TXbuff) : rx(RXbuff), tx(TXbuff), isBusy(true) {}
};

void initUSART();
extern USART usart;
void sendUSART();

#endif /* USART_H_ */