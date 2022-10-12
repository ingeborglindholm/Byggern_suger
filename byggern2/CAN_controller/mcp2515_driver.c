
/*
 * mcp2515_driver.c
 *
 * Created: 05.10.2022 14:42:04
 *  Author: martge
 */ 

#include "mcp2515_driver.h"

void mcp2515_reset(){
	// setter CS lav, deretter sender vi instruksjonen MCP_RESET som resetter interne registre og setter config-modus. Setter så CS høy
	//CS = SS, siden vi kun har en slave
	set_SS_low();
	SPI_send(MCP_RESET);
	set_SS_high();
}

uint8_t mcp2515_init(){
	uint8_t value;
	SPI_init(); // Initialize SPI
	mcp2515_reset(); // Send reset - command
	
	//De to neste linjene er forsøk på å endre mode 
	//mcp2515_write(MCP_CANCTRL, MODE_CONFIG );
	//mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LISTENONLY);
	
	// Self - test
	value = mcp2515_read(MCP_CANSTAT);
	uint8_t can_ctrl = mcp2515_read(MCP_CANCTRL);
	printf("\nvalue: %d can_ctrl: %d \n" , value, can_ctrl);
	/*if ((value & MODE_MASK) != MODE_CONFIG){
		printf (" MCP2515 is NOT in configuration mode after reset !\n");
		return 1;
	}*/
	printf("Etter init");
	// More initialization
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	return 0;
}


uint8_t mcp2515_read(uint8_t address){
	uint8_t result;
	
	set_SS_low();
	//PORTB &= ~(1 << PB4); // Select CAN - controller -> bruke funksjonen vår slaveselect low
	
	SPI_send(MCP_READ); // Send read instruction
	SPI_send(address); // Send address
	result = SPI_read(); // Read result
	
	//PORTB |= (1 << CAN_CS); // Deselect CAN - controller
	set_SS_high();
	return result;
}void mcp2515_write(uint8_t address, uint8_t data){	set_SS_low();	SPI_send(MCP_WRITE);	SPI_send(address);	SPI_send(data);	set_SS_high();}void mcp2515_request_to_send(){	set_SS_low();	SPI_send(MCP_RTS_TX0);	// setter MCP_TXB0CTRL.TXREQ-bitet for bufferet vårt (TX0)	set_SS_high();}void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data){	set_SS_low();	uint8_t register_list[12] = {MCP_TXB0CTRL, MCP_TXB1CTRL, MCP_TXB2CTRL, MCP_RXB0CTRL, MCP_RXB1CTRL, MCP_CNF3, MCP_CNF2, MCP_CNF1, MCP_CANINTE, MCP_CANINTF, MCP_EFLG, MCP_CANCTRL};	//MCP_BFPCTRL, MCP_TXRTSCTRL er i listen i databladet, men ikke i filen med registre vi fikk fra BlackBoard		uint8_t address_in_list = 0;		for(int i = 0; i < 12; i++){		if(register_list[i] == address){			SPI_send(MCP_BITMOD);			//må sjekke om address som vi tok inn som input faktisk er i listen over registre som er lov å manipulere manuelt bit for bit			SPI_send(address);			SPI_send(mask);			SPI_send(data);			set_SS_high();			address_in_list = 1;			break;		}	}		if (address_in_list == 0){		printf("You can not bit-modify register %d \n", address);	}}uint8_t mcp2515_read_status(){	uint8_t status;	set_SS_low();	SPI_send(MCP_READ_STATUS);	// CAN-controlleren sender nå de 8 status-bitene på SO-bussen til ATmegaen. Status-bitene er 8 bits fra fire ulike registre, se figur 12-8 i databladet til MCP2515	status = SPI_read();	set_SS_high();		return status;}