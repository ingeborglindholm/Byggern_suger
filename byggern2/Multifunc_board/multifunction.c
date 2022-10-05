
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
	PORTB |= (1 << PINB0);
	
	calibrate_joy_stick();
	
	//Legge til initialisering av sliderknappene
	
	OLED_init();
	
	Menu main_menu = {
		{"* Menu *", "Maxe-mandag", "Pirbadet", "Tabata", "Cava-søndag", "Byggern lab", "x", "y"},
		8
	};
	/* Menu tabata_menu = {
		.choices = {"Tabataka boom", "Tabtata", "Tabayta", "Tabratata", "Feliz Tabatad"},
		.length = 5
	};*/
	
	Menu current_menu = main_menu;
	menu_init(main_menu);
}