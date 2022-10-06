
/*
 * spi_driver.S
 *
 * Created: 05.10.2022 14:40:35
 *  Author: martge
 */ 

#pragma once

#include <avr/io.h>



void SPI_init();

void set_SS_low();

void set_SS_high();

void SPI_send(uint8_t data);

uint8_t SPI_read();

