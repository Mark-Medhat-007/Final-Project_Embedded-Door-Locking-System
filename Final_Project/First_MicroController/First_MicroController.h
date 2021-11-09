/*
 * First_MicroController.h
 *
 *  Created on: Nov 6, 2021
 *      Author: marcm
 */

#ifndef FIRST_MICROCONTROLLER_H_
#define FIRST_MICROCONTROLLER_H_

# define F_CPU 8000000UL
#include "lcd.h"
#include "keypad.h"
#include "std_types.h"
#include "util/delay.h"
#include "uart.h"
#include "Timer0.h"


#define ENTER 13
/*#define MC2_READY 0x10*/

typedef enum
{
	SEND_PASS,OPEN_DOOR,CHANGE_PASS,ACTIVATE_BUZZER
}Address;   /* Address of commands*/

typedef enum
{
	CORRECT_PASS=10,INVALID_PASS
}passtype;

uint8 First_Time_Pass(uint8 *ptr);
void read_write_pass(uint8 *ptr);
uint8 check_pass(uint8 *ptr);
void menu(uint8 *ptr,uint8 *pass_Limit);
void Null_to_Hash(uint8 *ptr);
void send_pass(uint8 *pass);

#endif /* FIRST_MICROCONTROLLER_H_ */
