/*
 * buttons.cpp
 * 
 * Created: 09.06.2021 07:30:35
 * Author: ThePetrovich
 */


#include <Arduino.h>
#include <stdint.h>
#include "buttons.h"

const uint32_t debounceDelay = 300;

void buttons_setupButton(alarm_button *button, int pin)
{
	button->lastState = 0;
	button->state = 0;
	button->bswitch = 0;
	button->debounce = 0;
	button->pin = pin;

	pinMode(pin, INPUT);
}

uint8_t buttons_readButton(alarm_button *button)
{
	uint8_t reading = digitalRead(button->pin);

	if (reading != button->lastState) {
		button->debounce = millis();
	}

	if ((millis() - button->debounce) > debounceDelay) {
		if (reading != button->state) {
			button->state = reading;

			if (reading == HIGH) {
				button->bswitch = !button->bswitch;
			}
		}
	}

	button->lastState = reading;
	return reading;
}

uint8_t buttons_checkButton(alarm_button *button)
{
	return button->state;
}

uint8_t buttons_checkSwitch(alarm_button *button)
{
	return button->bswitch;
}