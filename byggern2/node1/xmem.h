/*
 * xmem.h
 *
 * Created: 08.09.2022 15:17:42
 *  Author: martge
 */ 
#pragma once

#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef BASE_ADDRESS
#define BASE_ADDRESS 0x1000
#endif

#ifndef ADDRESS_SRAM
#define ADDRESS_SRAM 0x1800
#endif

#ifndef ADDRESS_ADC
#define ADDRESS_ADC 0x1400
#endif

#ifndef ADDRESS_OLED_COMMAND
#define ADDRESS_OLED_COMMAND 0x1000
#endif

#ifndef ADDRESS_OLED_DATA
#define ADDRESS_OLED_DATA 0x1200
#endif

void xmem_init ( void );

void xmem_write ( uint8_t data , uint16_t addr );

uint8_t xmem_read ( uint16_t addr );