
/*
 * can_driver.h
 *
 * Created: 05.10.2022 14:41:20
 *  Author: martge
 */ 

#include "mcp2515_driver.h"

//#define F_CPU 16000000 //Clock Speed

typedef struct{
	uint8_t message_IDH;
	uint8_t message_IDL;
	uint8_t data_lenght;
	uint8_t data[8];
	} Frame;

void CAN_init();
void CAN_transmit(Frame message);
Frame CAN_recieve();

