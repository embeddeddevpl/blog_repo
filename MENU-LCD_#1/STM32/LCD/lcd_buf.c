/*
 * Author: £ukasz £aguna
 * E-mail: kontakt@embeddedev.pl
 * Blog:   www.EmbeddedDev.pl
 *
 * LCD HD44780 buffering #1
 * Tutorial(in polish): www.EmbeddedDev.pl/buforowanie-lcd/
 *
 * MCU: STM32F103
 *
 */

#include "lcd.h"
#include "lcd_buf.h"
#include "stdlib.h"

char 	lcd_buf[LCD_ROWS][LCD_COLS];
char 	lcd_buf_old[LCD_ROWS][LCD_COLS];
uint8_t lcd_buf_x, lcd_buf_y;

void buf_locate(uint8_t x, uint8_t y)
{
	lcd_buf_x = x;
	lcd_buf_y = y;
}

void buf_char(char c)
{
	if (lcd_buf_x < LCD_COLS && lcd_buf_y < LCD_ROWS)
	{
		lcd_buf[lcd_buf_y][lcd_buf_x] = c;
		lcd_buf_x++;
		if (lcd_buf_x == LCD_COLS) {
			lcd_buf_x = 0;
			lcd_buf_y++;
			if (lcd_buf_y == LCD_ROWS)
				lcd_buf_y = 0;
		}
	}
}

void buf_clear(void)
{
	for(uint8_t y=0; y<LCD_ROWS; y++)
	{
		for(uint8_t x=0; x<LCD_COLS; x++)
		{
			lcd_buf[y][x]=' ';
		}
	}
	lcd_buf_x=0; lcd_buf_y=0;
}


void lcd_refresh(void)
{
	static uint8_t locate_flag = 0; // informs when lcd cursor position have to be changed

	for(uint8_t y=0; y<LCD_ROWS; y++)
	{
		lcd_locate( 0, y );

		for(uint8_t x=0; x<LCD_COLS; x++)
		{

			if( lcd_buf[y][x] != lcd_buf_old[y][x] )
			{
				if( !locate_flag )
					lcd_locate( x, y );
				lcd_char( lcd_buf[y][x] );
				lcd_buf_old[y][x] = lcd_buf[y][x];
				locate_flag = 1;
			}
			else
				locate_flag = 0;

		}

	}
}

/* Additional functions */

void buf_str(char *text)
{
	while(*text)
		buf_char(*text++);
}

void buf_str_XY(uint8_t x, uint8_t y, char *text)
{
	buf_locate(x,y);

	while(*text)
		buf_char(*text++);

}
