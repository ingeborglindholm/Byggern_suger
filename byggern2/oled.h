
/*
 * oled.h
 *
 * Created: 22.09.2022 10:40:33
 *  Author: ingebobl
 */ 
#pragma once

#include <avr/io.h>
#include <stdio.h>
#include <string.h>

#include "xmem.h"
#include "uart.h"

//#define FDEV_SETUP_STREAM(, , _FDEV_SETUP_READ)

void OLED_write_command(uint8_t cmd);

void OLED_init();

void OLED_write_data(uint8_t c); //volatile

void OLED_pos(uint8_t page, uint8_t column);

void OLED_print_arrow (uint8_t page, uint8_t col);

void print_solid_circle(uint8_t page, uint8_t col);

void OLED_clear_line(uint8_t page);

void OLED_reset();

int OLED_goto_line(uint8_t page);

void OLED_print_char(char* c);

void OLED_print_string(char str[]);

/*
OLED_goto_line(line);

OLED_pos(row, column);
OLED_write_data(char); //volatile
OLED_print(char*);
OLED_set_brightness(lvl);
*/