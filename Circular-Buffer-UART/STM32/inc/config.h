/*
 * Autor: Łukasz Łaguna
 * E-mail: kontakt@embeddeddev.pl
 * www.EmbeddedDev.pl
 *
 * Obsługa interfejsu UART w mikrokontrolerach w oparciu o przerwania,
 * korzystając z bufora kołowego (cyklicznego)
 *
 * MCU: STM32F103
 *
 */

#ifndef CONFIG_H_
#define CONFIG_H_

void GPIO_Config(void);
void UART_Config(void);
void NVIC_Config(void);

#endif /* CONFIG_H_ */
