/*
 * main2.c
 *
 *  Created on: Nov 6, 2021
 *      Author: marcm
 */

# define F_CPU 8000000UL
#include "Second_MicroController.h"


int main(void)
{
	uint8 pass[17];
	uint8 Npass[17];
	uint8 state=1;				/*flag for checking the string compare function value*/
	Address command_Address; 	/*variable for selecting command*/
	UART_init(9600);			/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	LCD_init();					/* Initialize the LCD Driver */
	DcMotor_Init();				/* Initialize the DC MOTOR Driver */
	TWI_init();					/* Initialize the I2C Driver */
	Buzzer_init();				/* Initialize the BUZZER Driver */

    while(1){
    	command_Address=UART_recieveByte(); 	/*Micro controller  command address */
    	switch(command_Address){				/* switch case for commands*/
    	case RECEIVE_PASS:
    		UART_receiveString(pass);	/* Receive Password from MC1 through UART */
    		save_pass(pass);			/* saving password at EEPROM by I2C*/

    		break;
    	case OPEN_DOOR:
    		UART_receiveString(Npass);			/*recieving pass from user*/
    		state=compare_pass(pass,Npass);		/*comparing password that user entered and pass saved in EEPROM*/
    		if(state==0){						/*checking the validation of password*/
    			_delay_ms(200);
    			UART_sendByte(CORRECT_PASS);	/* sending the decision for the first micro controller*/
    			DcMotor_Rotate(CW);				/* Function to rotate motor Clock-wise*/
    			delay_Timer0(250,15);			/*delay function by timer0*/
    			DcMotor_Rotate(STOP);
    			delay_Timer0(250,3);
    			DcMotor_Rotate(CCW);
    			delay_Timer0(250,15);
    			DcMotor_Rotate(STOP);
    		}
    		else if(state!=0){					/*checking the validation of password*/
    			_delay_ms(200);
    			UART_sendByte(INVALID_PASS);	/* sending invalid command to micro conroller*/
    		}
    		break;
    	case CHANGE_PASS:
    		UART_receiveString(Npass);			/*Receiving entered password from other micro controller*/
    		state=compare_pass(pass,Npass);		/*comparing password that user entered and pass saved in EEPROM*/
    		if(state==0){						/*checking the validation of password*/
    			_delay_ms(200);
    			UART_sendByte(CORRECT_PASS);
    		}
    		else if(state!=0){					/*checking the validation of password*/
    			_delay_ms(200);
    			UART_sendByte(INVALID_PASS);
    		}
    		break;
    	case ACTIVATE_BUZZER:					/* activating buzzer command*/
    		Buzzer_Start();
    		delay_Timer0(250,60);
    		Buzzer_stop();
    		break;
    	}

    }
}
