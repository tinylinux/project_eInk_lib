// Programme de base TP II ENS

#include "LPC8xx.h"
#include "syscon.h"
#include "lib_ENS_II1_lcd.h"
#include "rom_api.h"
#include <stdio.h>
#include "ctimer.h"
#include "uart.h"

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

void set_freq(char touch) {
	lcd_position(0,0);
	char str[20];
	sprintf(str, "Touche : %c", touch);
	lcd_puts(str);
}

int main(void) {
		// Configuration de l'horloge : 15MHz
		LPC_PWRD_API->set_fro_frequency(30000);

		// Configuration UART1
		LPC_SYSCON->UART1CLKSEL = 0;
			// Activation du périphérique d'entrées/sorties TOR
		LPC_SYSCON->SYSAHBCLKCTRL0 |= IOCON | GPIO0 | CTIMER0 | SWM | MRT | UART1;
		LPC_SWM->PINASSIGN1 = 0xFF1412FF;
		// Connect UART0 TXD, RXD signals to port pins
		// ConfigSWM(U1_TXD, DBGTXPIN);
		// ConfigSWM(U1_RXD, DBGRXPIN);
			// Give USART1 a reset
		LPC_SYSCON->PRESETCTRL0 &= (UART1_RST_N);
		LPC_SYSCON->PRESETCTRL0 |= ~(UART1_RST_N);

		// Connect speakers to TO_MAT1
		// LPC_SWM->PINASSIGN4 = 0xFFFF13FF;
		// LPC_SYSCON->SYSAHBCLKCTRL0 &= ~(SWM);

		LPC_USART1->CFG = 0;
		LPC_USART1->OSR = 4;
		// Configured clock : FRO
		LPC_SYSCON->UART1CLKSEL = FCLKSEL_FRO_CLK;
		// Configure the USART0 baud rate generator
		// FRCLK = FRSET * 1000 / 2 = FRSET * 500
		LPC_USART1->BRG = (15000000 / (115000 *5)) - 1;

		//Configuration en sortie des broches P0_11, 17, 19 et 21
		LPC_GPIO_PORT->DIR0 |= (1 << 17);
		LPC_GPIO_PORT->DIR0 |= 1 << 19;

		// Configure the USART0 CFG register:
		// 8 data bits, no parity, one stop bit, no flow control, asynchronous mode
		LPC_USART1->CFG = DATA_LENG_8|PARITY_NONE|STOP_BIT_1;
		LPC_USART1->CTL = 0;
		// Clear any pending flags, just in case
		LPC_USART1->STAT = 0xFFFF;
		// Enable USART0
		LPC_USART1->CFG |= UART_EN;

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
					PutTerminalString(LPC_USART1, "Bouton 2 enfoncé\r\n");
					lcd_position(1,0);
					lcd_puts("b envoye");
				}
			}

			etat_bouton1_before = etat_bouton1_now;

			if (LPC_USART1->STAT & RXRDY)
			{
				received = LPC_USART1->RXDAT;
				set_freq(received);
			}
	} // end of while(1)

} // end of main
