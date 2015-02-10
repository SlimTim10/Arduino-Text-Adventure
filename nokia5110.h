#ifndef NOKIA5110_H
#define NOKIA5110_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {	// Use C library with Arduino
#endif

void lcd_clear(void);
void lcd_init(void);
void lcd_light(byte);
void lcd_write(char const *, byte, byte);
void lcd_write_wrap(char const *, byte, byte);

#ifdef __cplusplus
}
#endif

#endif
