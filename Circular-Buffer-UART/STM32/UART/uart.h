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

#ifndef UART_H_
#define UART_H_

#include "stm32f10x.h"

#define UART_RX_BUF_SIZE 20
#define UART_TX_BUF_SIZE 20

int8_t uart_put_char( char data );
int8_t uart_get_char( char *data );

void uart_put_string( char *s );

#endif /* UART_H_ */
