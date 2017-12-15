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

#ifndef CONFIG_H_
#define CONFIG_H_

void GPIO_Config(void);
void NVIC_Config(void);
void TIMERS_Config(void);

#endif /* CONFIG_H_ */
