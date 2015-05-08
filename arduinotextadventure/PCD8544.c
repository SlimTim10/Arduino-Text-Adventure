#include "PCD8544.h"
#include "font.h"
#include <Arduino.h>
#include <string.h>

#define SET_BIT(P, B)	(P |= B)
#define CLR_BIT(P, B)	(P &= (~B))

static struct rawports {
	volatile uint8_t *sce;
	volatile uint8_t *dc;
	volatile uint8_t *sdin;
	volatile uint8_t *sclk;
} port;

static struct bitmasks {
	uint8_t sce;
	uint8_t dc;
	uint8_t sdin;
	uint8_t sclk;
} bitmask;

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
void lcd_send_cmd(uint8_t cmd) {
	SET_BIT(*port.sce, bitmask.sce);
	CLR_BIT(*port.sclk, bitmask.sclk);
	CLR_BIT(*port.dc, bitmask.dc);
	CLR_BIT(*port.sce, bitmask.sce);
	uint8_t i;
	for (i = 0x80; i; i >>= 1) {
		(cmd & i) ? SET_BIT(*port.sdin, bitmask.sdin) : CLR_BIT(*port.sdin, bitmask.sdin);
		SET_BIT(*port.sclk, bitmask.sclk);
		CLR_BIT(*port.sclk, bitmask.sclk);
	}
	SET_BIT(*port.sce, bitmask.sce);}

/* Send a data byte to the LCD */
void lcd_send_data(uint8_t data) {
	SET_BIT(*port.sce, bitmask.sce);
	CLR_BIT(*port.sclk, bitmask.sclk);
	SET_BIT(*port.dc, bitmask.dc);
	CLR_BIT(*port.sce, bitmask.sce);
	uint8_t i;
	for (i = 0x80; i; i >>= 1) {
		(data & i) ? SET_BIT(*port.sdin, bitmask.sdin) : CLR_BIT(*port.sdin, bitmask.sdin);
		SET_BIT(*port.sclk, bitmask.sclk);
		CLR_BIT(*port.sclk, bitmask.sclk);
	}
	SET_BIT(*port.sce, bitmask.sce);
}

/* Send a single ASCII character to the LCD */
void lcd_send_char(char c) {
	int i;
	for (i = 0; i < FONT_WIDTH; i++) {
		lcd_send_data(pgm_read_byte(&font5x8[c - ASCII_SPC][i]));
	}
	lcd_send_data(NULL);
}

/* Set the contrast of the LCD */
void lcd_contrast(uint8_t vop) {
	vop &= (bit(6) | bit(5) | bit(4) | bit(3) | bit(2) | bit(1) | bit(0));
	lcd_send_cmd(EXTENDED_INSTRUCTION);
	lcd_send_cmd(SET_VOP | vop);
	lcd_send_cmd(BASIC_INSTRUCTION);
}

/* Set the position of the cursor */
void lcd_setpos(uint8_t x, uint8_t y) {
	x %= LCD_MAX_X;
	y %= LCD_MAX_Y;
	lcd_send_cmd(SET_X | x);
	lcd_send_cmd(SET_Y | y);
}

/* Clear the LCD */
void lcd_clear(void) {
	lcd_setpos(0, 0);
	int i;
	for (i = 0; i < (LCD_MAX_X * LCD_MAX_Y); i++) {
		lcd_send_data(NULL);
	}
	lcd_setpos(0, 0);
}

/* Write a string to the LCD */
void lcd_print(const char *str) {
	while (*str) {
		lcd_send_char(*str++);
	}
}

/* Write a string to the LCD, starting at the specified location */
void lcd_printat(const char *str, uint8_t x, uint8_t y) {
	lcd_setpos(x % LCD_MAX_X, y % LCD_MAX_Y);
	while (*str) {
		lcd_send_char(*str++);
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
				lcd_send_char(*str++);
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

	port.sce = portOutputRegister(digitalPinToPort(pins->sce));
	bitmask.sce = digitalPinToBitMask(pins->sce);
	port.dc = portOutputRegister(digitalPinToPort(pins->dc));
	bitmask.dc = digitalPinToBitMask(pins->dc);
	port.sdin = portOutputRegister(digitalPinToPort(pins->sdin));
	bitmask.sdin = digitalPinToBitMask(pins->sdin);
	port.sclk = portOutputRegister(digitalPinToPort(pins->sclk));
	bitmask.sclk = digitalPinToBitMask(pins->sclk);


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

	lcd_send_cmd(EXTENDED_INSTRUCTION);
	lcd_send_cmd(MUX_48);
	lcd_send_cmd(BASIC_INSTRUCTION);
	lcd_send_cmd(DISPLAY_NORMAL);
}
