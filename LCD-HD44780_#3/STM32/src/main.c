/*
 * Autor: £ukasz £aguna
 * E-mail: kontakt@embeddeddev.pl
 * www.EmbeddedDev.pl
 *
 * Obs³uga LCD opartych na sterowniku HD44780
 * tryb 4-bitowy, z odczytem busy flag
 *
 * MCU: STM32F103
 *
 */

#include "stm32f10x.h"
#include "../LCD_1602/lcd.h"
#include "common.h"
#include "config.h"

int main(void)
{
	TIMERS_Config();

	LCD_Init();

	lcd_str_XY(1,0,"EmbeddedDev.pl");

	lcd_locate(7,1);
	lcd_char(':');
	lcd_char(')');

	while(1)
	{

	}


}


