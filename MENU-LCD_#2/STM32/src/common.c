/*
 * Author: £ukasz £aguna
 * E-mail: kontakt@embeddedev.pl
 * Blog:   www.EmbeddedDev.pl
 *
 * LCD HD44780 MENU #2
 * Tutorial(in polish): http://www.embeddeddev.pl/menu-na-lcd-implementacja-rozszerzenie/
 *
 * MCU: STM32F103
 *
 */

#include "stm32f10x.h"
#include "common.h"
#include "../MENU/menu.h"

void (*key_next_func)(void) = &menu_next;
void (*key_prev_func)(void) = &menu_prev;
void (*key_enter_func)(void) = &menu_enter;
void (*key_back_func)(void) = &menu_back;


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

		if(key_next_func) (*key_next_func)();

	} else if( key_next_lock && (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)) ) key_next_lock++;

}

void key_prev_press(void){

	static uint8_t key_prev_lock=0;

	if( !key_prev_lock && !(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8) ) ) {

		key_prev_lock=1;

		if(key_prev_func) (*key_prev_func)();

	} else if( key_prev_lock && (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)) ) key_prev_lock++;

}



void key_enter_press(void){

	static uint8_t key_enter_lock=0;

	if( !key_enter_lock && !(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5) ) ) {

		key_enter_lock=1;

		if(key_enter_func) (*key_enter_func)();

	} else if( key_enter_lock && (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)) ) key_enter_lock++;

}



void key_back_press(void){

	static uint8_t key_back_lock=0;

	if( !key_back_lock && !(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4) ) ) {

		key_back_lock=1;

		if(key_back_func) (*key_back_func)();

	} else if( key_back_lock && (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)) ) key_back_lock++;

}
