/*
 * Buzzer.c
 *
 *  Created on: Nov 8, 2021
 *      Author: marcm
 */

#include "Buzzer.h"


void Buzzer_init(void){
	GPIO_setupPinDirection(BUZZER_PORT_ID , BUZZER_PIN_ID , PIN_OUTPUT);
}

void Buzzer_Start(void){
	GPIO_writePin(BUZZER_PORT_ID ,  BUZZER_PIN_ID, LOGIC_HIGH );
}
void Buzzer_stop(void){
	GPIO_writePin(BUZZER_PORT_ID ,  BUZZER_PIN_ID, LOGIC_LOW );
}
