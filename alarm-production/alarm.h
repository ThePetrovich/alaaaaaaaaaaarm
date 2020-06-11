#include <Arduino.h>
#include <Button.h>

#define FSM_STATE_KALM = 0
#define FSM_STATE_ALARMED = 1
#define FSM_STATE_PANIK = 2

#define BUTTON_ENABLE_PIN 13
#define BUTTON_DISABLE_PIN 12
#define BUTTON_FAILSAFE_PIN 11
#define BUTTON_OPEN_PIN 4
#define BUTTON_DOOR_PIN 3

#define MOSFET_LOUD_THING 6
#define MOSFET_BLINKY_THING 5
#define MOSFET_SOLENOID_THING 9

void fsm_setState(int state);
int fsm_getState(state);
void fsm_runStateMachine();

void buttons_setup();
void buttons_setup();

void actions_openDoor(); 
void actions_closeDoor();

void actions_WeeWooWeeWoo(); //Enables the loud thingy
void actions_calmTFDown(); //Disables the loud thingy

int actions_sniff(); //Checks the smoke detector

void actions_bonk(); //Disables everything
