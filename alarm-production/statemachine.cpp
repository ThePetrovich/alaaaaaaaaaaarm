/*
 * statemachine.cpp
 * 
 * Created: 09.06.2021 07:30:35
 * Author: ThePetrovich
 */


#include <Arduino.h>
#include "statemachine.h"
#include "actions.h"
#include "alarm.h"
#include "sched.h"

int fsm_globalAlarmState = FSM_STATE_KALM;
int fsm_globalPreviousState = FSM_STATE_KALM;

unsigned long int fix_PanikDelay = 0;

static int fsm_nextState = 0;

extern sSched_t schedMain;

sJob_t fsm_jobSwitch;

static void fsm_setStateJob(void *);
void fsm_setStateDelayed(int state, int delay);

void fsm_init()
{
	sched_createJob(&schedMain, &fsm_jobSwitch, (void(*)(void*))fsm_setStateJob, NULL, 0, 0, 4, "fsm_dsw");
	sched_suspendJob(&fsm_jobSwitch);
}

static void fsm_stateAlarmed()
{	
	actions_setSwitchPeriod(ACTIONS_OUTPUT_ALARM, 1000);
	if (actions_sniff()) {
		fsm_globalPreviousState = fsm_globalAlarmState;
		fsm_setStateDelayed(FSM_STATE_PANIK, PANIK_START_DELAY_MS);
		Serial.println(F("[Debug] fsm: PANIC! Fire detected!"));
	}
	
	if (actions_checkInput(ACTIONS_INPUT_BTN_DISABLE) == 1) {
		fsm_setState(FSM_STATE_KALM);
		Serial.println(F("[Debug] fsm: Disabling the alarm"));
	}
}

static void fsm_stateKalm()
{
	actions_setSwitchPeriod(ACTIONS_OUTPUT_ALARM, 0);
	
	if (actions_checkInput(ACTIONS_INPUT_BTN_ENABLE) == 1) {
		fsm_setStateDelayed(FSM_STATE_ALARMED, 20000);
		Serial.println(F("[Debug] fsm: Enabling the alarm"));
	}
}

static void fsm_statePanik()
{
	actions_setSwitchPeriod(ACTIONS_OUTPUT_ALARM, 10);

	if (actions_checkInput(ACTIONS_INPUT_BTN_DISABLE) == 1) {
		fsm_setState(FSM_STATE_KALM);
		Serial.println(F("[Debug] fsm: Disabling the alarm"));
	}
	
	fsm_setStateDelayed(fsm_globalPreviousState, 2000);
}

static void fsm_setStateJob(void *)
{
	fsm_globalAlarmState = fsm_nextState;
	sched_suspendJob(&fsm_jobSwitch);

	Serial.println(F("[Debug] fsm: Delayed state switch"));
}

void fsm_setState(int state)
{
	fsm_globalAlarmState = state;
	sched_suspendJob(&fsm_jobSwitch);
}

void fsm_setStateDelayed(int state, int delay)
{
	if (sched_getJobState(&fsm_jobSwitch) == STATE_SUSPENDED) {
		sched_setJobDelay(&fsm_jobSwitch, delay);
		sched_activateJob(&fsm_jobSwitch);

		fsm_nextState = state;
	}
}

int fsm_getState()
{
	return fsm_globalAlarmState;
}

void fsm_runStateMachine()
{
	if (fsm_globalAlarmState == FSM_STATE_KALM) fsm_stateKalm();
	if (fsm_globalAlarmState == FSM_STATE_ALARMED) fsm_stateAlarmed();
	if (fsm_globalAlarmState == FSM_STATE_PANIK) fsm_statePanik();
}
