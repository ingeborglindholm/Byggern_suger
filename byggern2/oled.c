
/*
 * oled.c
 *
 * Created: 22.09.2022 10:40:22
 *  Author: ingebobl
 */ 

#include "oled.h"
#include "fonts.h"

void OLED_write_command(uint8_t cmd){
	volatile uint8_t *memory = (uint8_t *)0;
	memory[ADDRESS_OLED_COMMAND] = cmd;
}

void OLED_init(){
	OLED_write_command(0xAE); // display off
	OLED_write_command(0xA1); //segment remap
	OLED_write_command(0xDA); //common pads hardware: alternative
	OLED_write_command(0x12);
	OLED_write_command(0xC8); //common output scan direction:com63~com0
	OLED_write_command(0xA8); //multiplex ration mode:63
	OLED_write_command(0x3F);
	OLED_write_command(0xD5); //display divide ratio/osc. freq. mode
	OLED_write_command(0x80);
	OLED_write_command(0x81); //contrast control
	OLED_write_command(0x50);
	OLED_write_command(0xD9); //set pre-charge period
	OLED_write_command(0x21);
	OLED_write_command(0x20); //Set Memory Addressing Mode
	OLED_write_command(0x00);		//var satt til 0x02
	OLED_write_command(0xDB); //VCOM deselect level mode
	OLED_write_command(0x30);
	OLED_write_command(0xAD); //master configuration
	OLED_write_command(0x00);
	OLED_write_command(0x40); //Set display start line (gjør at displayet ikke er forskjøvet)
	OLED_write_command(0xA4); //out follows RAM content
	OLED_write_command(0xA6); //set normal display
	OLED_write_command(0xAF); // display on
}

void OLED_write_data(uint8_t data){
	volatile uint8_t *memory = (uint8_t *)0;
	memory[ADDRESS_OLED_DATA] = data;
}

void OLED_pos(uint8_t page, uint8_t column){
	OLED_write_command(0x21);
	OLED_write_command(column);
	OLED_write_command(0x7F);
	
	OLED_write_command(0x22);
	OLED_write_command(page);
	OLED_write_command(0x07); 
}

void OLED_print_arrow (uint8_t page, uint8_t col ){
	OLED_pos (page, col);
	OLED_write_data(0b00011000);
	OLED_write_data(0b00011000);
	OLED_write_data(0b00011000);
	OLED_write_data(0b00011000);
	OLED_write_data(0b00011000);
	OLED_write_data(0b00011000);
	OLED_write_data(0b01111110);
	OLED_write_data(0b00111100);
	OLED_write_data(0b00011000);
	OLED_write_data(0b00010000);
}void print_solid_circle(uint8_t page, uint8_t col){
	OLED_pos (page, col);
	OLED_write_data(0b00011000);
	OLED_write_data(0b01111110);
	OLED_write_data(0b01111110);
	OLED_write_data(0b11111111);
	OLED_write_data(0b11111111);
	OLED_write_data(0b01111110);
	OLED_write_data(0b01111110);
	OLED_write_data(0b00011000);
}void OLED_clear_line(uint8_t page){	OLED_pos(page,0);	for (int i = 0; i < 128;i++){		OLED_write_data(0b00000000);	}}void OLED_reset(){	OLED_pos(0,0);	for (int i=0; i < 8; i++){		OLED_clear_line(i);	}	OLED_pos(0,0);}int OLED_goto_line(uint8_t page){	if (page > 7 && page < 0){		return 0;	}	OLED_pos(page, 0);	return 0;}void OLED_print_char(char* c){	unsigned char byte;	for (int i = 0; i < 8; i++){		byte = pgm_read_byte(&(font8[*c-32][i])); //Font starts on char value 32 in ASCII-table		OLED_write_data(byte);	}}void OLED_print_string(char str[]){	int length = strlen(str);	for (int i = 0; i < length; i++){		OLED_print_char(str + i);	}}