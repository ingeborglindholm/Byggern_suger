/*
 * sram.c
 *
 * Created: 08.09.2022 15:16:59
 *  Author: martge
  

#include "sram.h"

#define BASE_ADDRESS 

void xmem_init ( void ){
	MCUCR |= (1 << SRE ); // enable XMEM
	SFIOR |= (1 << XMM0 ); // mask unused bits
}

void xmem_write ( uint8_t data , uint16_t addr ){
	volatile char * ext_mem = ( char *) BASE_ADDRESS ;
	ext_mem [ addr ]= data ;
}

uint8_t xmem_read (uint16_t addr ){
	volatile char * ext_mem = ( char *) BASE_ADDRESS ;
	uint8_t ret_val = ext_mem [ addr ];
	return ret_val ;
}
*/
