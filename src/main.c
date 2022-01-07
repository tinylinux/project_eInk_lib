// Programme de base TP II ENS

#include "LPC8xx.h"
#include "syscon.h"
#include "lib_ENS_II1_lcd.h"
#include "rom_api.h"
#include <stdio.h>
#include "ctimer.h"
#include "serie_bluetooth.h"

#define BP1  LPC_GPIO_PORT->B0[13]
#define BP2  LPC_GPIO_PORT->B0[12]
#define LED1 LPC_GPIO_PORT->B0[19]
#define LED2 LPC_GPIO_PORT->B0[17]
#define LED3 LPC_GPIO_PORT->B0[21]
#define LED4 LPC_GPIO_PORT->B0[11]

uint8_t etat_bouton1_before;
uint8_t etat_bouton1_now;
uint8_t etat_bouton2_before;
uint8_t etat_bouton2_now;
char received = 0;

int main(void) {
		// Configuration de l'horloge : 15MHz
		LPC_PWRD_API->set_fro_frequency(30000);


			// Activation du périphérique d'entrées/sorties TOR
		LPC_SYSCON->SYSAHBCLKCTRL0 |= IOCON | GPIO0 | CTIMER0 | SWM | MRT;

		// Connect UART0 TXD, RXD signals to port pins
		// ConfigSWM(U1_TXD, DBGTXPIN);
		// ConfigSWM(U1_RXD, DBGRXPIN);


		// Connect speakers to TO_MAT1
		// LPC_SWM->PINASSIGN4 = 0xFFFF13FF;
		// LPC_SYSCON->SYSAHBCLKCTRL0 &= ~(SWM);

		set_bluetooth();

		//Configuration en sortie des broches P0_11, 17, 19 et 21
		LPC_GPIO_PORT->DIR0 |= (1 << 17);
		LPC_GPIO_PORT->DIR0 |= 1 << 19;


		//Mise à 1 de la sortie P0_11 et mise à 0 des autres
		//LPC_GPIO_PORT->PIN0 = (1 << 11);

		LPC_GPIO_PORT->DIR0 |= (1<<19);
		//Initialisation de l'afficheur lcd et affichage d'un texte
		//init_lcd();
		//lcd_puts("TP ENS II1 2021");


		//set_ctimer0();
		init_lcd();
		while (1) {

			etat_bouton1_now = BP2;
			if ((etat_bouton1_now != etat_bouton1_before))
			{
				if (etat_bouton1_now)
				{
					send_bluetooth("Bouton 2 enfoncé\r\n");
				}
			}

			etat_bouton1_before = etat_bouton1_now;

			received = check_bluetooth_received();
			if (received >= 32 && received <= 126) // entre Espace et Tilde
			{
				printf("Touche : %c", received);
			}
	} // end of while(1)

} // end of main
