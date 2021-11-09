/*
 * Buzzer.h
 *
 *  Created on: Nov 8, 2021
 *      Author: marcm
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#define BUZZER_PORT_ID                 PORTD_ID
#define BUZZER_PIN_ID                  PIN7_ID
#include "gpio.h"
#include "std_types.h"

void Buzzer_init(void);
void Buzzer_Start(void);
void Buzzer_stop(void);
#endif /* BUZZER_H_ */
