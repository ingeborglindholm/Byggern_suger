
/*
 * adc.c
 *
 * Created: 15.09.2022 12:45:52
 *  Author: ingebobl
 */ 

#include "adc.h"

void adc_init (void){	DDRD |= (1 << DDD5); //Set PD5 to output		TCCR1A |= (1 << WGM10); //Fast PWM mode	TCCR1A |= (1 << WGM11); //Fast PWM mode	TCCR1B |= (1 << WGM12); //Fast PWM mode	TCCR1B |= (1 << WGM13); //Fast PWM mode		TCCR1A &= ~(1 << COM1A1); // Toggle	TCCR1A |= (1 << COM1A0); //Toggle		TCCR1B &= ~(1 << CS12); //Clock select bit	TCCR1B &= ~(1 << CS11); //Clock select bit	TCCR1B |= (1 << CS10); //Clock select bit		TCCR1A &= ~(1 << FOC1A); // Had to be zero}uint8_t adc_read(uint8_t channel){ //volatile
}

void adc_calibrate(){
	
}

/*
pos_t pos_read(void){
	
}*/