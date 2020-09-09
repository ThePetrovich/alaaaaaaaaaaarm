#include "buttons.h"
#include <stdint.h>

const uint32_t debounceDelay = 300;

void buttons_setupButton(struct buttonStruct_t *button, int pin)
{
	button->lastState = 0;
	button->state = 0;
	button->bswitch = 0;
	button->debounce = 0;
	button->pin = pin;

	pinMode(pin, INPUT);
}

uint8_t buttons_readButton(struct buttonStruct_t *button)
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

uint8_t buttons_checkButton(struct buttonStruct_t *button)
{
	return button->state;
}

uint8_t buttons_checkSwitch(struct buttonStruct_t *button)
{
	return button->bswitch;
}