/*
 *	File :		serie_bluetooth.c
 *	Author :	Rida Lali
 *	Task :		Module pour l'utilisation
 *				du bluetooth
 */

#include "LPC8xx.h"
#include "syscon.h"
#include "lib_ENS_II1_lcd.h"
#include "rom_api.h"
#include <stdio.h>
#include "ctimer.h"
#include "uart.h"
#include "serie_bluetooth.h"

// USART 1 -> used for bluetooth

void set_bluetooth() {
	/*
	 * set_bluetooth : () -> void
	 * 		Configuration des ports UART1
	 * 		pour l'intégration du module bluetooth
	 * 		à la LPC804
	 */
	// Configuration UART1
	LPC_SYSCON->UART1CLKSEL = 0;
	LPC_SYSCON->SYSAHBCLKCTRL0 |=  UART1;
	LPC_SWM->PINASSIGN1 = 0xFF1412FF;
	// Give USART1 a reset
	LPC_SYSCON->PRESETCTRL0 &= (UART1_RST_N);
	LPC_SYSCON->PRESETCTRL0 |= ~(UART1_RST_N);
	LPC_USART1->CFG = 0;
	LPC_USART1->OSR = 4;
	// Configured clock : FRO
	LPC_SYSCON->UART1CLKSEL = FCLKSEL_FRO_CLK;
	// Configure the USART0 baud rate generator
	// FRCLK = FRSET * 1000 / 2 = FRSET * 500
	LPC_USART1->BRG = (15000000 / (115000 *5)) - 1;
	// Configure the USART1 CFG register:
		// 8 data bits, no parity, one stop bit, no flow control, asynchronous mode
	LPC_USART1->CFG = DATA_LENG_8|PARITY_NONE|STOP_BIT_1;
	LPC_USART1->CTL = 0;
		// Clear any pending flags, just in case
	LPC_USART1->STAT = 0xFFFF;
		// Enable USART0
	LPC_USART1->CFG |= UART_EN;

}

char check_bluetooth_received() {
	/*
	 * check_bluetooth_received : () -> char
	 * 		Fonction de vérification de réception
	 * 		d'un caractère via la liaison UART
	 * 		si oui, le caractère
	 * 		sinon renvoie -1 (ne correspondant à aucun char)
	 */
	char received;
	if (LPC_USART1->STAT & RXRDY)
	{
		received = LPC_USART1->RXDAT;
		// Debug Begin
		/*lcd_position(0,0);
		char str[20];
		sprintf(str, "Touche : %c", received);
		lcd_puts(str);*/
		// Debug End
		return received;
	}
	return -1;
}

void send_bluetooth(char* phrase) {
	/*
	 * send_bluetooth : char* -> void
	 * 		À partir d'une chaîne de caractères donnée
	 * 		transmet cette chaîne via liaison série
	 * 		au module bluetooth
	 */
	PutTerminalString(LPC_USART1, phrase);
	// Debug Begin
	/*lcd_position(0,0);
	lcd_puts("Bluetooth sent");*/
	// End Debug
}

