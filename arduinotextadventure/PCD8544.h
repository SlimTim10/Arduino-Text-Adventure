#ifndef PCD8544_H
#define PCD8544_H

#include "font.h"
#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

	enum info {
		LCD_MAX_X = 84,
		LCD_MAX_Y = 6,
		LCD_MAX_X_CHARS = LCD_MAX_X / (FONT_WIDTH + 1),
		LCD_MAX_CHARS = (LCD_MAX_X * LCD_MAX_Y) / (FONT_WIDTH + 1),
	};

	struct lcd_pins {
		uint8_t res;
		uint8_t sce;
		uint8_t dc;
		uint8_t sdin;
		uint8_t sclk;
	};

	void lcd_send_cmd(uint8_t);
	void lcd_send_data(uint8_t);
	void lcd_send_char(char);
	void lcd_contrast(uint8_t);
	void lcd_setpos(uint8_t, uint8_t);
	void lcd_clear(void);
	void lcd_print(const char *);
	void lcd_printat(const char *, uint8_t, uint8_t);
	void lcd_printwrap(const char *, uint8_t, uint8_t);
	void lcd_init(struct lcd_pins *);

#define lcd_printf(...)	({\
			char tmpstr[LCD_MAX_CHARS];\
			sprintf(tmpstr, __VA_ARGS__);\
			lcd_print(tmpstr);\
		})

#ifdef __cplusplus
}
#endif

#endif
