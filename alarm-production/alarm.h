/*
 * alarm.h
 * 
 * Created: 09.06.2021 07:30:35
 * Author: ThePetrovich
 */


#ifndef _ALARM_ALARM_H_ //Holy shit I'm dumb
#define _ALARM_ALARM_H_

#define VERSION "0.5.0"
#define TIMESTAMP __TIMESTAMP__

#define FSM_STATE_KALM 0
#define FSM_STATE_ALARMED 1
#define FSM_STATE_PANIK 2

#define BUTTON_ENABLE_PIN 13
#define BUTTON_DISABLE_PIN 10
//#define BUTTON_FAILSAFE_PIN 10
//#define BUTTON_OPEN_PIN 4
#define OPEN_DETECT_PIN 12

#define MOSFET_LOUD_THING 6
#define MOSFET_BLINKY_THING 5

#define rfid_DATA1_PIN 3
#define rfid_DATA2_PIN 2

#define DOOR_OPEN_PIN 4

#define FIRE_ALARM_PIN A0
#define LED_ALARMED_PIN 7
#define LED_KALM_PIN 8

#define PANIK_START_DELAY_MS 10000
#define PANIK_DURATION_MS 10000
#define FAILSAFE_BUTTON_DURATION_MS 20000
#define OPEN_BUTTON_DURATION_MS 5000

#define MAX_COMMAND_NUM 5
#define MAX_COMMAND_LENGTH 16

#define FIRE_CHECKS_COUNT 10000

#endif
