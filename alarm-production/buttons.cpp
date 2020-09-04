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
	//buttonFailsafe.begin();
	//buttonOpen.begin();
	buttonDetector.begin();
}

void buttonFailsafe_pressed() 
{
	actions_openDoor();
	for (int i = 0; i < FAILSAFE_BUTTON_DURATION_MS/250; i++) {
		delay(250);
		digitalWrite(LED_KALM_PIN, !digitalRead(LED_KALM_PIN));
	}
	actions_closeDoor();
}


void buttonOpen_pressed() 
{
	actions_openDoor();
	for (int i = 0; i < OPEN_BUTTON_DURATION_MS/250; i++) {
		delay(250);
		digitalWrite(LED_KALM_PIN, !digitalRead(LED_KALM_PIN));
	}
	actions_closeDoor();
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

/*
int buttons_checkFailsafe()
{
	if (buttonFailsafe.toggled()) {
		if (buttonFailsafe.read() == Button::PRESSED) {
			Serial.println(F("Debug: FAILSAFE button pressed"));
			buttonFailsafe_pressed();
			return 1;
		}
		else {
			Serial.println(F("Debug: FAILSAFE button released"));
			return -1;
		}	
	}
	return 0;
}

int buttons_checkOpen()
{
	if (buttonOpen.toggled()) {
		if (buttonOpen.read() == Button::PRESSED) {
			Serial.println(F("Debug: OPEN button pressed"));
			buttonOpen_pressed();
			return 1;
		}
		else {
			Serial.println(F("Debug: OPEN button released"));
			return -1;
		}	
	}
	return 0;
}*/