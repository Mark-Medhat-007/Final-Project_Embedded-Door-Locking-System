/*
 * Second_MicroController.h
 *
 *  Created on: Nov 6, 2021
 *      Author: marcm
 */

#ifndef SECOND_MICROCONTROLLER_H_
#define SECOND_MICROCONTROLLER_H_
# define F_CPU 8000000UL
#include "std_types.h"
#include "lcd.h"
#include "uart.h"
#include "Motor_driver.h"
#include "util/delay.h"
#include "twi.h"
#include "external_eeprom.h"
#include "Buzzer.h"
/*#define MC2_READY 0x10*/


typedef enum
{
	RECEIVE_PASS,OPEN_DOOR,CHANGE_PASS,ACTIVATE_BUZZER
}Address;   /* Address of commands*/

typedef enum
{
	CORRECT_PASS=10,INVALID_PASS
}passtype;

void save_pass(uint8 *ptr);
uint8 compare_pass(uint8 *ptr1,uint8 *ptr2);


#endif /* SECOND_MICROCONTROLLER_H_ */
