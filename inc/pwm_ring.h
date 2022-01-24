/*
 *	File :		pwm_ring.h
 *	Author :	Rida Lali
 *	Task :		Fichier pour la sonnerie en PWM
 */

#ifndef INC_PWM_RING_H_
#define INC_PWM_RING_H_

#define NNOTES 22
#define MUSICENABLE (currentNote >= NNOTES*2+1)

uint8_t ringtone[NNOTES];
float notes[4];
uint8_t currentNote;

void set_ctimer5();
void init_MRT0(float frequency);
void MRT_IRQHandler();
void setNextKey();
void MRT0_setFrequency(float frequency);
void set_PWM(float frequency, float dutyCycle);

#endif /* INC_PWM_RING_H_ */
