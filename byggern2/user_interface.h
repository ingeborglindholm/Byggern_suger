
/*
 * user_interface.h
 *
 * Created: 15.09.2022 12:46:03
 *  Author: ingebobl
 */ 

#pragma once

#include <avr/io.h>
#include <stdio.h>
#include <math.h>

#include "xmem.h"

#define PI 3.14159265

enum Direction {LEFT=0, RIGHT=1, UP=2, DOWN=3, NEUTRAL=4};

typedef struct  
{
	int x_percent;
	int y_percent;
	enum Direction dir;
} Joy_state;


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


void adc_init (void);ADC_output adc_read();void calibrate_joy_stick();int to_percent(uint8_t i);enum Direction joy_get_dir(int x, int y);Joy_state get_joy_state();int joy_btn_pressed();void joy_print_state();void print_slider_state();