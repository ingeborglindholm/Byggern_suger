
/*
 * can_driver.c
 *
 * Created: 05.10.2022 14:41:39
 *  Author: martge
 */ 

#include "can_driver.h"

void CAN_init(){
	mcp2515_init();
	
	//Set CNF1-> BRP = 3 and SJW = 3
	mcp2515_write(MCP_CNF1, CAN_BRP|SJW4);
	
	//Set CNF2-> BTLMODE: 1 , SAM: 0 , PHSEG: 3 and PRSEG: 1  
	mcp2515_write(MCP_CNF2, BTLMODE | SAMPLE_1X | PHSEG1 | PRSEG);
	
	//Set CNF3-> SOF: 0, WAKFIL: 0 PHSEG2: 5
	mcp2515_write(MCP_CNF3, SOF_DISABLE | WAKFIL_DISABLE | PHSEG2);
	
	//Sette Loopback- mode når konfigurert ferdig
	mcp2515_bit_modify(MCP_CANCTRL, 0x11100000, MODE_LOOPBACK);	//Velger Loopback-mode, se register 10-1 i MCP2515 datasheet

	mcp2515_bit_modify(MCP_CANINTE, MCP_TX0IF ,MCP_TX0IF); //skal bare ha en av disse, de gjør nesten det samme, men ikke helt. Første her nå skriver hele registeret til å være lik TX0IF og ikke bare ORer inn
	//MCP_CANINTE |= MCP_TX0IF;	// setter TX0IE-bitet i CANINTE. Bruker flagg-register-bit fordi det er de som er definert i h-filen til mcp, men bitene har samme plass i CANINTE og CANINTF, så det er same same
	//mcp2515_write(MCP_RXB0CTRL, MCP_RXM0 | MCP_RXM1);	//MCP_RXB0CTRL = 0b0110 0000
}

void CAN_transmit(Setup message){
	mcp2515_write(MCP_TXB0SIDH, message.message_IDH);
	mcp2515_write(MCP_TXB0SIDL, message.message_IDL);
	
	mcp2515_write(MCP_TXB0DLC, message.data_lenght);
	for (int i = 0; i < message.data_lenght; i++){
		mcp2515_write(MCP_TXB0D0 + i, message.data[i]);
	}
	
	mcp2515_request_to_send();
}

uint8_t CAN_recieve(){
	
}


