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
#include "Multifunc_board/multifunction.h"
#include "CAN_controller/spi_driver.h"

int main(void){
	uart_init(MYUBRR);
	xmem_init(); 
	
	multifunction_init();
	printf("Start test: \n\r");
	
	/*
	SPI_init();
	while(1){
		SPI_send(0b01011111);
		//SPI_send(0b11111111);
		//uint8_t x = SPDR;
		uint8_t x = SPI_read();
		printf("Look at this: %d\n", x);
	}
	*/
	can_test();
}

/*
- Sjekket at SCK og SI fungerer som de skal, SO er en trapp/et funky signal.	
	* Verifisere at det g�r fint 
	
- Pr�ver � kj�re CAN_test (send noe og les det tilbake, print til skjerm.) 
	- Det stopper opp fordi vi tilsynelatende ikke er i config_mode. Mest sannsynlig er det noe feil med read, ikke moden 
	- SPI_read/send er like som emil sine, det er ogs� MCP2515 read/write 
	
	



*/