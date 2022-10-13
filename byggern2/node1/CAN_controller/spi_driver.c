
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
	
	//venter på at transmision skal fullføres 
	while (!(SPSR & (1<<SPIF))){
		;
	}

	/*
	SPIF settes til 1 når en serial transfer er er ferdig.
	while-løkken kjører while(1), som er mens SPSR & SPIF er 0 fordi vi inverterer
	altså når SPSR blir 1 på bit 7 (SPIF) blir hele uttrykket 0 og while-løkken avsluttes
	
	MCP_RXF4EID0 brukes i SPI_send mellom mcp_read(CANSTAT) og mcp_read(CANCTRL) i mcp_init() og etter mcp_read(CANCTRL) igjen -> er det dummyen??
	- glem det, var dummy 
	SPDR er 0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! wtf??
	*/
}

uint8_t SPI_read(){
	//Legger en dummy byte på SPDR registeret og sender dette til CAN, får da tilbake det som lå på registere til CAN. 
	uint8_t dummy = 0x11;
	SPI_send(dummy);
	return SPDR;
}

// stud ass sa vi burde ha set_SS_high/low utenfor SPI_send fordi senere skal vi sende flere ganger på rad mens CS er lav hele tiden
// vi hadde fra før at vi satte CS lav og så høy først og sist i alle mcp-funksjonene også gjorde vi det inni SPI_send også, så det ble dobbelt opp
/*
Var tydeligvis dette som var problemet, fyyyyyyyyyyyyYYYYY aah. jaja. Kommenterte ut set_SS inni read-funksjonen og da var det good
Virker som at SPDR ikke alltid får med seg all dataen (alle bitene) fordi CS settes høy før den er "ferdig", aner ikke hvorfor den gjør det, men er nå sånn det virker


Skjedde noe rart på slutten, jobbet i SPI, også plutselig ville den ikke flashe når jeg kjørte can_test i main med mindre jeg kommenterte ut multifunction_init
Den kjørte derimot hvis jeg kjørte SPDR_test. Den ble også stuck i en evig loop virket det som og bare printet "Start test:" i det uendelige, altså den kjørte alt som var over multifunction_init i main, veldig rart 

I tillegg ble menyen litt fakka, men kjørte den ikke, så var kanskje det
*/