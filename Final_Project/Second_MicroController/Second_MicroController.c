/*
 * Second_MicroController.c
 *
 *  Created on: Nov 6, 2021
 *      Author: marcm
 */

/*# define F_CPU 8000000UL*/
#include "Second_MicroController.h"


void save_pass(uint8 *ptr){
	uint8 i=0;
	while(ptr[i]!=NULL_PTR){
	EEPROM_writeByte(0x0311+i, ptr[i]); 			/* Write 0x0F in the external EEPROM */
			_delay_ms(40);
	i++;
	}
	EEPROM_writeByte(0x0311+i, ptr[i]);
	/*LCD_displayString("save is done");*/
}

uint8 compare_pass(uint8 *ptr1,uint8 *ptr2){
	uint8 i=0;
	uint8 x=0;
	while(1){
			EEPROM_readByte(0x0311+i,(ptr1+i));		/* Write 0x0F in the external EEPROM */
			if(ptr1[i]==NULL_PTR){
				break;
			}
			i++;
	}
	x=strcmp(ptr1,ptr2);
	if (x==0){
		LCD_clearScreen();
		LCD_displayString("correct ");
		return 0;
	}
	else{
		LCD_clearScreen();
		LCD_displayString("invalid ");
		return 1;
	}

}
