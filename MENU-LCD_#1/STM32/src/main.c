/*
 * Author: £ukasz £aguna
 * E-mail: kontakt@embeddedev.pl
 * Blog:   www.EmbeddedDev.pl
 *
 * LCD HD44780 MENU
 * Tutorial(in polish): http://www.embeddeddev.pl/menu-lcd-implementacja/
 *
 * MCU: STM32F103
 *
 */

#include "stm32f10x.h"

#include "common.h"
#include "config.h"

#include "../LCD/lcd.h"
#include "../MENU/menu.h"

volatile uint8_t timer_flag;

int main(void) {

	GPIO_Config();
	NVIC_Config();
	TIMERS_Config();
	LCD_Init();

	menu_refresh();

	while (1) {

		key_next_press();
		key_prev_press();
		key_enter_press();
		key_back_press();

		if (timer_flag) {
			lcd_refresh();
			LED_TOG;
			timer_flag = 0;
		}

	}

}

