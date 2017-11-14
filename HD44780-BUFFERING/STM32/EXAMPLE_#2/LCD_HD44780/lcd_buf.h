/*
 * Author: £ukasz £aguna
 * E-mail: kontakt@embeddedev.pl
 * Blog:   www.EmbeddedDev.pl
 *
 * LCD HD44780 buffering #2
 * Tutorial(in polish): www.EmbeddedDev.pl/buforowanie-lcd/
 *
 * MCU: STM32F103
 *
 */

#ifndef LCD_BUF_H_
#define LCD_BUF_H_

#include "stm32f10x.h"
#include "lcd.h"

void buf_locate(uint8_t x, uint8_t y);
void buf_char(char c);
void buf_clear(void);
void lcd_refresh(void);

void buf_str(char *text);
void buf_str_XY(uint8_t x, uint8_t y, char * text);


#endif /* LCD_BUF_H_ */
