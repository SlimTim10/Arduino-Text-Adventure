#include "PCD8544.h"
#include "font.h"
#include <Arduino.h>
#include <string.h>

enum instructions {
	FUNCTION_SET = bit(5),
	BASIC_INSTRUCTION = FUNCTION_SET,
	EXTENDED_INSTRUCTION = FUNCTION_SET | bit(0),
	BIAS_SYSTEM = bit(4),
	MUX_48 = BIAS_SYSTEM | bit(1) | bit(0),
	SET_VOP = bit(7),
	DISPLAY_CONTROL = bit(3),
	DISPLAY_NORMAL = DISPLAY_CONTROL | bit(2),
	SET_Y = bit(6),
	SET_X = bit(7),
};

static struct lcd_pins *pins;

/* Send a command to the LCD */
static void send_cmd(uint8_t cmd) {
	digitalWrite(pins->sce, HIGH);
	digitalWrite(pins->sclk, LOW);
	digitalWrite(pins->dc, LOW);
	digitalWrite(pins->sce, LOW);
	shiftOut(pins->sdin, pins->sclk, MSBFIRST, cmd);
	digitalWrite(pins->sce, HIGH);
}

/* Send a data byte to the LCD */
static void send_data(uint8_t data) {
	digitalWrite(pins->sce, HIGH);
	digitalWrite(pins->sclk, LOW);
	digitalWrite(pins->dc, HIGH);
	digitalWrite(pins->sce, LOW);
	shiftOut(pins->sdin, pins->sclk, MSBFIRST, data);
	digitalWrite(pins->sce, HIGH);
}

/* Send a single ASCII character to the LCD */
void send_char(char c) {
	int i;
	for (i = 0; i < FONT_WIDTH; i++) {
		send_data(pgm_read_byte(&font5x8[c - ASCII_SPC][i]));
	}
	send_data(NULL);
}

/* Set the contrast of the LCD */
void lcd_contrast(uint8_t vop) {
	vop &= (bit(6) | bit(5) | bit(4) | bit(3) | bit(2) | bit(1) | bit(0));
	send_cmd(EXTENDED_INSTRUCTION);
	send_cmd(SET_VOP | vop);
	send_cmd(BASIC_INSTRUCTION);
}

/* Set the position of the cursor */
void lcd_setpos(uint8_t x, uint8_t y) {
	x %= LCD_MAX_X;
	y %= LCD_MAX_Y;
	send_cmd(SET_X | x);
	send_cmd(SET_Y | y);
}

/* Clear the LCD */
void lcd_clear(void) {
	lcd_setpos(0, 0);
	int i;
	for (i = 0; i < (LCD_MAX_X * LCD_MAX_Y); i++) {
		send_data(NULL);
	}
	lcd_setpos(0, 0);
}

/* Write a string to the LCD */
void lcd_print(const char *str) {
	while (*str) {
		send_char(*str++);
	}
}

/* Write a string to the LCD, starting at the specified location */
void lcd_printat(const char *str, uint8_t x, uint8_t y) {
	lcd_setpos(x % LCD_MAX_X, y % LCD_MAX_Y);
	while (*str) {
		send_char(*str++);
	}
}

/* Write a string to the LCD with word wrapping */
void lcd_printwrap(const char *str, uint8_t xpos, uint8_t ypos) {
	while (*str) {
		int wraploc = LCD_MAX_X_CHARS;

		/* Check if it's short enough to write */
		if (strlen(str) <= wraploc) {
			lcd_printat(str, xpos, ypos);
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
				send_char(*str++);
			}
			/* Skip over trailing space */
			str++;
			i++;
		} else {
			/* No space character to wrap at */
			lcd_setpos(xpos, ypos);
			int i;
			for (i = 0; i < LCD_MAX_X_CHARS; i++) {
				send_char(*str++);
			}
		}

		/* Move cursor to next line */
		xpos = 0;
		ypos = (ypos + 1) % LCD_MAX_Y;
	}
}

/* Initialize the LCD */
void lcd_init(struct lcd_pins *p) {
	pins = p;

	pinMode(pins->res, OUTPUT);
	pinMode(pins->sce, OUTPUT);
	pinMode(pins->dc, OUTPUT);
	pinMode(pins->sdin, OUTPUT);
	pinMode(pins->sclk, OUTPUT);

	digitalWrite(pins->res, HIGH);
	digitalWrite(pins->sce, HIGH);

	/* Initialize the LCD */
	/* RES pulse to perform reset function  */
	digitalWrite(pins->res, LOW);
	delayMicroseconds(1);
	digitalWrite(pins->res, HIGH);

	send_cmd(EXTENDED_INSTRUCTION);
	send_cmd(MUX_48);
	send_cmd(BASIC_INSTRUCTION);
	send_cmd(DISPLAY_NORMAL);
}
