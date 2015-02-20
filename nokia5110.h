#ifndef NOKIA5110_H
#define NOKIA5110_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {	/* Use C library with Arduino */
#endif

enum char_info {
	ASCII_CHAR_WIDTH = 5,
};

enum screen_info {
	LCD_WIDTH = 84,
	LCD_HEIGHT = 48,
	LCD_MAX_X = LCD_WIDTH,
	LCD_MAX_Y = LCD_HEIGHT / 8,
	LCD_WIDTH_CHARS = LCD_WIDTH / (ASCII_CHAR_WIDTH + 1),
	LCD_MAX_TEXT = LCD_WIDTH_CHARS * LCD_MAX_Y,
};

void lcd_clear(void);
void lcd_init(void);
void lcd_contrast(byte);
void lcd_light(byte);
void lcd_write(char const *, byte, byte);
void lcd_write_anim(char const *, byte, byte);
void lcd_write_wrap(char const *, byte, byte);
void lcd_write_wrap_anim(char const *, byte, byte);

#ifdef __cplusplus
}
#endif

#endif
