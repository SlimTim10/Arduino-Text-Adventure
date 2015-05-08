#include "lcd_extra.h"
#include "const.h"
#include "hal.h"
#include "PCD8544.h"
#include <string.h>

/* Control the brightness of the backlight (0: off, 255: full brightness) */
void lcd_light(uint8_t b) {
	analogWrite(LCD_PIN_LIGHT, ~b);
}

/* Write a string to the LCD, starting at the specified location, with a short delay between each character */
void lcd_printat_anim(const char *str, uint8_t x, uint8_t y) {
	lcd_setpos(x % LCD_MAX_X, y % LCD_MAX_Y);
	while (*str) {
		lcd_send_char(*str++);
		delay(TEXT_SPEED);
	}
}

/* Write a string to the LCD with word wrapping and a short delay between each character */
void lcd_printwrap_anim(const char *str, uint8_t xpos, uint8_t ypos) {
	while (*str) {
		int wraploc = LCD_MAX_X_CHARS;

		/* Check if it's short enough to write */
		if (strlen(str) <= wraploc) {
			lcd_printat_anim(str, xpos, ypos);
			return;
		}

		/* Find wrap location (first space character backwards from right margin) */
		while (str[wraploc] != ' ' && wraploc > 0) {
			wraploc--;
		}

		if (wraploc > 0) {
			/* Write characters up until wrap location */
			lcd_setpos(xpos, ypos);
			int i;
			for (i = 0; i < wraploc; i++) {
				lcd_send_char(*str++);
				delay(TEXT_SPEED);
			}
			/* Skip over trailing space */
			str++;
			i++;
		} else {
			/* No space character to wrap at */
			lcd_setpos(xpos, ypos);
			int i;
			for (i = 0; i < LCD_MAX_X_CHARS; i++) {
				lcd_send_char(*str++);
				delay(TEXT_SPEED);
			}
		}

		/* Move cursor to next line */
		xpos = 0;
		ypos = (ypos + 1) % LCD_MAX_Y;
	}
}
