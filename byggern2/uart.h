/*
 * uart.h
 *
 * Created: 07.09.2022 09:53:08
 *  Author: ingebobl
 */ 

#pragma once

#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg , bit ) ( reg &= ~( 1 << bit ) ) //Setter et gitt bit til 0
#define test_bit( reg , bit ) ( reg & ( 1 << bit ) )
#define loop_until_bit_is_set( reg , bit ) while ( ! test_bit ( reg , bit ) )
#define loop_until_bit_is_clear( reg , bit ) while ( test_bit ( reg , bit ) )
/*
int uart_read();

void uart_write(char letter);

void uart_init(unsigned int ubrr);

void uart_test(unsigned int ubrr);

*/
void uart_init(unsigned int ubrr);


/**
 * @brief Tranmits @p data to the MCU.
 * 
 * @param data 8-bit value to be tranmitted.
 */
void uart_transmit(unsigned char data);


/**
 * @brief Recieves data from the MCU.
 * 
 * @return 8-bit value recieved from the MCU.
 */
unsigned char uart_recieve();


/**
 * @brief Links the @c printf() function to the uart module. 
 */
void uart_link_printf();


#endif 