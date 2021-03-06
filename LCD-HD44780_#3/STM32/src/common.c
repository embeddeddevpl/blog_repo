/*
 * Autor: �ukasz �aguna
 * E-mail: kontakt@embeddeddev.pl
 * www.EmbeddedDev.pl
 *
 * Obs�uga LCD opartych na sterowniku HD44780
 * tryb 4-bitowy, z odczytem busy flag
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

