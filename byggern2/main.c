/*
 * main.c
 
 *
 * Created: 31.08.2022 15:57:45
 * Author : martge
 */ 
#include <avr/io.h>
#include <stdio.h>

#include "uart.h"
#include "test.h"


int main(void)
{	uart_init(MYUBRR);
	fdevopen(uart_write, uart_read);
	SRAM_test();
	
}

