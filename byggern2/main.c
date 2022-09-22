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
#include "xmem.h"
#include "multifunction.h"

int main(void){
	uart_init(MYUBRR);
	
	xmem_init();
	adc_init();
	printf("Start: ");
	
	while(1){
		joy_print_state();
		print_slider_state();
		_delay_ms(1000);
	}
}