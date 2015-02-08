#ifndef _NOKIA5110_H
#define _NOKIA5110_H

#include <Arduino.h>

enum {
	LCD_C = LOW,
	LCD_D = HIGH,
};

enum screen {
	LCD_MAX_X = 84,
	LCD_MAX_Y = 48,
};

void lcdCharacter(char);
void lcdClear(void);
void lcdInitialize(void);
void lcdString(char *);
void lcdWrite(byte, byte);

#endif
