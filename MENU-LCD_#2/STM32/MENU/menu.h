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

#ifndef MENU_H_
#define MENU_H_

typedef struct menu_struct menu_t;

struct menu_struct {

	const char * name;
	menu_t * next;
	menu_t * prev;
	menu_t * child;
	menu_t * parent;
	void (*menu_function)(void);

};

menu_t menu1;
	menu_t sub_menu1_1;
	menu_t sub_menu1_1_1;
		menu_t sub_menu1_1_brightness;
	menu_t sub_menu1_2;

menu_t menu2;
	menu_t sub_menu2_1, sub_menu2_2,sub_menu2_3, sub_menu2_4, sub_menu2_5;
menu_t menu3;
menu_t menu4;
menu_t menu5;
menu_t menu6;

void menu_refresh(void);
void menu_next(void);
void menu_prev(void);
void menu_enter(void);
void menu_back(void);

#endif /* MENU_H_ */
