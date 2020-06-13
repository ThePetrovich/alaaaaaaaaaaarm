#include "alarm.h"

extern unsigned long int fix_PanikDelay;

static unsigned int fireChecksCount = 0;
static unsigned int fireChecksDetected = 0;
static unsigned int fireChecksFalse = 0;
static bool fireTriggered = false;

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
	fix_PanikDelay = millis();
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
	if (result <= 512 && !fireTriggered) {
		fireTriggered = true;
	}
	
	if (fireTriggered) {
		if (fsm_getState() == FSM_STATE_ALARMED) {
			delay(1);
			fireChecksCount++;
			result = analogRead(FIRE_ALARM_PIN);
			if (result <= 512) {
				fireChecksDetected++;
			}
			else {
				fireChecksFalse++;
			}
		}
	}
	
	if (fireChecksCount >= 1000) {
		if (fireChecksDetected > fireChecksFalse) {
			if (fsm_getState() == FSM_STATE_ALARMED) {
				fsm_setState(FSM_STATE_PANIK);
				Serial.println(F("Debug: oh noes, fire detected"));
			}
		}
		fireTriggered = false;
		fireChecksCount = 0;
		fireChecksDetected = 0;
		fireChecksFalse = 0;
	}
	
	return result;
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