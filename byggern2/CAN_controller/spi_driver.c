
/*
 * spi_driver.c
 *
 * Created: 05.10.2022 14:42:16
 *  Author: martge
 */ 


#include "spi_driver.h"



void SPI_init(){
	
	//Setter MOSI, SCK og SS til output
	DDRB |= (1<<PB4)|(1<<PB5)|(1<<PB7);
	DDRB &= ~(1<<PB6);
	//Enable SPI, Master, setter klokke til fck/16
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
	//Setter modus til SPI
	SPCR &= ~(1<<CPOL);
	SPCR &= ~(1<<CPHA);
	//Setter SS til 1
	PORTB |= (1<<PB4);
}


void set_SS_low(){
	//Setter SS til 0
	PORTB &= ~(1<<PB4);
}

void set_SS_high(){
	//Setter SS til 1
	PORTB |= (1<<PB4);
}

void SPI_send(uint8_t data){
	//setter SS lav
	set_SS_low();
	//Start transmission
	SPDR = data;
	//venter på at transmisjon skal fullføres 
	while (!(SPSR & (1<<SPIF)));
	//Setter SS høy
	set_SS_high();
}

uint8_t SPI_read(){
	//Legger en dummy byte på SPDR registeret og sender dette til CAN, får da tilbake det som lå på registere til CAN. 
	uint8_t dummy = 0x11;
	SPI_send(dummy);
	return SPDR;
}