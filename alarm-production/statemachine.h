#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

#include <Arduino.h>
#include "alarm.h"

void fsm_setState(int state);
int fsm_getState();
void fsm_runStateMachine();

#endif