
/*
 * menu.h
 *
 * Created: 29.09.2022 13:11:59
 *  Author: ingebobl
 */ 

#pragma once

#include "oled.h"
#include "user_interface.h"

typedef struct{
	char choices[8][16];
	int length;
	} Menu;



typedef enum{
	PAGE0, PAGE1, PAGE2, PAGE3, PAGE4, PAGE5, PAGE6, PAGE7,
	}page;

void menu_init(Menu menu_x);

void update_arrow();

int get_menu_choice();

void update_current_menu(page current_page); 

/*
enum med pages 

Vi må ha menyen i switch-casen, ikke pages
Tanken var: i main
while (1){
	if (joy_btn_pressed)
		switch (case)
			case 1: 
				clear screen, print choice 1
			case 2: 
				clear ....
			
			default
		
}

Alternativ løsning: prøve å se på det med lenkede lister 

*/
