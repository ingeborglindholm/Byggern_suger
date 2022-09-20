
/*
 * adc.h
 *
 * Created: 15.09.2022 12:46:03
 *  Author: ingebobl
 */ 

#include <avr/io.h>
#include "sram.h"

enum Direction {LEFT, RIGHT, UP, DOWN, NEUTRAL};

typedef struct  
{
	int x_percent;
	int y_percent;
	enum Direction dir;
}Joy_state;


typedef struct  
{
	int left;
	int right;
} Slider_state;


typedef struct  
{
	uint8_t x_axis;
	uint8_t y_axis;
	uint8_t left_slider;
	uint8_t right_slider;
} ADC_output;


void adc_init (void);
uint8_t adc_read(uint8_t channel); //volatile

input_position ADC_pos_read(void);

void adc_calibrate();*/

//pos_t pos_read(void);