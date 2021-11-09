/*
 * main1.c
 *
 *  Created on: Nov 6, 2021
 *      Author: marcm
 */

# define F_CPU 8000000UL
#include "First_MicroController.h"
#include "delay.h"


int main(void)
{

	uint8 state= FALSE; 	/*  for entering password for first time*/
	uint8 Pass_Limit=0;		/* counter for invalid  passwords*/
	uint8 pass[17];			/* array of uint8 to save the password and send it by UART*/
	UART_init(9600);		/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	LCD_init();				/* for initiating LCD */
	while (state==FALSE){
		state=First_Time_Pass(pass);	/*function to take password and save it*/
		 delay_Timer0(250,2);			/*delay function by timer0*/
		}
	Null_to_Hash(pass);					/* function to replace NULL at the end of array by hash*/
	UART_sendByte(SEND_PASS);			/* sending command to the second micro controller  */
	UART_sendString(pass);	/* Send the required string to MC2 through UART */
    while(1)
    {
    	menu(pass,&Pass_Limit);		/* menu function*/
    	if(Pass_Limit==3){			/* condition will be active if user entered wrong pass 3 times*/
    		LCD_clearScreen();
    		LCD_displayString("ALERT!!!!");
    		UART_sendByte(ACTIVATE_BUZZER);		/*send command activate buzzer to the second micro controller*/

    		delay_Timer0(250,60);	/*delay function by timer0*/
    		Pass_Limit=0;			/*clearing counter */
    	}
    }
}
