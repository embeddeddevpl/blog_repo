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

#include <string.h>

#include "../LCD/lcd.h"
#include "../LCD/lcd_buf.h"

#include "menu.h"

// definition of menu's components: (*name, *next, *prev, *child, *parent, (*menu_function))
menu_t menu1 = { "ELEMENT 1", &menu2, &menu6, &sub_menu1_1, NULL, NULL };
	menu_t sub_menu1_1 = { "ELEMENT 1_1", &sub_menu1_2, &sub_menu1_2, &sub_menu1_1_1, &menu1, NULL };
		menu_t sub_menu1_1_1 = { "ELEMENT 1_1_1", NULL, &sub_menu1_1_1, NULL, &sub_menu1_1, NULL };
	menu_t sub_menu1_2 = { "ELEMENT 1_2", NULL, &sub_menu1_1, NULL, &menu1, NULL };
menu_t menu2 = { "ELEMENT 2", &menu3, &menu1, &sub_menu2_1, NULL, NULL };
	menu_t sub_menu2_1 = { "ELEMENT 2_1", &sub_menu2_2, &sub_menu2_4, NULL, &menu2, NULL };
	menu_t sub_menu2_2 = { "ELEMENT 2_2", &sub_menu2_3, &sub_menu2_1, &sub_menu2_2_1, &menu2, NULL };
		menu_t sub_menu2_2_1 = { "ELEMENT 2_2_1", &sub_menu2_2_2, &sub_menu2_2_5, NULL, &sub_menu2_2, NULL };
		menu_t sub_menu2_2_2 = { "ELEMENT 2_2_2", &sub_menu2_2_3, &sub_menu2_2_1, NULL, &sub_menu2_2, NULL };
		menu_t sub_menu2_2_3 = { "ELEMENT 2_2_3", &sub_menu2_2_4, &sub_menu2_2_2, NULL, &sub_menu2_2, NULL };
		menu_t sub_menu2_2_4 = { "ELEMENT 2_2_4", &sub_menu2_2_5, &sub_menu2_2_3, NULL, &sub_menu2_2, NULL };
		menu_t sub_menu2_2_5 = { "ELEMENT 2_2_5", NULL, &sub_menu2_2_4, NULL, &sub_menu2_2, NULL };
	menu_t sub_menu2_3 = { "ELEMENT 2_3", &sub_menu2_4, &sub_menu2_2, NULL, &menu2, NULL };
	menu_t sub_menu2_4 = { "ELEMENT 2_4", NULL, &sub_menu2_3, NULL, &menu2, NULL };
menu_t menu3 = { "ELEMENT 3", &menu4, &menu2, NULL, NULL, NULL };
menu_t menu4 = { "ELEMENT 4", &menu5, &menu3, NULL, NULL, NULL };
menu_t menu5 = { "ELEMENT 5", &menu6, &menu4, NULL, NULL, NULL };
menu_t menu6 = { "ELEMENT 6", NULL, &menu5, NULL, NULL, NULL };

menu_t *currentPointer = &menu1;

uint8_t menu_index;
uint8_t lcd_row_pos;
uint8_t lcd_row_pos_level_1, lcd_row_pos_level_2;

void menu_refresh(void) {

	menu_t *temp;
	uint8_t i;

	if (currentPointer->parent) temp = (currentPointer->parent)->child;
	else temp = &menu1;

	for (i = 0; i != menu_index - lcd_row_pos; i++) {
		temp = temp->next;
	}

	buf_clear();
	for (i = 0; i < LCD_ROWS; i++) {

		buf_locate(0, i);
		if (temp == currentPointer) buf_char(62);
		else buf_char(' ');

		buf_locate(2, i);
		buf_str(temp->name);

		temp = temp->next;
		if (!temp) break;

	}

	// lcd_refresh();
}

uint8_t menu_get_index(menu_t *q) {

	menu_t *temp;
	uint8_t i = 0;

	if (q->parent) temp = (q->parent)->child;
	else temp = &menu1;

	while (temp != q) {
		temp = temp->next;
		i++;
	}

	return i;
}

uint8_t menu_get_level(menu_t *q) {

	menu_t *temp = q;
	uint8_t i = 0;

	if (!q->parent) return 0;

	while (temp->parent != NULL) {
		temp = temp->parent;
		i++;
	}

	return i;
}

void menu_next(void) {

	if (currentPointer->next)
	{

		currentPointer = (*currentPointer).next;
		menu_index++;
		if (++lcd_row_pos > LCD_ROWS - 1) lcd_row_pos = LCD_ROWS - 1;
	}
	else
	{
		menu_index = 0;
		lcd_row_pos = 0;

		if (currentPointer->parent) currentPointer = (currentPointer->parent)->child;
		else currentPointer = &menu1;
	}

	menu_refresh();

}

void menu_prev(void) {

	currentPointer = currentPointer->prev;

	if (menu_index)
	{
		menu_index--;
		if (lcd_row_pos > 0) lcd_row_pos--;
	}
	else
	{
		menu_index = menu_get_index(currentPointer);

		if (menu_index >= LCD_ROWS - 1) lcd_row_pos = LCD_ROWS - 1;
		else lcd_row_pos = menu_index;
	}

	menu_refresh();
}

void menu_enter(void) {

	if (currentPointer->menu_function) currentPointer->menu_function();

	if (currentPointer->child)
	{

		switch (menu_get_level(currentPointer)) {
			case 0:
				lcd_row_pos_level_1 = lcd_row_pos;
				break;

			case 1:
				lcd_row_pos_level_2 = lcd_row_pos;
				break;
		}

		// switch...case can be replaced by:
		// lcd_row_pos_level[ menu_get_level(currentPointer) ] = lcd_row_pos;

		menu_index = 0;
		lcd_row_pos = 0;

		currentPointer = currentPointer->child;

		menu_refresh();
	}
}

void menu_back(void) {

	if (currentPointer->parent) {

		switch (menu_get_level(currentPointer)) {
			case 1:
				lcd_row_pos = lcd_row_pos_level_1;
				break;

			case 2:
				lcd_row_pos = lcd_row_pos_level_2;
				break;
			}

		currentPointer = currentPointer->parent;
		menu_index = menu_get_index(currentPointer);

		menu_refresh();

	}
}
