/*
 * Timer0.h
 *
 *  Created on: Nov 5, 2021
 *      Author: marcm
 */

#ifndef TIMER0_H_
#define TIMER0_H_

#include <avr/io.h>
#include "common_macros.h"
#include "std_types.h"
#include <avr/interrupt.h> /* For ICU ISR */

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,F_CPU_EXTERNAL_FALLING,F_CPU_EXTERNAL_RISING
}Timer0_Clock;

typedef enum
{
	NORMAL,CTC
}Timer0_mode;
typedef enum
{
	DISCONNECTED_OC0,TOGGLE_OC0,CLEAR_OC0,SET_OC0
}OC0_mode;

typedef struct
{
	Timer0_Clock clock;
	Timer0_mode mode;
	uint8 compare_value;
	OC0_mode pin;
}Timer0_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Timer0_init(const Timer0_ConfigType * Config_Ptr);
void Timer0_setCallBack(void(*a_ptr)(void));
void Timer0_DeInit(void);



#endif /* TIMER0_H_ */
