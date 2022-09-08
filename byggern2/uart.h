/*
 * uart.h
 *
 * Created: 07.09.2022 09:53:08
 *  Author: ingebobl
 */ 

#pragma once
#include <avr/io.h>
//#include <util/delay.h>

#define FOSC 4915200 //Clock Speed
#define BAUDRATE 9600
#define MYUBRR FOSC/16/BAUDRATE - 1 //Asynchronous normal mode (31)

/*
#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg , bit ) ( reg &= ~( 1 << bit ) ) //Setter et gitt bit til 0
#define test_bit( reg , bit ) ( reg & ( 1 << bit ) )
#define loop_until_bit_is_set( reg , bit ) while ( ! test_bit ( reg , bit ) )
#define loop_until_bit_is_clear( reg , bit ) while ( test_bit ( reg , bit ) )*/

void uart_init(unsigned int ubrr);
void uart_write(unsigned char letter);
unsigned char uart_read();



