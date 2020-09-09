#include "alarm.h"

const uint32_t debounceDelay = 300;

struct buttonSrtuct_t {
	uint8_t lastState;
	uint8_t state;
	uint8_t bswitch;
	uint32_t debounce;
	int pin;
};

void buttons_setupButton(struct buttonStruct* button, int pin)
{
	button->lastState = 0;
	button->state = 0;
	button->bswitch = 0;
	button->debounce = 0;
	button->pin = pin;

	pinMode(pin, INPUT);
}

uint8_t buttons_checkButton(struct buttonStruct* button)
{
	uint8_t reading = digitalRead(button->pin);

	if (reading != button->lastState) {
		button->debounce = millis();
	}

	if ((millis() - button->debounce) > debounceDelay) {
		if (reading != button->state) {
			button->state = reading;

			if (reading == HIGH) {
				button->switch = !button->switch;
			}
		}
	}

	button->lastState = reading;
	return reading;
}