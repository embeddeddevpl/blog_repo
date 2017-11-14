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

#include "stm32f10x.h"
#include "../LCD_HD44780/lcd.h"
#include "../LCD_HD44780/lcd_buf.h"
#include "common.h"
#include "config.h"

int main(void)
{
	TIMERS_Config();
	LCD_Init();

	buf_locate(3,1);
	buf_str("BUFOROWANIE LCD");
	buf_locate(1,2);
	buf_str("www.EmbeddedDev.pl");

	while(1)
	{
		lcd_refresh();
	}

}


