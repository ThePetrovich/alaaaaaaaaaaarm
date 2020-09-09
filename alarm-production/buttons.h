#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#include <arduino.h>
#include <stdint.h>

struct buttonStruct_t {
	uint8_t lastState;
	uint8_t state;
	uint8_t bswitch;
	uint32_t debounce;
	int pin;
};

void buttons_setupButton(struct buttonStruct_t *button, int pin);
uint8_t buttons_readButton(struct buttonStruct_t *button);
uint8_t buttons_checkButton(struct buttonStruct_t *button);
uint8_t buttons_checkSwitch(struct buttonStruct_t *button);

#endif