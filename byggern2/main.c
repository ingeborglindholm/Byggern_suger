/*
 * main
 
 *
 * Created: 31.08.2022 15:57:45
 * Author : martge
 */ 

#include "uart.h"

#define FOSC 4915200 //Clock Speed
#define BAUDRATE 9600
#define MYUBRR FOSC/(16*BAUDRATE) - 1 //Asynchronous normal mode (31)

int main(void)
{	//Sette riktige innstillinger for å få output fra ICen 
	DDRA = 0x01;
	PORTA = PORTA||0x01;
	
	while(1){
		
		_delay_ms(100);
		//uart_write('a');
		uart_test(MYUBRR);
	}
	
}
/*while (1) {
	_delay_ms(1000);
	PORTA ^= 0x01;
}*/
