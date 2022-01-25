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
#include "serie_bluetooth.h"
#include "i2c_clock.h"
#include "menu.h"

void changemenu(uint8_t* menu)
{
	*menu = (*menu + 1) % NOMBRE_MENU;
	display_menu(*menu);
}

void display_menu(uint8_t menu)
{
	uint8_t h, m, s;
	char text[30];

	switch(menu)
	{
		case MENU_INDEX :
			send_bluetooth("Bienvenue dans l'interface \r\n");
			send_bluetooth("Pour défiler, sur le menu, appuyer sur BP2 \r\n");
			read_time(&h, &m, &s);
			sprintf(text,"%2d:%2d:%2d\r\n", h, m, s);
			send_bluetooth("Il est : ");
			send_bluetooth(text);
			send_bluetooth("--------- \r\n");
			break;
		case MENU_FREQ_S :
			send_bluetooth("Choisir la fréquence de la sonnerie : \r\n");
			send_bluetooth("A -> Do (261.63Hz) - Z -> Re (293.66Hz) \r\n");
			send_bluetooth("E -> Mi (329.63Hz) - R -> Fa (349.23Hz) \r\n");
			send_bluetooth("T -> Sol (392Hz)   - Y -> La (440Hz) \r\n");
			send_bluetooth("U -> Si (493.88Hz) - I -> Do (523.25Hz) \r\n");
			send_bluetooth("--------- \r\n");
			break;
		case MENU_HOUR_S :
			send_bluetooth("Une sonnerie est déclenchée toutes les 30s. \r\n");
			break;
		case MENU_TEST	:
			send_bluetooth("Voici l'heure et la date en direct \r\n");
			send_bluetooth("--------- \r\n");
			break;
	}
}

void change_freq(float* freq, char gotKey)
{
	switch (gotKey)
	{
		case 'A': send_bluetooth("Fréquence Choisie : Do 261,63 Hz \r\n"); *freq = 261.63; break;
		case 'Z': send_bluetooth("Fréquence Choisie : Re 293,66 Hz \r\n"); *freq = 293.66; break;
		case 'E': send_bluetooth("Fréquence Choisie : Mi 329,63 Hz \r\n"); *freq = 329.63; break;
		case 'R': send_bluetooth("Fréquence Choisie : Fa 349,23 Hz \r\n"); *freq = 349.23; break;
		case 'T': send_bluetooth("Fréquence Choisie : Sol 392 Hz   \r\n"); *freq = 392.00; break;
		case 'Y': send_bluetooth("Fréquence Choisie : La 440 Hz    \r\n"); *freq = 440.00; break;
		case 'U': send_bluetooth("Fréquence Choisie : Si 493,88 Hz \r\n"); *freq = 493.88; break;
		case 'I': send_bluetooth("Fréquence Choisie : Do 523,25 Hz \r\n	"); *freq = 523.25; break;
	}
}
