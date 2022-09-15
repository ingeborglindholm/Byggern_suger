/*
 * test.c
 *
 * Created: 08.09.2022 10:29:18
 *  Author: martge
 */ 

#include "test.h"
#include <stdlib.h>

void pina_test(){
	while (1) {
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
}


void latch_test(){
	//Sette output
	DDRA = 0x01;
	DDRE |= 1 << DDE1;
	
		PORTA = 0x01;
		PORTE = 1 << PE1;
	
		_delay_ms(1000); 
	
		PORTE = 0; 
		PORTA = 0x00;
		
		_delay_ms(1000);
		PORTA = 0x01; 
		_delay_ms(1000);
		PORTA = 0x00;
		PORTE = 1 << PE1; 

}

void SRAM_test(void) {
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			write_errors++;
		}
		/*else{
			printf("Success!: ext_ram[%4d] = %02X", i, retreived_value);
		}*/
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}

void NAND_test(void) {

	DDRA = 0xFF;		// setter alle PINs på PORTA til output

	DDRC |= 0x0F;		// setter de 4 første PINs-ene på PORTC til output. Vet ikke hva disse JTAG greiene er, så bruker OR=
	
	//sette en adresse som er i adresseområdet vi vil teste
	//PORTA er de 8 LSB og i disse tre eksemplene er de alle 0. Bare sett en av adressene av gangen
	PORTA = 0x00;
	// 0x1000 er OLED
	//PORTC = 0x10;
	
	// 0x1400 er ADC
	PORTC = 0x14;
	
	// 0x1800 er SRAM
	//PORTC = 0x18;
	
	/*PD6 = 1 (WR)
	
	
	*/
	
	
}