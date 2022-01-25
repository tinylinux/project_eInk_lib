/*
 *	File :		menu.h
 *	Author :	Rida Lali
 *	Task :		Création de module pour le menu
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_

#define	NOMBRE_MENU	4

#define MENU_INDEX	0
#define MENU_FREQ_S	1
#define MENU_HOUR_S	2
#define MENU_TEST	3

void change_menu(uint8_t* menu);
void display_menu(uint8_t menu);
void change_freq(float* freq, char gotKey);

#endif /* INC_MENU_H_ */
