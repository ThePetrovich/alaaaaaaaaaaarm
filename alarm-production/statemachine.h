/*
 * statemachine.h
 * 
 * Created: 09.06.2021 07:30:41
 * Author: ThePetrovich
 */


#ifndef _STATEMACHINE_ALARM_H_
#define _STATEMACHINE_ALARM_H_

#include "alarm.h"

void fsm_setState(int state);
int fsm_getState();
void fsm_runStateMachine();

#endif