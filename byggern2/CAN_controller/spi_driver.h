
/*
 * spi_driver.S
 *
 * Created: 05.10.2022 14:40:35
 *  Author: martge
 */ 

#pragma once

#include <avr/io.h>


void SPI_init();

void SPI_send(uint8_t data);

uint8_t SPI_read();

