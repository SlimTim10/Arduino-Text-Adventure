#ifndef LCD_EXTRA_H
#define LCD_EXTRA_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {	/* Use C library with Arduino */
#endif

	void lcd_light(uint8_t);
	void lcd_printat_anim(const char *, uint8_t, uint8_t);
	void lcd_printwrap_anim(const char *, uint8_t, uint8_t);

#ifdef __cplusplus
}
#endif

#endif
