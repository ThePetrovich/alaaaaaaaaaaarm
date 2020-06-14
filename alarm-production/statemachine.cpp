#include "alarm.h"

int fsm_globalAlarmState = 0;
int fsm_globalPreviousState = 0;

unsigned long int fix_PanikDelay = 0;

static void fsm_stateAlarmed()
{	
	actions_setAlarmBlinkPeriod(2000);
	actions_ledAlarmed();
	actions_sniff();
	
	actions_blinkAlarm();
	
	buttons_checkDetector();
}

static void fsm_stateKalm()
{
	actions_ledKalm();
	actions_calmTFDown();
}

static void fsm_statePanik()
{
	static bool dumbFix = false;
	static unsigned long start = 0;
	
	actions_setAlarmBlinkPeriod(100);
	
	if (fix_PanikDelay != 0) {
		if (millis() - fix_PanikDelay >= PANIK_START_DELAY_MS) {
			fix_PanikDelay = 0;
		}
		else {
			Serial.println(F("Debug: delaying PANIK"));
			return;
		}
	}
	
	if (!dumbFix) {
		start = millis();
		dumbFix = true;
	}
	
	if (millis() - start >= PANIK_DURATION_MS) { //TODO: change delay
		dumbFix = false;
		fsm_setPreviousState();
	}
	
	actions_WeeWooWeeWoo();
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