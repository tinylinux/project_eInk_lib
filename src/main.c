// Programme de base TP II ENS

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

uint8_t etat_bouton1_before;
uint8_t etat_bouton1_now;
uint8_t etat_bouton2_before;
uint8_t etat_bouton2_now;
uint8_t tempo;
uint8_t menu;
uint8_t modeauto;
uint32_t periode;
uint8_t state;
uint8_t captLED1;


int main(void) {



	while (1) {

	} // end of while(1)

} // end of main
