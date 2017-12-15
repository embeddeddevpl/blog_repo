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
#include "config.h"

void GPIO_Config(void) {

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}


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
