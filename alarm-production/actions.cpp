/*
 * actions.cpp
 * 
 * Created: 09.06.2021 07:30:35
 * Author: ThePetrovich
 */


#include <Arduino.h>
#include "actions.h"
#include "buttons.h"
#include "statemachine.h"
#include "alarm.h"

extern unsigned long int fix_PanikDelay;
static unsigned long int act_blinkStart = 0;
static unsigned int act_blinkPeriod = 0;
static bool act_alarmLedState = false;

static alarm_button detector;
static alarm_button enable;
static alarm_button disable;

void actions_setup()
{
	pinMode(DOOR_OPEN_PIN, OUTPUT);
	pinMode(MOSFET_LOUD_THING, OUTPUT);
	pinMode(MOSFET_BLINKY_THING, OUTPUT);
	pinMode(LED_ALARMED_PIN, OUTPUT);
	pinMode(LED_KALM_PIN, OUTPUT);

	buttons_setupButton(&detector, OPEN_DETECT_PIN);
	buttons_setupButton(&enable, BUTTON_ENABLE_PIN);
	buttons_setupButton(&disable, BUTTON_DISABLE_PIN);
}

uint8_t actions_checkDetector()
{
	buttons_readButton(&detector);
	uint8_t result = buttons_checkButton(&detector);
	return result;
}

uint8_t actions_checkEnable()
{
	buttons_readButton(&enable);
	uint8_t result = buttons_checkButton(&enable);
	return result;
}

uint8_t actions_checkDisable()
{
	buttons_readButton(&disable);
	uint8_t result = buttons_checkButton(&disable);
	return result;
}

void actions_readAllButtons()
{
	buttons_readButton(&detector);
	buttons_readButton(&disable);
	buttons_readButton(&enable);
}

void actions_WeeWooWeeWoo()
{
	//Serial.println(F("[Debug] actions: enabling the alarm"));
	digitalWrite(MOSFET_LOUD_THING, HIGH);
	actions_blinkAlarm();
}

void actions_calmTFDown()
{
	//Serial.println(F("[Debug] actions: disabling the alarm"));
	digitalWrite(MOSFET_LOUD_THING, LOW);
	digitalWrite(MOSFET_BLINKY_THING, LOW);
}

int actions_sniff()
{
	int returnCode = 0;
	static unsigned int fireChecksCount = 0;
	static unsigned int fireChecksDetected = 0;
	static unsigned int fireChecksFalse = 0;
	static bool fireTriggered = false;

	int result = analogRead(FIRE_ALARM_PIN);
//	Serial.print(F("[Debug] sniffing: "));
//	Serial.println(result);
	if (result <= 512 && !fireTriggered) {
		fireTriggered = true;
	}
	
	if (fireTriggered) {
		if (fsm_getState() == FSM_STATE_ALARMED) {
			fireChecksCount++;
			result = analogRead(FIRE_ALARM_PIN);
			if (result <= 512) {
				fireChecksDetected++;
			}
			else {
				fireChecksFalse++;
			}
		}
		
		if (fireChecksCount >= FIRE_CHECKS_COUNT) {
			if (fireChecksDetected > fireChecksFalse) {
				returnCode = 1;
				Serial.println(F("[Debug] actions: oh noes, fire detected"));
			}
			fireTriggered = false;
			fireChecksCount = 0;
			fireChecksDetected = 0;
			fireChecksFalse = 0;
		}
	}
	
	return returnCode;
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

void actions_setAlarmBlinkPeriod(unsigned int period) 
{
	act_blinkPeriod = period;
}

void actions_blinkAlarm() 
{
	if (millis() - act_blinkStart >= act_blinkPeriod) {
		digitalWrite(MOSFET_BLINKY_THING, act_alarmLedState);
		act_alarmLedState = !act_alarmLedState;
		act_blinkStart = millis();
	}
}
