/*
 *	File :		menu.c
 *	Author :	Rida Lali
 *	Task :		Création de module pour le menu
 */

#include "LPC8xx.h"
#include "fro.h"
#include "syscon.h"
#include "lib_ENS_II1_lcd.h"
#include "rom_api.h"
#include <stdio.h>
#include "menu.h"

void changemenu(uint8_t* menu)
{
	*menu = (*menu + 1) % NOMBRE_MENU;
	displaymenu(*menu);
}

void displaymenu(uint8_t menu)
{
	switch(menu)
	{
		case MENU_INDEX : lcd_position(0,0); lcd_puts("Bienvenue !"); break;
		case MENU_FREQ_S : lcd_position(0,0); lcd_puts("Choix freq :"); break;
		case MENU_HOUR_S : lcd_position(0,0); lcd_puts("Choix heure sonnerie :"); break;
		case MENU_TEST	: lcd_position(0,0); lcd_puts("Test bluetooth :"); break;
	}
}
