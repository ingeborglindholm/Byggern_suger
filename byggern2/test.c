/*
 * test.c
 *
 * Created: 08.09.2022 10:29:18
 *  Author: martge
 */ 

#include "test.h"

void pina_test(){
	*while (1) {
	_delay_ms(1000);
	PORTA ^= 0x01;
	}
}

void uart_test(){
	uart_init(MYUBRR);
	fdevopen(uart_write, uart_read);
	
	while(1){
		uart_write(uart_read()+1);
		_delay_ms(1000);
		//printf("Nå funker det!!");
	}
	
	//uart_write(uart_read() + 1);
}
