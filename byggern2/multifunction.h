
/*
 * multifunction.h
 *
 * Created: 15.09.2022 12:46:03
 *  Author: ingebobl
 */ 

#include <avr/io.h>
#include <stdio.h>

#include "xmem.h"

enum Direction {LEFT=0, RIGHT=1, UP=2, DOWN=3, NEUTRAL=4, UNKNOWN= 5};

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
	uint8_t right_slider;
	uint8_t left_slider;
} ADC_output;


void adc_init (void);