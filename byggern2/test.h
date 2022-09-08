/*
 * test.h
 *
 * Created: 08.09.2022 10:29:29
 *  Author: martge
 */ 


#pragma once

#include <avr/io.h>
#define F_CPU 4.9152E6
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"

void pina_test();

void uart_test();

void latch_test();

void SRAM_test(void);