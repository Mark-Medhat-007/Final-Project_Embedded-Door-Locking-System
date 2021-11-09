/*
 * First_MicroController.c
 *
 *  Created on: Nov 6, 2021
 *      Author: marcm
 */
# define F_CPU 8000000UL
#include "First_MicroController.h"


uint8 First_Time_Pass(uint8 *ptr){		/*function to get password and send it to the other micro controller in first time only*/
	uint8 PassCheck=1;
	LCD_clearScreen();
	LCD_displayString("enter new pass");
	LCD_moveCursor(1,0);
	read_write_pass(ptr);
	LCD_clearScreen();
	LCD_displayString("enter same pass");
	LCD_moveCursor(1,0);
	PassCheck=check_pass(ptr);
	LCD_clearScreen();
	if (PassCheck==0){
		LCD_displayString("Password Saved");
		return TRUE;
	}
	else{
		LCD_clearScreen();
		LCD_displayString("pass not matched");
		return FALSE;
	}

}
void read_write_pass(uint8 *ptr){	/*function to get pass from keypad and save it in string */
		uint8 i=0;
		uint8 key;					/*Taking pass from 1 character to 16 character as user decides and presses enter*/

		do{
			key = KEYPAD_getPressedKey(); /* get the pressed key number */
			_delay_ms(400);
			if(i==16){
				break;
			}
			if(((key <= 9) && (key >= 0)) || (key==ENTER))
					{
						if(key==ENTER){
						*(ptr+i)=key;
							}
						else{
							LCD_displayCharacter('*');	/* display the pressed keypad switch */
						*(ptr+i)=key+48;
						}
					}
			i++;
		}while(*(ptr+(i-1))!=ENTER);

		if(i!=16){
			*(ptr+(i-1))=NULL_PTR;
		}
		else{
			*(ptr+16)=NULL_PTR;
		}
}
uint8 check_pass(uint8 *ptr){	/*function to check pass 1 and pass 2*/
	uint8 pass[17];
	read_write_pass(pass);
	return strcmp(ptr,pass);
	}

void menu(uint8 *ptr,uint8 *pass_Limit){	/* this is the main menu of the first micro controller*/
	uint8 key;
	uint8 pass_State=0;						/* flag gets 1 if the second micro controler sends correct pass in open door switch case*/
	uint8 pass_State_1=0;					/* flag gets 1 if the second micro controler sends correct pass in change password switch case*/
	LCD_clearScreen();
	LCD_displayString("+: Open Door");
	LCD_displayStringRowColumn(1,0,"-: Change Pass");
	key = KEYPAD_getPressedKey(); 			/* get the pressed key number */
	_delay_ms(400);
	if(key=='+'){
		UART_sendByte(OPEN_DOOR);
		LCD_clearScreen();
		LCD_displayString("enter password");
		LCD_moveCursor(1,0);
		read_write_pass(ptr);
		Null_to_Hash(ptr);
		UART_sendString(ptr);
		_delay_ms(200);
		pass_State=UART_recieveByte();
		switch(pass_State){			/*switch case for pass if it is correct or invalid*/
		case CORRECT_PASS:
			LCD_clearScreen();
			LCD_displayString("CORRECT PASS");
			LCD_moveCursor(1,0);
			LCD_displayString("DOOR UNLOCKED");
			delay_Timer0(250,33);		/*delay function by timer0*/
			*pass_Limit=0;				/* reseting pass limiter if the user enter correct pass*/
			break;

		case INVALID_PASS:
			LCD_clearScreen();
			LCD_displayString("INVALID PASS");
			LCD_moveCursor(1,0);
			LCD_displayString("DOOR LOCKED");
			_delay_ms(3000);
			pass_State=0;
			(*pass_Limit)++;			/* incrementing pass limiter if the user enter invalid  pass*/
			break;
		}

	}
	else if(key=='-'){
		UART_sendByte(CHANGE_PASS);
		LCD_clearScreen();
		LCD_displayString("enter password");
		LCD_moveCursor(1,0);
		read_write_pass(ptr);
		Null_to_Hash(ptr);
		UART_sendString(ptr);
		_delay_ms(200);
		pass_State_1=UART_recieveByte();
		switch(pass_State_1){
		case CORRECT_PASS:
			LCD_clearScreen();
			LCD_displayString("CORRECT PASS");
			LCD_moveCursor(1,0);
			_delay_ms(1000);
			send_pass(ptr);
			pass_State_1=0;
			*pass_Limit=0;
			break;

		case INVALID_PASS:
			LCD_clearScreen();
			LCD_displayString("INVALID PASS");
			LCD_moveCursor(1,0);
			_delay_ms(1000);
			pass_State_1=0;
			(*pass_Limit)++;
			break;
		default:
			LCD_clearScreen();
			LCD_intgerToString(pass_State_1);
			_delay_ms(1000);
			break;
		}
	}

}
void Null_to_Hash(uint8 *ptr){ 		/*function to replace null in string by hash to get sent by uart*/
	int i=0;
	while(1){
	if (ptr[i]==NULL_PTR){
		ptr[i]='#';
		break;
		}
	i++;
	}
}
void send_pass(uint8 *pass){		/*function to send password by uart*/
	uint8 state= FALSE;
	while (state==FALSE){
			state=First_Time_Pass(pass);
			_delay_ms(2000);
			}
		Null_to_Hash(pass);
		UART_sendByte(SEND_PASS);
		UART_sendString(pass);	/* Send the required string to MC2 through UART */
}
