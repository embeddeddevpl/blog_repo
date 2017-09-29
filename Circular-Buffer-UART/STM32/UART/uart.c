/*
 * Autor: £ukasz £aguna
 * E-mail: kontakt@embeddeddev.pl
 * www.EmbeddedDev.pl
 *
 * Obs³uga interfejsu UART w mikrokontrolerach w oparciu o przerwania,
 * korzystaj¹c z bufora ko³owego (cyklicznego)
 *
 * MCU: STM32F103
 *
 */

#include "uart.h"
#include "stm32f10x.h"

volatile char uart_rxBuff[UART_RX_BUF_SIZE];
volatile char uart_txBuff[UART_TX_BUF_SIZE];

typedef struct {
	volatile char * const buffer;
	uint8_t head;
	uint8_t tail;
} circ_buffer_t;

volatile circ_buffer_t uart_rx_circBuff = { uart_rxBuff, 0, 0 };
volatile circ_buffer_t uart_tx_circBuff = { uart_txBuff, 0, 0 };

int8_t uart_put_char( char data )
{

	uint8_t head_temp = uart_tx_circBuff.head + 1;

	if ( head_temp == UART_TX_BUF_SIZE )
		head_temp = 0;

//	if ( head_temp == uart_tx_circBuff.tail )
//		return -1;

	while ( head_temp == uart_tx_circBuff.tail );

	uart_tx_circBuff.buffer[head_temp] = data;
	uart_tx_circBuff.head = head_temp;

	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);

	return 0;

}

int8_t uart_get_char( char *data )
 {

	if (uart_rx_circBuff.head == uart_rx_circBuff.tail)
		return -1;

	uart_rx_circBuff.tail++;

	if (uart_rx_circBuff.tail == UART_RX_BUF_SIZE)
		uart_rx_circBuff.tail = 0;

	*data = uart_rx_circBuff.buffer[uart_rx_circBuff.tail];

	return 0;

}

void USART2_IRQHandler( void ) {

	// Identyfikujemy Ÿród³o przerwania

	// Jeœli jest to przerwanie od danych przychodz¹cych
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		uint8_t head_temp = uart_rx_circBuff.head + 1;

		if ( head_temp == UART_RX_BUF_SIZE )
			head_temp = 0;

		// Sprawdzamy czy jest miejsce w buforze
		if ( head_temp == uart_rx_circBuff.tail ) {
			// Jeœli bufor jest pe³ny to mo¿emy tu jakoœ na to zareagowaæ
			// W procedurze obs³ugi przerwania nie mo¿na czekaæ na zwolnienie miejsca!

			// Ja w tym wypadku zdecydowa³em siê pomin¹æ nowe dane.
			// Czyszczenie flagi USART_IT_RXNE:
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		}

		// Jeœli jest miejsce w buforze to przechodzimy dalej:
		else
		{
			uart_rx_circBuff.buffer[head_temp] = USART_ReceiveData(USART2);
			uart_rx_circBuff.head = head_temp;

		}

	}

	// Jeœli jest to przerwanie od danych wychodz¹cych
	if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET) {

		// Sprawdzamy czy jest coœ w buforze
		// Jeœli bufor jest pusty tzn, ¿e wszystkie dane zosta³y wys³ane
		// i mo¿emy wy³¹czyæ przerwanie od TX, które w³¹czyliœmy w funkcji uart_put_char()
		if (uart_tx_circBuff.head == uart_tx_circBuff.tail) {

			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);

		}
		else
		{
			uart_tx_circBuff.tail++;

			if (uart_tx_circBuff.tail == UART_TX_BUF_SIZE)
				uart_tx_circBuff.tail = 0;

			// Odczytujemy znak z bufora i go wysy³amy
			USART_SendData(USART2,
					uart_tx_circBuff.buffer[uart_tx_circBuff.tail]);
		}

	}

}

/* Dodatkowe funkcje */

void uart_put_string( char *s )
{
	while(*s)
		uart_put_char(*s++);
}

