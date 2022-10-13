/*
 * main.c
 
 *
 * Created: 31.08.2022 15:57:45
 * Author : martge
 */ 

#include <avr/io.h>
#include <stdio.h>

#include "node1/uart.h"
#include "node1/test.h"
#include "node1/xmem.h"
#include "node1/Multifunc_board/multifunction.h"
#include "node1/CAN_controller/can_driver.h"


int main(void){
	uart_init(MYUBRR);
	printf("\r\n\n\n\nStart test: \n\r");
	xmem_init(); 
	
	multifunction_init();
	can_test();
	
	
	SPDR_test();
	
	
	printf("\r\n\n\nSlutt test: \n\r");		// \r gjør at man i putty begynner på neste linje (tabber ut linjen)
	
	
/*
	
	while (1){
		_delay_ms(100);
		update_arrow();
		
		if (joy_btn_pressed()){
			printf("Menu choice: %d\n", get_menu_choice());
		}
	}
	*/
	
	
}

/*
- Sjekket at SCK og SI fungerer som de skal, SO er en trapp/et funky signal.	
	* Verifisere at det går fint 
	
- Prøver å kjøre CAN_test (send noe og les det tilbake, print til skjerm.) 
	- Det stopper opp fordi vi tilsynelatende ikke er i config_mode. Mest sannsynlig er det noe feil med read, ikke moden 
	- SPI_read/send er like som emil sine, det er også MCP2515 read/write 
	
	
Spør studass: er det mening at man skal kunne printe SPDR?? det blir 0 uansett og dermed blir value i mcp_init lik 0 og dermed
får vi at vi ikke er i config-mode


Enten så er value faktisk 0, som betyr at SPI_send ikke fungerer
Eller så blir value 0 fordi SPI_read ikke funker

Update: SPDR er 0, det får aldri en verdi, så da er det ikke så rart at det vi leser fra SPDR også er 0...

OBSOBS!!!!!!!!!!!!!!!!!!!!
Bruk 2043 på Arduino, Jan og Luan brukte feil og fant ikke Arduinoen på PC-en

84MHz MCK Arduino master clock
*/


	/*SPI_init();
	while(1){
		SPI_send(0b01011111);
		//SPI_send(0b11111111);
		//uint8_t x = SPDR;
		uint8_t x = SPI_read();
		printf("Look at this: %d\n", x);
	}*/