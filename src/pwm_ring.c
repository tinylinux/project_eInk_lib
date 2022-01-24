/*
 *	File :		pwm_ring.c
 *	Author :	Rida Lali
 *	Task :		Module pour la sonnerie en PWM
 */

#include "LPC8xx.h"
#include "syscon.h"
#include "lib_ENS_II1_lcd.h"
#include "rom_api.h"
#include <stdio.h>
#include "ctimer.h"
#include "mrt.h"
#include "swm.h"
#include "pwm_ring.h"

uint8_t ringtone[NNOTES] = {0,0,3,0,2,0,1,0,0,3,0,3,0,1,0,0,3,0,2,0,1,0};
float notes[4] = {293.66, 349.22, 392.0, 440.0};
//uint8_t musicEnable = 0;
uint8_t currentNote = NNOTES*2+1;

void set_ctimer5() {
	LPC_PWRD_API->set_fro_frequency(30000);
	LPC_SYSCON->UART0CLKSEL = 0;

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

	LPC_MRT->Channel[0].CTRL = 0b11; // Active mrt0
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
	LPC_MRT->Channel[0].INTVAL = 15000000/4;
}

void init_MRT0(float frequency)
{
	LPC_SYSCON->SYSAHBCLKCTRL0 |= MRT;
	//Reglage MRT
	MRT0_setFrequency(frequency);
	LPC_MRT->Channel[0].CTRL = (1 << MRT_INTEN) | (0 << MRT_MODE);	//Interrupt Enable
	//Configuration des interruptions
	NVIC->ISER[0] |= (1 << (uint32_t)MRT_IRQn);	//Activation des interrupt MRT
	NVIC->IP[2] &= ~(0x00C00000);				//Priorite sur MRT
}

void MRT_IRQHandler()
{
	if (LPC_MRT->Channel[0].STAT & (1 << MRT_INTFLAG))
	{
		LPC_MRT->Channel[0].STAT |= (1 << MRT_INTFLAG);
		//LPC_GPIO_PORT->NOT0 = 1 << LED2;
		if (MUSICENABLE)
		{
			setNextKey();
		}
	}
}

void setNextKey()
{
		if ((++currentNote)/2 >= NNOTES)
		{
			currentNote -= 1;
			LPC_CTIMER0->MR[1] = 0;
		}
		else
		{
			if (currentNote % 2)
			{
				LPC_CTIMER0->MR[1] = 128;
				LPC_CTIMER0->PR = (int) (15000000 / (notes[ringtone[currentNote/2]] * 256));
			}
			else {
				LPC_CTIMER0->MR[1] = 0;
			}
		}
}

void MRT0_setFrequency(float frequency)
{
	LPC_MRT->Channel[0].INTVAL = (uint32_t)(15000000 / frequency); //Timer Period
}

void set_PWM(float frequency, float dutyCycle)
{
	uint32_t msr3 = (uint32_t)(15000000 / frequency);
	LPC_CTIMER0->MR[3] = msr3;
	LPC_CTIMER0->MR[1] = (uint32_t)(msr3 - (float)(dutyCycle * msr3 / 100));
}
