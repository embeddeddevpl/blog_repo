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

#ifndef COMMON_H_
#define COMMON_H_

#define LED_ON GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define LED_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define LED_TOG GPIO_WriteBit(GPIOA, GPIO_Pin_5, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_5))

void delay_ms(uint16_t czas);
void delay_us(uint8_t czas);

void key_next_press(void);
void key_prev_press(void);
void key_enter_press(void);
void key_back_press(void);

#endif /* COMMON_H_ */
