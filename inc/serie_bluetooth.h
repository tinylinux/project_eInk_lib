/*
 *	File :		serie_bluetooth.h
 *	Author :	Rida Lali
 *	Task :		Module pour l'utilisation
 *				du bluetooth
 */

#ifndef SERIE_BLUETOOTH_H_
#define SERIE_BLUETOOTH_H_

void set_bluetooth();
char check_bluetooth_received();
void send_bluetooth(char* phrase);

#endif /* SERIE_BLUETOOTH_H_ */
