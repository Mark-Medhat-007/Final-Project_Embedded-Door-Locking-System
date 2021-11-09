/*
 * delay.c
 *
 *  Created on: Nov 9, 2021
 *      Author: marcm
 */


#include "delay.h"

uint16	 Timer_Counter=0;
Timer0_ConfigType Config;



void delay_Timer0(uint8 cmp_value,uint8 Num_Secs){
	Config.clock=F_CPU_1024;
	Config.mode=CTC;
	Config.compare_value=cmp_value;
	Config.pin=DISCONNECTED_OC0;
	Timer0_setCallBack(&delay_ISR);
	Timer0_init(&Config);
	while(Timer_Counter<=(Num_Secs*31)){}
	Timer0_DeInit();
	Timer_Counter=0;
}

void delay_ISR(void){
	Timer_Counter++;

}
