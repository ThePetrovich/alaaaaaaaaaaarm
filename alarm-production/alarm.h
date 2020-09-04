#ifndef _ALARM_H_ //Holy shit I'm dumb
#define _ALARM_H_

#include <Arduino.h>

#define VERSION "0.4.0"
#define TIMESTAMP __TIMESTAMP__

#define FSM_STATE_KALM 0
#define FSM_STATE_ALARMED 1
#define FSM_STATE_PANIK 2

#define BUTTON_ENABLE_PIN 13
#define BUTTON_DISABLE_PIN 2
//#define BUTTON_FAILSAFE_PIN 10
//#define BUTTON_OPEN_PIN 4
#define BUTTON_DOOR_PIN 10

#define MOSFET_LOUD_THING 6
#define MOSFET_BLINKY_THING 5

#define WIEGAND_DATA1_PIN 2
#define WIEGAND_DATA2_PIN 3

#define DOOR_OPEN_PIN 4

#define FIRE_ALARM_PIN A0
#define LED_ALARMED_PIN 7
#define LED_KALM_PIN 8

#define PANIK_START_DELAY_MS 10000
#define PANIK_DURATION_MS 10000
#define FAILSAFE_BUTTON_DURATION_MS 20000
#define OPEN_BUTTON_DURATION_MS 5000

#define FIRE_CHECKS_COUNT 10000

void fsm_setState(int state);
int fsm_getState();
void fsm_runStateMachine();

void buttons_setup();
int buttons_checkDetector();
int buttons_checkEnable();
int buttons_checkDisable();

void actions_setup();

void actions_WeeWooWeeWoo(); //Enables the loud thingy
void actions_calmTFDown(); //Disables the loud thingy

int actions_sniff(); //Checks the smoke detector

void actions_bonk(); //Disables everything

void actions_ledAlarmed();
void actions_ledKalm();

void actions_blinkAlarm();
void actions_setAlarmBlinkPeriod(unsigned int period);

void wiegand_setup();

void wiegand_processCommand();

#endif