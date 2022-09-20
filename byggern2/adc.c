
/*
 * adc.c
 *
 * Created: 15.09.2022 12:45:52
 *  Author: ingebobl
 */ 

#include "adc.h"
#include <math.h>

#define PI 3.14159265

void adc_init (void){	DDRD |= (1 << DDD5); //Set PD5 to output		TCCR1A |= (1 << WGM10); //Fast PWM mode	TCCR1A |= (1 << WGM11); //Fast PWM mode	TCCR1B |= (1 << WGM12); //Fast PWM mode	TCCR1B |= (1 << WGM13); //Fast PWM mode		TCCR1A &= ~(1 << COM1A1); // Toggle	TCCR1A |= (1 << COM1A0); //Toggle		TCCR1B &= ~(1 << CS12); //Clock select bit	TCCR1B &= ~(1 << CS11); //Clock select bit	TCCR1B |= (1 << CS10); //Clock select bit		TCCR1A &= ~(1 << FOC1A); // Had to be zero		OCR1AH = 0x0;	OCR1AL = 0x1;		DDRD &= ~(1 << DDD4); // set PD4 to input		uint8_t* x_pos_offset = (BASE_ADDRESS + ADDRESS_SRAM + 4); // plusser på 4 fordi på denne minneadressen skal vi lagre en float, som tar opp 4 bytes, altså må vi ha 4 minneaddresser
	*x_pos_offset = 0;
	uint8_t* y_pos_offset = (BASE_ADDRESS + ADDRESS_SRAM + 8); 
	*y_pos_offset = 0;}ADC_output adc_read(){
	//volatile uint8_t *ADC_data = (uint8_t *) (BASE_ADDRESS + ADDRESS_ADC);
	volatile char *ADC_data = (char *)(BASE_ADDRESS + ADDRESS_ADC);		// ADC_data er en peker til port A der dataen fra ADCen blir lagt ut
	
	ADC_data[0]=0;
	
	while((PORTD &= 0x10))		// busy er PD4, venter altså på 0b010000 = 0x10. Bit 5 (PD4) skal bli 1, da er busy høy
	{
		// Venter på at busy blir høy
	}
	
	// kan nå hente ut dataen
	uint8_t data_channel_0 = ADC_data[0];
	uint8_t data_channel_1 = ADC_data[0];
	uint8_t data_channel_2 = ADC_data[0];
	uint8_t data_channel_3 = ADC_data[0];
	
	
	return (ADC_output){data_channel_0, data_channel_1, data_channel_2, data_channel_3};
}

int to_percent(uint8_t pos_in_bit){
	
	if(pos_in_bit > 156){
		return (int)(pos_in_bit - 156)/(99) *100;
	}
	else{
		return (int)(pos_in_bit /156)*100 - 100;
	}
	
	//return (int)pos_in_bit  * ((float)200) / ((float)256) - 100;		// skalering: hele bredden er 200% med 0% i midten og -100% og 100% i hver sin ende
}

void calibrate_joyStick(){
	ADC_output adc_output = adc_read();
	uint8_t x = adc_output.x_axis;
	uint8_t y = adc_output.y_axis;
	
	
}

enum Direction joy_get_dir(int x, int y){
	enum Direction dir;
	
	if (x == 0 && y == 0){
		dir = NEUTRAL;
	}
	else{
		double angle = atan2((double) y, (double) x);
		
		if (angle > PI/4 && angle <= 3*PI/4){
			dir = UP;
		}
		if (angle > 3*PI/4 && angle <= 5*PI/4){
			dir = LEFT;
		}
		if (angle > 5*PI/4 && angle <= 7*PI/4){
			dir = DOWN;
		}
		if (angle > 7*PI/4 && angle <= PI/4){
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
	
	printf("x = %d  og  y = %d     ", state.x_percent, state.y_percent);
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