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
#include "sram.h"
#include "adc.h"


int main(void)
{	uart_init(MYUBRR);
	fdevopen(uart_write, uart_read);
	/*xmem_init();
	SRAM_test();*/
	//NAND_test();
	//printf("Hei");
	//uart_test();
	//pina_test();
	/*DDRA = 0x01;
	PORTA = 0x01;*/
	adc_init();
}

