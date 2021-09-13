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
#include "sched.h"

static alarm_button detector;
static alarm_button enable;
static alarm_button disable;

extern sSched_t schedMain;

sJob_t actions_jobBlinkAlarm;
sJob_t actions_jobBlinkLed1;
sJob_t actions_jobBlinkLed2;

void actions_blink(void* output);

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

	sched_createJob(&schedMain, &actions_jobBlinkAlarm, actions_blink, (void*)ACTIONS_OUTPUT_ALARM, 0, 0, 4, "act_blink");
	sched_activateJob(&actions_jobBlinkAlarm);
	sched_createJob(&schedMain, &actions_jobBlinkLed1, actions_blink, (void*)ACTIONS_OUTPUT_LED_ALARMED, 0, 0, 4, "act_blink1");
	sched_activateJob(&actions_jobBlinkLed1);
	sched_createJob(&schedMain, &actions_jobBlinkLed2, actions_blink, (void*)ACTIONS_OUTPUT_LED_KALM, 0, 0, 4, "act_blink2");
	sched_activateJob(&actions_jobBlinkLed2);
}

uint8_t actions_checkInput(int input)
{
	uint8_t result = 0;

	switch(input) {
		case ACTIONS_INPUT_BTN_DISABLE:
			result = buttons_readButton(&disable);
			break;
		case ACTIONS_INPUT_BTN_ENABLE:
			result = buttons_readButton(&enable);
			break;
		case ACTIONS_INPUT_DETECTOR:
			result = buttons_readButton(&detector);
			break;
		case ACTIONS_OUTPUT_ALARM:
			result = digitalRead(MOSFET_BLINKY_THING);
			break;
		case ACTIONS_OUTPUT_LOUD:
			result = digitalRead(MOSFET_LOUD_THING);
			break;
		case ACTIONS_OUTPUT_LED_ALARMED:
			result = digitalRead(LED_ALARMED_PIN);
			break;
		case ACTIONS_OUTPUT_LED_KALM:
			result = digitalRead(LED_KALM_PIN);
			break;
		default:
			result = 0;
			break;
	}

	return result;
}

void actions_setOutput(int output, int state)
{
	switch(output) {
		case ACTIONS_OUTPUT_ALARM:
			digitalWrite(MOSFET_BLINKY_THING, state);
			break;
		case ACTIONS_OUTPUT_LOUD:
			digitalWrite(MOSFET_LOUD_THING, state);
			break;
		case ACTIONS_OUTPUT_LED_ALARMED:
			digitalWrite(LED_ALARMED_PIN, state);
			digitalWrite(LED_KALM_PIN, !state);
			break;
		case ACTIONS_OUTPUT_LED_KALM:
			digitalWrite(LED_ALARMED_PIN, !state);
			digitalWrite(LED_KALM_PIN, state);
			break;
		default:
			break;
	}
}

void actions_setSwitchPeriod(int output, unsigned int period) {
	switch(output) {
		case ACTIONS_OUTPUT_ALARM:
			sched_setJobPeriod(&actions_jobBlinkAlarm, period);
			sched_activateJob(&actions_jobBlinkAlarm);
			break;
		case ACTIONS_OUTPUT_LED_ALARMED:
			sched_setJobPeriod(&actions_jobBlinkLed1, period);
			sched_activateJob(&actions_jobBlinkLed1);
			break;
		case ACTIONS_OUTPUT_LED_KALM:
			sched_setJobPeriod(&actions_jobBlinkLed2, period);
			sched_activateJob(&actions_jobBlinkLed2);
			break;
		default:
			break;
	}
}

int actions_sniff()
{
	int returnCode = 0;
	static unsigned int fireChecksCount = 0;
	static unsigned int fireChecksDetected = 0;
	static unsigned int fireChecksFalse = 0;
	static bool fireTriggered = false;

	int result = analogRead(FIRE_ALARM_PIN);
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
	fsm_setState(FSM_STATE_KALM);
}

void actions_readAllButtons()
{
	buttons_readButton(&detector);
	buttons_readButton(&disable);
	buttons_readButton(&enable);
}

void actions_blink(void* output) 
{
	int out = (int)output;
	actions_setOutput(out, !actions_checkInput(out));
}

