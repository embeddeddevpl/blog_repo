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

#include "stm32f10x.h"
#include "config.h"
#include "../UART/uart.h"


int main(void){

	GPIO_Config();
	UART_Config();
	NVIC_Config();

	while(1){

		uart_put_string("www.EmbeddedDev.pl\n\r");

	}

}
