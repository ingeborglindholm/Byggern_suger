
/*
 * menu.c
 *
 * Created: 29.09.2022 13:11:48
 *  Author: ingebobl
 */ 

#include "menu.h"

int arrow_page = 1; 

void menu_init(Menu menu_x){
	printf("inni menu init");
	//OLED_init();
	printf("reset");
	OLED_reset();
	
	for (int i = 0; i < menu_x.length; i++){
		OLED_pos(i, 16);
		OLED_print_string(menu_x.choices[i]);
	}
	print_solid_circle(arrow_page, 0);
	
}

void update_arrow(){
	Joy_state joy_state = get_joy_state();
	enum Direction direction = joy_state.dir;
	
	switch (direction) {
		case UP:
			if (arrow_page != 1){
				arrow_page--;
				break;
			} else break;
		case DOWN:
			if (arrow_page != 7){
				arrow_page++;
			} else break;
		default:
			break;
	}
	
	for (int page = 1; page < 8; page++) {
		for (int col = 0; col < 16; col++) {
			OLED_pos(page, col);
			OLED_write_data(0b00000000);
		}
	}
	print_solid_circle(arrow_page, 0);
	//OLED_print_arrow(arrow_page, 0);
}
	int get_menu_choice(){
		return arrow_page;
	}

/*
void update_current_menu(page current_page){
	switch (current_page){
		case PAGE0:
		
		break;
		case PAGE1:
		break;
		case PAGE2:
		break;
		case PAGE3:
			current_menu = tabata_menu;
		break;
		case PAGE4:
		break;
		case PAGE5:
		break;
		case PAGE6:
		break;
		case PAGE7:
		break;
		default:
		break;
	}
}*/