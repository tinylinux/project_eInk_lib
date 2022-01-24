/*
 *	File :		spi_eink.c
 *	Author :	Rida Lali
 *	Task :		Module pour l'écran en liaison SPI
 */

#include "LPC8xx.h"
#include "fro.h"
#include "syscon.h"
#include "lib_ENS_II1_lcd.h"
#include "rom_api.h"
#include <stdio.h>
#include "ctimer.h"
#include "swm.h"
#include "spi.h"
#include "chip_setup.h"
#include "spi_eink.h"


void set_spi(){
	LPC_SYSCON->SYSAHBCLKCTRL0 |= SPI0 | SWM;

	// Give SPI0 a reset
	LPC_SYSCON->PRESETCTRL0 &= (SPI0_RST_N);
	LPC_SYSCON->PRESETCTRL0 |= ~(SPI0_RST_N);

	// Connect speakers to TO_MAT1
	LPC_SWM->PINASSIGN2 = 0x0B150C0A;

	LPC_SYSCON->SPI0CLKSEL = FCLKSEL_FRO_CLK;

	LPC_SPI0->CFG = SPI_CFG_MASTER|SPI_CFG_CPOL;
			// Clear any pending flags, just in case
	LPC_SPI0->STAT = 0xFFFF;
			// Enable USART0
	LPC_SPI0->CFG |= SPI_CFG_ENABLE;
}
