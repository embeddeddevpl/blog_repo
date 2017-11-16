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

#include "stm32f10x.h"
#include "config.h"

void TIMERS_Config(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	// delay_ms
	TIM_TimeBaseInitTypeDef TIM_TimeBaseMili_InitStructure;
	TIM_TimeBaseMili_InitStructure.TIM_Prescaler = 64000 - 1;
	TIM_TimeBaseMili_InitStructure.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseMili_InitStructure);

	// delay_us
	TIM_TimeBaseInitTypeDef TIM_TimeBaseMicro_InitStructure;
	TIM_TimeBaseMicro_InitStructure.TIM_Prescaler = 35 - 1;
	TIM_TimeBaseMicro_InitStructure.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseMicro_InitStructure);

	// lcd_refresh_time
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef TIM3_InitStructure;
	TIM3_InitStructure.TIM_Prescaler = 64000 - 1;
	TIM3_InitStructure.TIM_Period = 20;
	TIM3_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM3_InitStructure);

	TIM_ITConfig(TIM3, TIM_IT_Update , ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}


void NVIC_Config(void)
{

	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
