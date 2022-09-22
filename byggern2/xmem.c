/*
 * xmem.c
 *
 * Created: 08.09.2022 15:16:59
 *  Author: martge
 */
 
#include "xmem.h"

void xmem_init ( void ){
	MCUCR |= (1 << SRE ); // enable XMEM
	SFIOR |= (1 << XMM2 ); // fjerner JTAG-bitsene fra external memory address, se side 32 i ATmega datablad
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
