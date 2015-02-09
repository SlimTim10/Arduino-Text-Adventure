#ifndef _NOKIA5110_H
#define _NOKIA5110_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {	// Use C library with Arduino
#endif

enum {
	LCD_C = LOW,
	LCD_D = HIGH,
};

enum screen {
	LCD_WIDTH = 84,
	LCD_HEIGHT = 48,
	LCD_MAX_X = LCD_WIDTH,
	LCD_MAX_Y = LCD_HEIGHT / 8,
};

enum char_info {
	ASCII_CHAR_WIDTH = 5,
};

enum lcd_instructions {
	LCD_SET_Y = 0x40,
	LCD_SET_X = 0x80,
};

void lcdCharacter(char);
void lcdSetPos(byte x, byte y);
void lcdClear(void);
void lcdInitialize(void);
void lcdString(char const *, byte, byte);
void lcdCmd(byte);
void lcdData(byte);

#ifdef __cplusplus
}
#endif

#endif
