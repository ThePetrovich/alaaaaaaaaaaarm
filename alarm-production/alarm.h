#include <Arduino.h>
#include <Button.h>

#define FSM_STATE_KALM = 0
#define FSM_STATE_ALARMED = 1
#define FSM_STATE_PANIK = 2


void fsm_setState(int state);
int fsm_getState(state);
void fsm_runStateMachine();

void button_setup();

void actions_openDoor();
void actions_closeDoor();

void actions_WeeWooWeeWoo();
void actions_calmTFDown();

int actions_sniff();
