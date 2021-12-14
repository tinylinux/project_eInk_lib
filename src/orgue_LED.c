/*
 * File : 	orgue_LED.c
 * Author : Rida LALI
 * Task :	Création d'un module pour la gestion des LED
 * 			sur la LPC 804
 * */

#include "LPC8xx.h"
#include "syscon.h"
#include "lib_ENS_II1_lcd.h"
#include "rom_api.h"
#include <stdio.h>
#include "ctimer.h"

#define BP1  LPC_GPIO_PORT->B0[13]
#define BP2  LPC_GPIO_PORT->B0[12]
#define LED1 LPC_GPIO_PORT->B0[19]
#define LED2 LPC_GPIO_PORT->B0[17]
#define LED3 LPC_GPIO_PORT->B0[21]
#define LED4 LPC_GPIO_PORT->B0[11]

void led_power_on(int n)
{
	switch (n)
	{
		case 1:
			LED1 = 1;
			break;
		case 2:
			LED2 = 2;
			break;
		case 3:
			LED3 = 3;
			break;
		case 4:
			LED4 = 4;
			break;
	}
}

void led_power_off(int n)
{
	switch (n)
	{
		case 1:
			LED1 = 0;
			break;
		case 2:
			LED2 = 0;
			break;
		case 3:
			LED3 = 0;
			break;
		case 4:
			LED4 = 0;
			break;
	}
}
