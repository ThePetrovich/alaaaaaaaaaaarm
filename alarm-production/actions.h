/*
 * actions.h
 * 
 * Created: 09.06.2021 07:30:41
 * Author: ThePetrovich
 */


#ifndef _ACTIONS_ALARM_H_
#define _ACTIONS_ALARM_H_

#include <stdint.h>

#define ACTIONS_OUTPUT_ALARM 0
#define ACTIONS_OUTPUT_LOUD 1
#define ACTIONS_OUTPUT_LED_ALARMED 2
#define ACTIONS_OUTPUT_LED_KALM 3

#define ACTIONS_INPUT_DETECTOR 4
#define ACTIONS_INPUT_BTN_ENABLE 5
#define ACTIONS_INPUT_BTN_DISABLE 6

void actions_setup();

uint8_t actions_checkInput(int input);
void actions_readAllButtons();

int actions_sniff(); //Checks the smoke detector
void actions_bonk(); //Disables everything
void actions_setOutput(int output, int state);
void actions_setSwitchPeriod(int output, unsigned int period);

#endif