/*
 *	File :		dirac_ring.c
 *	Author :	Rida Lali
 *	Task :		Module pour la sonnerie en PWM
 */

#include "LPC8xx.h"
#include "fro.h"
#include "syscon.h"
#include "lib_ENS_II1_lcd.h"
#include "rom_api.h"
#include <stdio.h>
#include "ctimer.h"
#include "swm.h"
#include "chip_setup.h"
#include "dirac_ring.h"

void set_ctimer1() {
	/*
	 * set_ctimer0 : () -> void
	 * 		Réglage du ctimer0 pour le MR
	 */
	// Réglage du prédiviseur
	LPC_CTIMER0->PR = 15000000 / (400 * 256); // 400 Hz
	// Reset le timer quand il est égal au MR3
	LPC_CTIMER0->MCR |= 1 << 10;
	// Sortie du PWM sur MAT1
	LPC_CTIMER0->PWMC = 1 << 1;
	LPC_CTIMER0->MR[1] = 0; // Temps à l'état bas (désactivé)
	LPC_CTIMER0->MR[3] = 256; // Période

	// Réinitialisation
	LPC_CTIMER0->TCR = 1 << CRST; // reset
	LPC_CTIMER0->TCR = 1 << CEN; // enable
}

void set_ring() {
	/*
	 * set_ring: () -> void
	 * 		Paramétrage du bip de sonnerie
	 */
	LPC_PWRD_API->set_fro_frequency(30000);

	// Activation du périphérique d'entrées/sorties TOR
	LPC_SYSCON->SYSAHBCLKCTRL0 |= IOCON | GPIO0 | CTIMER0 | SWM | MRT;


	// Connect speakers to TO_MAT1
	LPC_SWM->PINASSIGN4 = 0xFFFF13FF;
	LPC_SYSCON->SYSAHBCLKCTRL0 &= ~(SWM);

	// Give CTIMER0 a reset
	LPC_SYSCON->PRESETCTRL0 &= (CTIMER0_RST_N);
	LPC_SYSCON->PRESETCTRL0 |= ~(CTIMER0_RST_N);

	// Give MRT a reset
	LPC_SYSCON->PRESETCTRL0 &= MRT_RST_N;
	LPC_SYSCON->PRESETCTRL0 |= ~(MRT_RST_N);

	//Configuration en sortie des broches P0_11, 17, 19 et 21
	LPC_GPIO_PORT->DIR0 |= (1 << 17);
	LPC_GPIO_PORT->DIR0 |= 1 << 19;

	LPC_GPIO_PORT->DIR0 |= (1<<19);

	LPC_MRT->Channel[0].CTRL = 0b11;

	set_ctimer1();

	LPC_MRT->Channel[0].INTVAL = 15000000;
}

void sonnerie() {
	/*
	 * sonnerie : () -> void
	 * 		Activation du Haut-parleur et de la sonnerie
	 */
	LPC_CTIMER0->MR[1] = 128;
	LPC_CTIMER0->PR = (int) (15000000 / (523.55 * 256));
}

void stop_sonnerie(){
	/*
	 * stop_sonnerie : () -> void
	 * 		Stopper la sonnerie
	*/
	LPC_CTIMER0->MR[1] = 0;
}
