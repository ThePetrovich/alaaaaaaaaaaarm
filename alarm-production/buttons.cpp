#include "alarm.h"

Button buttonEnable(BUTTON_ENABLE_PIN);
Button buttonDisable(BUTTON_DISABLE_PIN);
Button buttonFailsafe(BUTTON_FAILSAFE_PIN);
Button buttonOpen(BUTTON_OPEN_PIN);
Button buttonDetector(BUTTON_DOOR_PIN);

void buttons_setup()
{
	buttonEnable.begin();
	buttonDisable.begin();
	buttonFailsafe.begin();
	buttonOpen.begin();
	buttonDetector.begin();
}

void buttonEnable_pressed() 
{
	int currentState = fsm_getState();
	
	if (currentState == FSM_STATE_KALM) {
		for (int i = 0; i < 40; i++) {
			delay(250);
			digitalWrite(LED_ALARMED_PIN, !digitalRead(LED_ALARMED_PIN));
		}
		fsm_setState(FSM_STATE_ALARMED);
	}
}

void buttonDisable_pressed() 
{	
	fsm_setState(FSM_STATE_KALM);
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

void buttonDetector_pressed() 
{
	int currentState = fsm_getState();
	if (currentState == FSM_STATE_ALARMED) {
		fsm_setState(FSM_STATE_PANIK);
	}
}

void buttons_check()
{
	if (buttonEnable.toggled()) {
		if (buttonEnable.read() == Button::PRESSED) {
			Serial.println(F("Debug: ENABLE button pressed"));
			buttonEnable_pressed();
		}
		else {
			Serial.println(F("Debug: ENABLE button released"));
		}	
	}
	if (buttonDisable.toggled()) {
		if (buttonDisable.read() == Button::PRESSED) {
			Serial.println(F("Debug: DISABLE button pressed"));
			buttonDisable_pressed();
		}
		else {
			Serial.println(F("Debug: DISABLE button released"));
		}	
	}
	if (buttonFailsafe.toggled()) {
		if (buttonFailsafe.read() == Button::PRESSED) {
			Serial.println(F("Debug: FAILSAFE button pressed"));
			buttonFailsafe_pressed();
		}
		else {
			Serial.println(F("Debug: FAILSAFE button released"));
		}	
	}
	if (buttonOpen.toggled()) {
		if (buttonOpen.read() == Button::PRESSED) {
			Serial.println(F("Debug: OPEN button pressed"));
			buttonOpen_pressed();
		}
		else {
			Serial.println(F("Debug: OPEN button released"));
		}	
	}
}

void buttons_checkDetector()
{
	if (buttonDetector.toggled()) {
		if (buttonDetector.read() == Button::PRESSED) {
			Serial.println(F("Debug: DETECTOR button pressed"));
		}
		else {
			Serial.println(F("Debug: DETECTOR button released"));
			buttonDetector_pressed(); //This is a limit switch, so it is inverted
		}	
	}
}