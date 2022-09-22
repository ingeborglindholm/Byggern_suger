
/*
 * multifunciton.c
 *
 * Created: 15.09.2022 12:45:52
 *  Author: ingebobl
 */ 

#include "multifunction.h"
#include <math.h>

#define PI 3.14159265

void adc_init (void){	DDRD |= (1 << DDD5); //Set PD5 to output		TCCR1A |= (1 << WGM10); //Fast PWM mode	TCCR1A |= (1 << WGM11); //Fast PWM mode	TCCR1B |= (1 << WGM12); //Fast PWM mode	TCCR1B |= (1 << WGM13); //Fast PWM mode		TCCR1A &= ~(1 << COM1A1); // Toggle	TCCR1A |= (1 << COM1A0); //Toggle		TCCR1B &= ~(1 << CS12); //Clock select bit	TCCR1B &= ~(1 << CS11); //Clock select bit	TCCR1B |= (1 << CS10); //Clock select bit		TCCR1A &= ~(1 << FOC1A); // Had to be zero		OCR1AH = 0x0;	OCR1AL = 0x1;		DDRD &= ~(1 << DDD4); // Set PD4 to input		uint8_t* x_pos_offset = (BASE_ADDRESS + ADDRESS_SRAM + 4); // Plusser på 4 fordi på denne minneadressen skal vi lagre en float, som tar opp 4 bytes, altså må vi ha 4 minneaddresser
	*x_pos_offset = 0;
	uint8_t* y_pos_offset = (BASE_ADDRESS + ADDRESS_SRAM + 8); 
	*y_pos_offset = 0;		calibrate_joy_stick();}ADC_output adc_read(){
	volatile uint8_t *ADC_data = (uint8_t *) (BASE_ADDRESS + ADDRESS_ADC); // ADC_data er en peker til port A der dataen fra ADCen blir lagt ut
	ADC_data[0] = 0;
	
	while((PORTD &= 0x10))		// busy er PD4, venter altså på 0b010000 = 0x10. Bit 5 (PD4) skal bli 1, da er busy høy
	{
		// Venter på at busy blir høy, da er den klar til å hente ut data
	}
	
	uint8_t data_channel_0 = ADC_data[0];		// x-axis 
	uint8_t data_channel_1 = ADC_data[0];		// y-axis
	uint8_t data_channel_2 = ADC_data[0];		// Right slider
	uint8_t data_channel_3 = ADC_data[0];		// Left slider
	
	return (ADC_output){data_channel_0, data_channel_1, data_channel_2, data_channel_3};
}

int to_percent(uint8_t pos_in_bit){
	return (int)pos_in_bit  * ((float)200) / ((float)256) - 100;		// Skalering: hele bredden er 200% med 0% i midten og -100% og 100% i hver sin ende
}

void calibrate_joy_stick(){
	ADC_output adc_output = adc_read();
	uint8_t x = adc_output.x_axis;
	uint8_t y = adc_output.y_axis;
	
	uint8_t* x_pos_offset = (uint8_t)(BASE_ADDRESS + ADDRESS_SRAM + 4); 
	*x_pos_offset = x;
	uint8_t* y_pos_offset = (BASE_ADDRESS + ADDRESS_SRAM + 8);
	*y_pos_offset = y;
	
}

enum Direction joy_get_dir(int x, int y){
	enum Direction dir;
	
	uint8_t* x_pos_offset = (BASE_ADDRESS + ADDRESS_SRAM + 4);
	uint8_t* y_pos_offset = (BASE_ADDRESS + ADDRESS_SRAM + 8);
	int x_offset_percent = to_percent(*x_pos_offset);
	int y_offset_percent = to_percent(*y_pos_offset);
	
	if (((x_offset_percent -5) < x && x < (x_offset_percent + 5)) && ((y_offset_percent - 5) < y && y < (y_offset_percent + 5))){
		dir = NEUTRAL;
	} else{
		double angle = atan2((double) y, (double) x);
		
		if (angle > PI/4 && angle <= 3*PI/4){
			dir = UP;
		}
		else if ((angle > 3*PI/4 && angle <= PI) || (angle <= -3*PI/4 && angle > -PI)){
			dir = LEFT;
		}
		else if (angle > -3*PI/4 &&  angle <= -PI/4 ){
			dir = DOWN;
		}
		else if (angle > -PI/4 && angle <= PI/4){
			dir = RIGHT;
		}
	}
	return dir;
}

Joy_state get_joy_state(){
	ADC_output adc_output = adc_read();
	int x_percent = to_percent(adc_output.x_axis);
	int y_percent = to_percent(adc_output.y_axis);
	
	enum Direction dir = joy_get_dir(x_percent, y_percent);
	
	return (Joy_state){x_percent, y_percent, dir};
	}

void joy_print_state() {
	Joy_state state = get_joy_state();
	printf("x = %d, y = %d and dir = %d\n", state.x_percent, state.y_percent, state.dir);
}

Slider_state print_slider_state(){
	ADC_output adc_output = adc_read();
	printf("Left slider: %d, right slider: %d \n", adc_output.left_slider, adc_output.right_slider);
}























/*
input_position ADC_pos_read(void) {

	uint8_t* x_pos = (BASE_ADDRESS + ADDRESS_SRAM + 4);
	uint8_t* y_pos = (BASE_ADDRESS + ADDRESS_SRAM + 8);
	
	ADC_output input = adc_read();

	float k = 200/256;	// 
	float x_pos_float = (float) input.x_axis;	// Caster til float
	float x_pos_percent = x_pos_float*k; // Har en desimalverdi for prosent
	int x_pos_percent_int = (int)x_pos_percent - 100 - *x_pos; // Caster prosentverdien til int samtidig som vi trekker fra offset
	
	float y_pos_float = (float) input.y_axis;
	float y_pos_percent = y_pos_float*k;
	int y_pos_percent_int = (int) y_pos_percent - 100 - *y_pos;
	
	float left_pos_float = (float) input.left_slider;
	float left_pos_percent = left_pos_float*k/2;
	int left_pos_percent_int = (int) left_pos_percent - 100;
	
	float right_pos_float = (float) input.right_slider;
	float right_pos_percent = right_pos_float*k/2;
	int right_pos_percent_int = (int) right_pos_percent;

	input_position pos = {x_pos_percent_int,y_pos_percent_int, left_pos_percent_int, right_pos_percent_int};
	return pos;
}

void adc_calibrate(){
	uint8_t* x_pos = (BASE_ADDRESS + ADDRESS_SRAM + 4);
	uint8_t* y_pos = (BASE_ADDRESS + ADDRESS_SRAM + 8);
	input_position calibration = ADC_pos_read();
	*x_pos = calibration.x_pos;
	*y_pos = calibration.y_pos;
}*/

/*
pos_t pos_read(void){
	
}*/