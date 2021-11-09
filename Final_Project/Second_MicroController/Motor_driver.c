/*
 * Motor_driver.c
 *
 *  Created on: Oct 15, 2021
 *      Author: marcm
 */
#include "common_macros.h"
#include "gpio.h"
#include "Motor_driver.h"

void DcMotor_Init(void){
	GPIO_setupPinDirection(PORTD_ID, PIN2_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN3_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
	GPIO_writePin(PORTD_ID, PIN2_ID, LOGIC_LOW);
	GPIO_writePin(PORTD_ID, PIN3_ID, LOGIC_LOW);
	GPIO_writePin(PORTD_ID, PIN4_ID, LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state){
	switch(state){
	case CW:
		GPIO_writePin(PORTD_ID, PIN2_ID, LOGIC_HIGH);
		GPIO_writePin(PORTD_ID, PIN3_ID, LOGIC_LOW);
		GPIO_writePin(PORTD_ID, PIN4_ID, LOGIC_HIGH);
		break;
	case CCW:
		GPIO_writePin(PORTD_ID, PIN2_ID, LOGIC_LOW);
		GPIO_writePin(PORTD_ID, PIN3_ID, LOGIC_HIGH);
		GPIO_writePin(PORTD_ID, PIN4_ID, LOGIC_HIGH);
		break;
	case STOP:
		GPIO_writePin(PORTD_ID, PIN2_ID, LOGIC_LOW);
		GPIO_writePin(PORTD_ID, PIN3_ID, LOGIC_LOW);
		GPIO_writePin(PORTD_ID, PIN4_ID, LOGIC_LOW);
		break;
	}


}


