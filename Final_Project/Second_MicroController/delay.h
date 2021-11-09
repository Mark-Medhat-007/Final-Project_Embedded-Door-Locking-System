/*
 * delay.h
 *
 *  Created on: Nov 9, 2021
 *      Author: marcm
 */

#ifndef DELAY_H_
#define DELAY_H_
#include "Timer0.h"

void delay_Timer0(uint8 cmp_value,uint8 Num_Secs);
void delay_ISR(void);
#endif /* DELAY_H_ */
