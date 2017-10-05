/*
 * Autor: £ukasz £aguna
 * E-mail: kontakt@embeddeddev.pl
 * www.EmbeddedDev.pl
 *
 * Obs³uga LCD opartych na sterowniku HD44780
 * tryb 4-bitowy, bez odczytu busy flag
 *
 * MCU: STM32F103
 *
 */

#include "stm32f10x.h"
#include "lcd.h"

void lcd_sendHalf(uint8_t data)
{
	LCD_E_HIGH;
	GPIO_WriteBit(LCD_D4_PORT, LCD_D4_PIN, (data & 0x01));
	GPIO_WriteBit(LCD_D5_PORT, LCD_D5_PIN, (data & 0x02));
	GPIO_WriteBit(LCD_D6_PORT, LCD_D6_PIN, (data & 0x04));
	GPIO_WriteBit(LCD_D7_PORT, LCD_D7_PIN, (data & 0x08));
	LCD_E_LOW;
}

void lcd_write_byte(uint8_t data)
{
	lcd_sendHalf(data >> 4);
	lcd_sendHalf(data);

	delay_us(60);

}

void lcd_write_cmd(uint8_t cmd)
{
	LCD_RS_LOW;
	lcd_write_byte(cmd);

}

void lcd_char(char data)
{
	LCD_RS_HIGH;
	lcd_write_byte(data);

}

void lcd_locate(uint8_t x, uint8_t y)
{

	switch(y)
	{
		case 0:
			lcd_write_cmd( LCDC_SET_DDRAM | (LCD_LINE1 + x) );
			break;

		case 1:
			lcd_write_cmd( LCDC_SET_DDRAM | (LCD_LINE2 + x) );
			break;
	}

}

void lcd_gpio_init( void)
{
	// W³¹czamy taktowanie portów:
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	// Ustawiamy piny jako wyjœcia
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = LCD_D4_PIN;
	GPIO_Init(LCD_D4_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_D5_PIN;
	GPIO_Init(LCD_D5_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_D6_PIN;
	GPIO_Init(LCD_D6_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_D7_PIN;
	GPIO_Init(LCD_D7_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_RS_PIN;
	GPIO_Init(LCD_RS_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_E_PIN;
	GPIO_Init(LCD_E_PORT, &GPIO_InitStructure);

}

void LCD_Init(void)
{
	// Oczywiœcie na pocz¹tku musimy zainicjowac piny mikrokontrolera.
	// Stworzy³em w tym celu oddzieln¹ funkcjê lcd_gpio_init().
	// Jej cia³o przedstawiê w kolejnym punkcie.
	lcd_gpio_init();

	delay_ms(15);

	LCD_E_LOW;
	LCD_RS_LOW;

	lcd_sendHalf(0x03);
	delay_ms(4);
	delay_us(100);
	lcd_sendHalf(0x03);
	delay_us(100);
	lcd_sendHalf(0x03);
	delay_us(100);
	lcd_sendHalf(0x02);
	delay_us(100);

	// Ju¿ jesteœmy w trybie 4-bitowym. Tutaj dokonujemy ustawieñ wyœwietlacza:
	lcd_write_cmd( LCD_FUNC | LCD_4_BIT | LCDC_TWO_LINE | LCDC_FONT_5x7 );
	lcd_write_cmd( LCD_ONOFF | LCD_DISP_ON );
	lcd_write_cmd( LCD_CLEAR );
	delay_ms(5);
	lcd_write_cmd( LCDC_ENTRY_MODE | LCD_EM_SHIFT_CURSOR | LCD_EM_RIGHT );

}

/* Dodatkowe funkcje */

void lcd_str(char *text)
{
	while(*text)
		lcd_char(*text++);

}

void lcd_str_XY(uint8_t x, uint8_t y, char * text)
{
	lcd_locate(x,y);

	while(*text)
		lcd_char(*text++);

}
