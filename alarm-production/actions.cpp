#include "alarm.h"
/*
void actions_openDoor(); 
void actions_closeDoor();

void actions_WeeWooWeeWoo(); //Enables the loud thingy
void actions_calmTFDown(); //Disables the loud thingy

int actions_sniff(); //Checks the smoke detector

void actions_bonk(); //Disables everything */

void actions_setup()
{
	pinMode(MOSFET_SOLENOID_THING, OUTPUT);
	pinMode(MOSFET_LOUD_THING, OUTPUT);
	pinMode(MOSFET_BLINKY_THING, OUTPUT);
	pinMode(LED_ALARMED_PIN, OUTPUT);
	pinMode(LED_KALM_PIN, OUTPUT);
}

void actions_openDoor()
{
	Serial.println(F("Debug: opening the door"));
	digitalWrite(MOSFET_SOLENOID_THING, HIGH);
}

void actions_closeDoor()
{
	Serial.println(F("Debug: Closing the door"));
	digitalWrite(MOSFET_SOLENOID_THING, LOW);
}

void actions_WeeWooWeeWoo()
{
	Serial.println(F("Debug: enabling the alarm"));
	digitalWrite(MOSFET_LOUD_THING, HIGH);
	digitalWrite(MOSFET_BLINKY_THING, HIGH);
}

void actions_calmTFDown()
{
	Serial.println(F("Debug: disabling the alarm"));
	digitalWrite(MOSFET_LOUD_THING, LOW);
	digitalWrite(MOSFET_BLINKY_THING, LOW);
}

int actions_sniff()
{
	int result = analogRead(FIRE_ALARM_PIN);
	Serial.print(F("Debug: sniffing: "));
	Serial.println(result);
	if (result <= 512) {
		if (fsm_getState() == FSM_STATE_ALARMED) {
			Serial.println(F("Debug: oh noes, fire detected"));
			fsm_setState(FSM_STATE_PANIK);
		}
	}
}

void actions_bonk()
{
	actions_calmTFDown();
	fsm_setState(FSM_STATE_KALM);
}

void actions_ledAlarmed() 
{
	digitalWrite(LED_ALARMED_PIN, HIGH);
	digitalWrite(LED_KALM_PIN, LOW);
}

void actions_ledKalm() 
{
	digitalWrite(LED_ALARMED_PIN, LOW);
	digitalWrite(LED_KALM_PIN, HIGH);
}