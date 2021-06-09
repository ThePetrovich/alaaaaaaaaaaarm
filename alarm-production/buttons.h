/*
 * buttons.h
 * 
 * Created: 09.06.2021 07:30:41
 * Author: ThePetrovich
 */


#ifndef _BUTTONS_ALARM_H_
#define _BUTTONS_ALARM_H_

#include <stdint.h>

typedef struct alarm_button {
	uint8_t lastState;
	uint8_t state;
	uint8_t bswitch;
	uint32_t debounce;
	int pin;
} alarm_button;

void buttons_setupButton(alarm_button *button, int pin);
uint8_t buttons_readButton(alarm_button *button);
uint8_t buttons_checkButton(alarm_button *button);
uint8_t buttons_checkSwitch(alarm_button *button);

#endif