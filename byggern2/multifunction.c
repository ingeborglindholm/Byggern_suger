
/*
 * multifunction.c
 *
 * Created: 29.09.2022 13:52:13
 *  Author: ingebobl
 */ 

#include "multifunction.h"

void multifunction_init(){
	adc_init();
	//Joy-stick button:
	DDRB &= ~(1 << DDB7); //Sette PB7 til input
	PORTB |= (1 << PINB7);
	
	calibrate_joy_stick();
	
	//Legge til initialisering av sliderknappene
	
	OLED_init();
	
	Menu main_menu = {
		{"* Menu *", "Valg 1", "Valg 2", "Tabata", "x", "x", "x", "y"},
		8
	};
	
	Menu current_menu = main_menu;
	
	
	menu_init(main_menu);
}