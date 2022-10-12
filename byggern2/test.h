/*
 * test.h
 *
 * Created: 08.09.2022 10:29:29
 *  Author: martge
 */ 

#pragma once

#define F_CPU 4.9152E6

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "uart.h"
#include "Multifunc_board/multifunction.h"
#include "CAN_controller/can_driver.h"

void pina_test();

void uart_test();

void latch_test();

void SRAM_test(void);

void NAND_test(void);

void test_multifunction();

void can_test();

void SPDR_test();