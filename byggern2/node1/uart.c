/*
 * uart.c
 *
 * Created: 07.09.2022 08:35:22
 *  Author: ingebobl
 */ 

#include "uart.h"

void uart_init(unsigned int ubrr){
	//Set baud rate, divided into two registers
	UBRR0H = (unsigned char)(ubrr>>8); //high register, alt f�r egt plass p� 8 bit s� derfor blir det 0
	UBRR0L = (unsigned char)ubrr; //low register
				
	/* Enable receiver and transmitter 
	hvor mange bit data: man kan ha 5-9 bit, vi vil ha 8
	hvor mange stop-bit: 2 stk, pga ignorerer det f�rste bitet*/
			
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << URSEL0)|(1<< USBS0)|(3 << UCSZ00);
	
	fdevopen(uart_write, uart_read);
}

void uart_write(unsigned char letter){
	/*1. Sjekke om det er klart til � sende ny data
	2. sende ny data*/
	 
	while(!(UCSR0A & (1<<UDRE0))){
		
	}
	UDR0 = letter;
}

unsigned char uart_read(){
	while (!(UCSR0A & (1 << RXC0))){
		
	}
	return UDR0;
}

