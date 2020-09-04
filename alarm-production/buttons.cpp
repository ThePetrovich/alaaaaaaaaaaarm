#include "alarm.h"
#include <Button.h>

Button buttonEnable(BUTTON_ENABLE_PIN);
Button buttonDisable(BUTTON_DISABLE_PIN);
//Button buttonFailsafe(BUTTON_FAILSAFE_PIN);
//Button buttonOpen(BUTTON_OPEN_PIN);
Button buttonDetector(BUTTON_DOOR_PIN);

void buttons_setup()
{
	buttonEnable.begin();
	buttonDisable.begin();
	buttonDetector.begin();
}

int buttons_checkDetector()
{
	if (buttonDetector.toggled()) {
		if (buttonDetector.read() == Button::PRESSED) {
			Serial.println(F("Debug: DETECTOR button pressed"));
			return 1;
		}
		else {
			Serial.println(F("Debug: DETECTOR button released"));
			return -1;
		}	
	}
	return 0;
}

int buttons_checkEnable()
{
	if (buttonEnable.toggled()) {
		if (buttonEnable.read() == Button::PRESSED) {
			Serial.println(F("Debug: ENABLE button pressed"));
			return 1;
		}
		else {
			Serial.println(F("Debug: ENABLE button released"));
			return -1;
		}	
	}
	return 0;
}

int buttons_checkDisable()
{
	if (buttonDisable.toggled()) {
		if (buttonDisable.read() == Button::PRESSED) {
			Serial.println(F("Debug: DISABLE button pressed"));
			return 1;
		}
		else {
			Serial.println(F("Debug: DISABLE button released"));
			return -1;
		}	
	}
	return 0;
}