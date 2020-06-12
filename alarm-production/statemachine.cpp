#include "alarm.h"

int fsm_globalAlarmState = 0;
int fsm_globalPreviousState = 0;

static void fsm_stateAlarmed()
{
	actions_ledAlarmed();
	actions_sniff();
	buttons_checkDetector();
	Serial.println(F("Debug: current state: ALARMED"));
}

static void fsm_stateKalm()
{
	actions_ledKalm();
	actions_calmTFDown();
	Serial.println(F("Debug: current state: KALM"));
}

static void fsm_statePanik()
{
	static bool dumbFix = false;
	static unsigned long start = 0;
	
	if (!dumbFix) {
		start = millis();
		dumbFix = true;
	}
	
	if (millis() - start >= PANIK_DURATION_MS) { //TODO: change delay
		dumbFix = false;
		fsm_setPreviousState();
	}
	
	actions_WeeWooWeeWoo();
	Serial.println(F("Debug: current state: PANIK"));
}

void fsm_setState(int state)
{
	fsm_globalPreviousState = fsm_globalAlarmState;
	fsm_globalAlarmState = state;
}

void fsm_setPreviousState()
{
	fsm_globalAlarmState = fsm_globalPreviousState;
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