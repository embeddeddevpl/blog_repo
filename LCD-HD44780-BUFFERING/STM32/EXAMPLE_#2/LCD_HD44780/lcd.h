/*
 * Author: £ukasz £aguna
 * E-mail: kontakt@embeddedev.pl
 * Blog:   www.EmbeddedDev.pl
 *
 * LCD HD44780 LIBRARY (4bit mode, busy flag reading)
 * Tutorial(in polish): www.EmbeddedDev.pl/obsluga-lcd-hd44780-komunikacja-dwukierunkowa/
 *
 * MCU: STM32F103
 *
 */

#ifndef LCD_H_
#define LCD_H_

#include "stm32f10x.h"
#include "common.h"

#define LCD_ROWS 4
#define LCD_COLS 20


#define LCD_E_PIN	GPIO_Pin_7
#define LCD_E_PORT	GPIOC

#define LCD_RS_PIN	GPIO_Pin_9
#define LCD_RS_PORT	GPIOA

#define LCD_RW_PIN	GPIO_Pin_8
#define LCD_RW_PORT	GPIOB

#define LCD_D4_PIN	GPIO_Pin_13
#define LCD_D4_PORT	GPIOB

#define LCD_D5_PIN	GPIO_Pin_2
#define LCD_D5_PORT	GPIOD

#define LCD_D6_PIN	GPIO_Pin_2
#define LCD_D6_PORT	GPIOC

#define LCD_D7_PIN	GPIO_Pin_3
#define LCD_D7_PORT	GPIOC

#define LCD_E_HIGH 		GPIO_WriteBit(LCD_E_PORT, LCD_E_PIN, Bit_SET)
#define LCD_E_LOW 		GPIO_WriteBit(LCD_E_PORT, LCD_E_PIN, Bit_RESET)
#define LCD_RS_LOW 		GPIO_WriteBit(LCD_RS_PORT, LCD_RS_PIN, Bit_RESET)
#define LCD_RS_HIGH 	GPIO_WriteBit(LCD_RS_PORT, LCD_RS_PIN, Bit_SET)
#define LCD_RW_LOW 		GPIO_WriteBit(LCD_RW_PORT, LCD_RW_PIN, Bit_RESET)
#define LCD_RW_HIGH 	GPIO_WriteBit(LCD_RW_PORT, LCD_RW_PIN, Bit_SET)

#define LCD_LINE1 		0x00
#define LCD_LINE2 		0x40
#define LCD_LINE3 		0x14
#define LCD_LINE4 		0x54

#define LCD_CLEAR					0x01
#define LCD_HOME					0x02
#define LCDC_ENTRY_MODE				0x04
	#define LCD_EM_SHIFT_CURSOR			0x00
	#define LCD_EM_SHIFT_DISPLAY	 	0x01
	#define LCD_EM_LEFT		   			0x00
	#define LCD_EM_RIGHT				0x02
#define LCD_ONOFF					0x08
	#define LCD_DISP_ON					0x04
	#define LCD_CURSOR_ON				0x02
	#define LCDC_CURSOR_OFF				0x00
	#define LCDC_BLINK_ON				0x01
	#define LCDC_BLINK_OFF				0x00
#define LCD_SHIFT					0x10
	#define LCDC_SHIFT_DISP				0x08
	#define LCDC_SHIFT_CURSOR			0x00
	#define LCDC_SHIFT_RIGHT			0x04
	#define LCDC_SHIFT_LEFT				0x00
#define LCD_FUNC					0x20
	#define LCD_8_BIT					0x10
	#define LCD_4_BIT					0x00
	#define LCDC_TWO_LINE				0x08
	#define LCDC_FONT_5x10				0x04
	#define LCDC_FONT_5x7				0x00
#define LCDC_SET_CGRAM				0x40
#define LCDC_SET_DDRAM				0x80

void LCD_Init(void);
void lcd_locate(uint8_t x, uint8_t y);
void lcd_char(char data);

uint8_t lcd_readFlag(void);

#endif /* LCD_H_ */
