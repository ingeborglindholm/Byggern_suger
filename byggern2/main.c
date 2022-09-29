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
	multifunction_init();
	
	printf("Start test: ");
	while (1){
		_delay_ms(1000);
		update_arrow();
		
		printf("Port B: %d", PINB);
		
		if (joy_btn_pressed()){
			printf("Menu choice: %d", get_menu_choice());
		}
	}
	
}