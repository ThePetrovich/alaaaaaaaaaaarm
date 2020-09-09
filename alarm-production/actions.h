#ifndef _ACTIONS_H_
#define _ACTIONS_H_

#include <Arduino.h>
#include "alarm.h"

void actions_setup();

uint8_t actions_checkDetector();
uint8_t actions_checkEnable();
uint8_t actions_checkDisable();
void actions_readAllButtons();

void actions_WeeWooWeeWoo(); //Enables the loud thingy
void actions_calmTFDown(); //Disables the loud thingy
int actions_sniff(); //Checks the smoke detector
void actions_bonk(); //Disables everything
void actions_ledAlarmed();
void actions_ledKalm();
void actions_blinkAlarm();
void actions_setAlarmBlinkPeriod(unsigned int period);

#endif