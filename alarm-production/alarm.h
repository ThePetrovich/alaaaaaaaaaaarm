#include <Arduino.h>
#include <Button.h>
#include <VirtualWire.h>

#define FSM_STATE_KALM 0
#define FSM_STATE_ALARMED 1
#define FSM_STATE_PANIK 2

#define BUTTON_ENABLE_PIN 13
#define BUTTON_DISABLE_PIN 2
#define BUTTON_FAILSAFE_PIN 10
#define BUTTON_OPEN_PIN 4
#define BUTTON_DOOR_PIN 3

#define MOSFET_LOUD_THING 6
#define MOSFET_BLINKY_THING 5
#define MOSFET_SOLENOID_THING 9

#define FIRE_ALARM_PIN A0
#define LED_ALARMED_PIN 7
#define LED_KALM_PIN 8

#define RADIO_RX_PIN 11
#define RADIO_SPEED 1000
#define RADIO_RX_IS_INVERTED 0

#define RADIO_CMD_OPEN "FBIOPNUP"
#define RADIO_CMD_PANIK "HHAALLPP"
#define RADIO_CMD_DROP "IDCANMRE"
 
#define PANIK_DURATION_MS 10000
#define FAILSAFE_BUTTON_DURATION_MS 20000
#define OPEN_BUTTON_DURATION_MS 5000

void fsm_setState(int state);
void fsm_setPreviousState();
int fsm_getState();
void fsm_runStateMachine();

void buttons_setup();
void buttons_check();
void buttons_checkDetector();

void radio_setup();
void radio_processCommand();

void actions_setup();

void actions_openDoor(); 
void actions_closeDoor();

void actions_WeeWooWeeWoo(); //Enables the loud thingy
void actions_calmTFDown(); //Disables the loud thingy

int actions_sniff(); //Checks the smoke detector

void actions_bonk(); //Disables everything

void actions_ledAlarmed();
void actions_ledKalm();
