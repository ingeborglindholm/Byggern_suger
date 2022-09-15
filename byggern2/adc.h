
/*
 * adc.h
 *
 * Created: 15.09.2022 12:46:03
 *  Author: ingebobl
 */ 

#include <avr/io.h>

void adc_init (void);uint8_t adc_read(uint8_t channel); //volatile

void adc_calibrate();

//pos_t pos_read(void);