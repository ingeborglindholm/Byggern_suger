
/*
 * mcp2515_driver.c
 *
 * Created: 05.10.2022 14:42:04
 *  Author: martge
 */ 

#include "mcp2515_driver.h"

void mcp2515_reset(){
	// setter CS lav, deretter sender vi instruksjonen MCP_RESET som resetter interne registre og setter config-modus. Setter s� CS h�y
	//CS = SS, siden vi kun har en slave
	set_SS_low();
	SPI_send(MCP_RESET);
	set_SS_high();
}

uint8_t mcp2515_init(){
	uint8_t value;
	SPI_init(); // Initialize SPI
	mcp2515_reset(); // Send reset - command
	
	//De to neste linjene er fors�k p� � endre mode 
	//mcp2515_write(MCP_CANCTRL, MODE_CONFIG );
	//mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LISTENONLY);
	
	// Self - test
	value = mcp2515_read(MCP_CANSTAT);
	uint8_t can_ctrl = mcp2515_read(MCP_CANCTRL);
	if ((value & MODE_MASK) != MODE_CONFIG){
		printf ("MCP2515 is NOT in configuration mode after reset !\n\r");
		return 1;
	}
	// More initialization
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	return 0;
}


uint8_t mcp2515_read(uint8_t address){
	uint8_t result;
	
	set_SS_low();
	//PORTB &= ~(1 << PB4); // Select CAN - controller -> bruke funksjonen v�r slaveselect low
	
	SPI_send(MCP_READ); // Send read instruction
	SPI_send(address); // Send address
	result = SPI_read(); // Read result
	
	//PORTB |= (1 << CAN_CS); // Deselect CAN - controller
	set_SS_high();
	return result;
}