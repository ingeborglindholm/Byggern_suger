/*
 * uart.h
 *
 * Created: 07.09.2022 09:53:08
 *  Author: ingebobl
 */ 

#pragma once
#include <avr/io.h>

#define FOSC 4915200 //Clock Speed
#define BAUDRATE 9600
#define MYUBRR FOSC/16/BAUDRATE - 1 //Asynchronous normal mode (31)

void uart_init(unsigned int ubrr);
void uart_write(unsigned char letter);
unsigned char uart_read();



