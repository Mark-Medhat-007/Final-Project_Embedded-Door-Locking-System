/*
 * Timer0.c
 *
 *  Created on: Nov 5, 2021
 *      Author: marcm
 */
#include "Timer0.h"
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;


/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void Timer0_init(const Timer0_ConfigType * Config_Ptr){
	TCNT0 = 0;
	SREG  |= (1<<7);
	SET_BIT(TCCR0,FOC0);			/*Non PWM mode FOC0=1*/
	TCCR0=(TCCR0 & 0xF8) | (Config_Ptr->clock);	/*Configuring F_CPU*/
	if(Config_Ptr->mode==NORMAL){
		SET_BIT(TIMSK,TOIE0);		/*Enable Timer0 Overflow Interrupt*/
		CLEAR_BIT(TCCR0,WGM01);
		CLEAR_BIT(TCCR0,WGM00); 	/*Normal Mode WGM01=0 & WGM00=0*/
		CLEAR_BIT(TCCR0,COM00);
		CLEAR_BIT(TCCR0,COM01);		/*Normal Mode COM00=0 & COM01=0*/
	}
	else if(Config_Ptr->mode==CTC){
		SET_BIT(TIMSK,OCIE0);		/*Enable Timer0 Compare Interrupt*/
		SET_BIT(TCCR0,WGM01);
		OCR0  =Config_Ptr->compare_value ;
		CLEAR_BIT(TCCR0,WGM00); 	/*Compare Mode WGM01=1 & WGM00=0*/
		if (Config_Ptr->pin==DISCONNECTED_OC0){
			CLEAR_BIT(TCCR0,COM00);
			CLEAR_BIT(TCCR0,COM01);
		}
		else if(Config_Ptr->pin==TOGGLE_OC0){
			SET_BIT(TCCR0,COM00);
			CLEAR_BIT(TCCR0,COM01);
		}
		else if(Config_Ptr->pin==CLEAR_OC0){
			SET_BIT(TCCR0,COM01);
			CLEAR_BIT(TCCR0,COM00);
		}
		else if(Config_Ptr->pin==CLEAR_OC0){
			SET_BIT(TCCR0,COM01);
			SET_BIT(TCCR0,COM00);
		}
	}
}


void Timer0_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

void Timer0_DeInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR0 = 0;

	/* Disable the Input Capture interrupt */
	CLEAR_BIT(TIMSK,TOIE0);
	CLEAR_BIT(TIMSK,OCIE0);
}
