
/*
 * spi_driver.c
 *
 * Created: 05.10.2022 14:42:16
 *  Author: martge
 */ 


#include "spi_driver.h"



void SPI_init(){
	//Setter modus til SPI
	SPCR &= ~(1<<CPOL);
	SPCR &= ~(1<<CPHA);
	//Setter MOSI og SCK til output
	DDRB |= (1<<DDB5)|(1<<DDB7);
	//Enable SPI, Master, setter klokke til fck/16
	SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR0);
	
	
}

void SPI_send(uint8_t data){
	//Start transmission
	SPDR = data;
	//venter på at transmisjon skal fullføres 
	while (!(SPSR & (1<<SPIF)));
}

uint8_t SPI_read(){
	//Legger en dummy byte på SPDR registeret og sender dette til CAN, får da tilbake det som lå på registere til CAN. 
	uint8_t dummy = 0b00000000;
	SPI_send(dummy);
	return SPDR;
}