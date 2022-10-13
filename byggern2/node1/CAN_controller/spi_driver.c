
/*
 * spi_driver.c
 *
 * Created: 05.10.2022 14:42:16
 *  Author: martge
 */ 


#include "spi_driver.h"
#include <util/delay.h>

void set_SS_low(){
	//Setter SS til 0
	PORTB &= ~(1<<PB4);
}

void set_SS_high(){
	//Setter SS til 1
	PORTB |= (1<<PB4);
}

void SPI_init(){
	// input = 0, output = 1
	//Setter MOSI, SCK og SS til output
	DDRB |= (1<<PB4)|(1<<PB5)|(1<<PB7);
	DDRB &= ~(1<<PB6);
	//Enable SPI, Master, setter klokke til fck/16
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
	//Setter modus til SPI
	// kommenterte ut 14:47 onsdag 12.10
	SPCR &= ~(1<<CPOL);
	SPCR &= ~(1<<CPHA);
	//Setter SS til 1
	//PORTB |= (1<<PB4);
	set_SS_high();
}


void SPI_send(uint8_t data){
	//Start transmission
	SPDR = data;
	
	//venter p� at transmision skal fullf�res 
	while (!(SPSR & (1<<SPIF))){
		;
	}

	/*
	SPIF settes til 1 n�r en serial transfer er er ferdig.
	while-l�kken kj�rer while(1), som er mens SPSR & SPIF er 0 fordi vi inverterer
	alts� n�r SPSR blir 1 p� bit 7 (SPIF) blir hele uttrykket 0 og while-l�kken avsluttes
	
	MCP_RXF4EID0 brukes i SPI_send mellom mcp_read(CANSTAT) og mcp_read(CANCTRL) i mcp_init() og etter mcp_read(CANCTRL) igjen -> er det dummyen??
	- glem det, var dummy 
	SPDR er 0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! wtf??
	*/
}

uint8_t SPI_read(){
	//Legger en dummy byte p� SPDR registeret og sender dette til CAN, f�r da tilbake det som l� p� registere til CAN. 
	uint8_t dummy = 0x11;
	SPI_send(dummy);
	return SPDR;
}

// stud ass sa vi burde ha set_SS_high/low utenfor SPI_send fordi senere skal vi sende flere ganger p� rad mens CS er lav hele tiden
// vi hadde fra f�r at vi satte CS lav og s� h�y f�rst og sist i alle mcp-funksjonene ogs� gjorde vi det inni SPI_send ogs�, s� det ble dobbelt opp
/*
Var tydeligvis dette som var problemet, fyyyyyyyyyyyyYYYYY aah. jaja. Kommenterte ut set_SS inni read-funksjonen og da var det good
Virker som at SPDR ikke alltid f�r med seg all dataen (alle bitene) fordi CS settes h�y f�r den er "ferdig", aner ikke hvorfor den gj�r det, men er n� s�nn det virker


Skjedde noe rart p� slutten, jobbet i SPI, ogs� plutselig ville den ikke flashe n�r jeg kj�rte can_test i main med mindre jeg kommenterte ut multifunction_init
Den kj�rte derimot hvis jeg kj�rte SPDR_test. Den ble ogs� stuck i en evig loop virket det som og bare printet "Start test:" i det uendelige, alts� den kj�rte alt som var over multifunction_init i main, veldig rart 

I tillegg ble menyen litt fakka, men kj�rte den ikke, s� var kanskje det
*/