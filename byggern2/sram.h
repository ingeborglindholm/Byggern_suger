/*
 * sram.h
 *
 * Created: 08.09.2022 15:17:42
 *  Author: martge
 */ 
#pragma once

#ifndef BASE_ADDRESS
#define BASE_ADDRESS 0x1000
#endif

#ifndef ADDRESS_SRAM
#define ADDRESS_SRAM 0x800
#endif

#ifndef ADDRESS_ADC
#define ADDRESS_ADC 0x400
#endif

#ifndef ADDRESS_OLED
#define ADDRESS_OLED 0x200
#endif


#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>

void xmem_init ( void );

void xmem_write ( uint8_t data , uint16_t addr );

uint8_t xmem_read ( uint16_t addr );