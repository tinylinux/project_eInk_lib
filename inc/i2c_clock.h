/*
 *	File :		i2c_clock.h
 *	Author :	Rida Lali
 *	Task :		Module pour la gestion de l'horloge
 */

#ifndef INC_I2C_CLOCK_H_
#define INC_I2C_CLOCK_H_

void set_clock();
void read_time(uint8_t* h, uint8_t* m, uint8_t* s);
void read_date(uint8_t* j, uint8_t* d, uint8_t* m, uint16_t* a);
void write_time(uint8_t h, uint8_t m, uint8_t s);
void write_date(uint8_t j, uint8_t d, uint8_t m, uint16_t a);

#endif /* INC_I2C_CLOCK_H_ */
