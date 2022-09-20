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
	xmem_init();
	adc_init();
	printf("start");
while(1){
	
	
	joy_print_state();
	_delay_ms(1000);
	}
	
	
	
	
/*
	printf("%d", PA1);
	printf("%d", PA2);
	printf("%d", PA3);
	printf("%d", PA4);
	printf("%d", PA5);
	printf("%d", PA6);
	printf("%d", PA7);*/
/*
	int data[8] = {PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7};
	int data2[3] = {1, 2, 3};
	int tall = 0;
	for(int i = 0, i < 3, i++)
	{
		printf("%d", data2[i]);
	}*/
	//printf("%d", data2);

}


	/*xmem_init();
	SRAM_test();
	NAND_test();
	printf("Hei");
	uart_test();
	pina_test();*/
	
	/*DDRA = 0x01;
	PORTA = 0x01;*/
	
	
	// et eller annet greier
	/*DDRD |= (1 << DDD6);	// sette bit 6 på port D til output, write-signalet
	PORTD &= ~(1 << 6);		// sette WR lavt
	
	
	DDRA = 0xFF;		// setter alle PINs på PORTA til output
	DDRC |= 0x0F;		// setter de 4 første PINs-ene på PORTC til output. Vet ikke hva disse JTAG greiene er, så bruker OR=
	
	PORTA = 0x10;
	PORTC = 0x14;
	
	// setter WR høy så ADCen kan jobbe (konvertere fra analogt til digitalt signal)
	PORTD |= (1 << PD6);
	
	// setter RD lav
	DDRD |= (1 << DDD7);	// sette bit 7 på port D til output, read-signalet
	PORTD &= ~(1 << PD7);
	

	printf("%d", PORTA);
	*/