/*
 *	File :		i2c_clock.h
 *	Author :	Rida Lali
 *	Task :		Module pour la gestion de l'horloge
 */

#include "LPC8xx.h"
#include "syscon.h"
#include "lib_ENS_II1_lcd.h"
#include "rom_api.h"
#include <stdio.h>
#include "ctimer.h"
#include "swm.h"
#include "i2c.h"
#include "i2c_clock.h"

void set_clock() {
	LPC_SYSCON->SYSAHBCLKCTRL0 |= I2C0;
}

void read_time(uint8_t* h, uint8_t* m, uint8_t* s) {
	uint8_t I2CMasterBuffer[BUFSIZE];
	uint8_t I2CSlaveBuffer[3];
	uint32_t I2CReadLength, I2CWriteLength;
	WaitI2CMasterState(LPC_I2C0, I2C_STAT_MSTST_IDLE);
	I2CWriteLength = 1;
	I2CReadLength = 3;
	I2CMasterBuffer[0] = 0xD0;
	I2CMasterBuffer[1] = 0x00;
	I2CmasterWriteRead(I2CMasterBuffer, I2CSlaveBuffer, I2CWriteLength,
	I2CReadLength);
	*s = ((I2CSlaveBuffer[0]&0xF0)>>4)*10 + (I2CSlaveBuffer[0]&0x0F);
	*m = ((I2CSlaveBuffer[1]&0xF0)>>4)*10+ (I2CSlaveBuffer[1]&0x0F);
	*h = ((I2CSlaveBuffer[2]&0x20)>>5)*20 + ((I2CSlaveBuffer[2]&0x10)>>4)*10+ (I2CSlaveBuffer[2]&0x0F);
}

void read_date(uint8_t* j, uint8_t* d, uint8_t* m, uint16_t* a)
{
	uint8_t I2CMasterBuffer[BUFSIZE];
	uint8_t I2CSlaveBuffer[4];
	uint32_t I2CReadLength, I2CWriteLength;
	WaitI2CMasterState(LPC_I2C0, I2C_STAT_MSTST_IDLE);
	I2CWriteLength = 1;
	I2CReadLength = 4;
	I2CMasterBuffer[0] = 0xD0;
	I2CMasterBuffer[1] = 0x03;
	I2CmasterWriteRead(I2CMasterBuffer, I2CSlaveBuffer, I2CWriteLength,
	I2CReadLength);
	*j = (I2CSlaveBuffer[0]&0x0F);
	*d = ((I2CSlaveBuffer[1]&0xF0)>>4)*10+ (I2CSlaveBuffer[1]&0x0F);
	*m = ((I2CSlaveBuffer[2]&0xF0)>>4)*10+ (I2CSlaveBuffer[2]&0x0F);
	*a = 2000 + ((I2CSlaveBuffer[3]&0xF0)>>4)*10+ (I2CSlaveBuffer[3]&0x0F);
}

void write_time(uint8_t h, uint8_t m, uint8_t s) {
	uint8_t I2CMasterBuffer[BUFSIZE];
	uint32_t I2CWriteLength;
	WaitI2CMasterState(LPC_I2C0, I2C_STAT_MSTST_IDLE);
	I2CWriteLength = 4;
	I2CMasterBuffer[0] = 0xD0;
	I2CMasterBuffer[1] = 0x00;
	I2CMasterBuffer[2] = (s/10)*16 + (s%10);
	I2CMasterBuffer[3] = (m/10)*16 + (m%10);
	I2CMasterBuffer[4] = (h/20)*32 + (h/10 % 2)*16 + (h%10);
	I2CmasterWrite(I2CMasterBuffer, I2CWriteLength);
}

void write_date(uint8_t j, uint8_t d, uint8_t m, uint16_t a) {
	uint8_t I2CMasterBuffer[BUFSIZE];
	uint32_t I2CWriteLength;
	WaitI2CMasterState(LPC_I2C0, I2C_STAT_MSTST_IDLE);
	a = a - 2000;
	I2CWriteLength = 5;
	I2CMasterBuffer[0] = 0xD0;
	I2CMasterBuffer[1] = 0x03;
	I2CMasterBuffer[2] = j;
	I2CMasterBuffer[3] = (d/10)*16 + (d%10);
	I2CMasterBuffer[4] = (m/10)*16+(m%10);
	I2CMasterBuffer[5] = (a/10)*16+(a%10);
	I2CmasterWrite(I2CMasterBuffer, I2CWriteLength);
}
