#include "alarm.h"

int fsm_globalAlarmState = 0;
int fsm_globalPreviousState = 0;

static void fsm_stateAlarmed()
{
	
}

static void fsm_stateKalm()
{
	
}

static void fsm_statePanik()
{
	
}

void fsm_setState(int state)
{
	fsm_globalPreviousState = fsm_globalAlarmState;
	fsm_globalAlarmState = state;
}

int fsm_getState(state)
{
	return fsm_globalAlarmState;
}

void fsm_runStateMachine()
{
	if (fsm_globalAlarmState == FSM_STATE_KALM) fsm_stateKalm();
	if (fsm_globalAlarmState == FSM_STATE_ALARMED) fsm_stateAlarmed();
	if (fsm_globalAlarmState == FSM_STATE_PANIK) fsm_statePanik();
}