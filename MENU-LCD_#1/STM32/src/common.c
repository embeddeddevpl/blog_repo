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
#include "../MENU/menu.h"


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

void key_next_press(void){

	static uint8_t key_next_lock=0;

	if( !key_next_lock && !(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) ) ) {

		key_next_lock=1;

		menu_next();

	} else if( key_next_lock && (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)) ) key_next_lock++;

}

void key_prev_press(void){

	static uint8_t key_prev_lock=0;

	if( !key_prev_lock && !(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8) ) ) {

		key_prev_lock=1;

		menu_prev();

	} else if( key_prev_lock && (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)) ) key_prev_lock++;

}



void key_enter_press(void){

	static uint8_t key_enter_lock=0;

	if( !key_enter_lock && !(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5) ) ) {

		key_enter_lock=1;

		menu_enter();

	} else if( key_enter_lock && (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)) ) key_enter_lock++;

}



void key_back_press(void){

	static uint8_t key_back_lock=0;

	if( !key_back_lock && !(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4) ) ) {

		key_back_lock=1;

		menu_back();

	} else if( key_back_lock && (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)) ) key_back_lock++;

}
