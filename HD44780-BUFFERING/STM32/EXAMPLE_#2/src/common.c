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

#include "stm32f10x.h"
#include "common.h"

void delay_ms(uint16_t czas) {

	TIM_SetCounter(TIM2,czas);

	TIM_Cmd(TIM2, ENABLE);
	while (TIM_GetCounter(TIM2));
	TIM_Cmd(TIM2, DISABLE);

}

void delay_us(uint8_t czas) {

	TIM_SetCounter(TIM1,czas);

	TIM_Cmd(TIM1, ENABLE);
	while (TIM_GetCounter(TIM1));
	TIM_Cmd(TIM1, DISABLE);

}

