/*
 * sram.h
 *
 * Created: 08.09.2022 15:17:42
 *  Author: martge
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>

void xmem_init ( void );

void xmem_write ( uint8_t data , uint16_t addr );

uint8_t xmem_read ( uint16_t addr );