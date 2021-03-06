#include "alarm.h"

int fsm_globalAlarmState = FSM_STATE_KALM;
int fsm_globalPreviousState = FSM_STATE_KALM;

unsigned long int fix_PanikDelay = 0;

static void fsm_stateAlarmed()
{	
	actions_setAlarmBlinkPeriod(2000);
	actions_ledAlarmed();
    digitalWrite(MOSFET_LOUD_THING, LOW);
	
	actions_blinkAlarm();
	
    if (actions_sniff()) {
        fsm_globalPreviousState = fsm_globalAlarmState;
		fsm_setState(FSM_STATE_PANIK);
    }
    
	if (buttons_checkDetector() == -1) {
		fix_PanikDelay = millis();
		fsm_globalPreviousState = fsm_globalAlarmState;
		fsm_setState(FSM_STATE_PANIK);
	}
	
	if (buttons_checkDisable() == 1) {
		fsm_setState(FSM_STATE_KALM);
	}
}

static void fsm_stateKalm()
{
	actions_ledKalm();
	actions_calmTFDown();
    digitalWrite(MOSFET_BLINKY_THING, LOW); //Doing this explicitly because this sick fuck can't do this
	
	if (buttons_checkEnable() == 1) {
		for (int i = 0; i < 20; i++) {
			delay(250);
			digitalWrite(LED_ALARMED_PIN, !digitalRead(LED_ALARMED_PIN));
		}
		fsm_setState(FSM_STATE_ALARMED);
	}
}

static void fsm_statePanik()
{
	static bool dumbFix = false;
	static unsigned long start = 0;
	
	if (fix_PanikDelay != 0) {
		if (millis() - fix_PanikDelay >= PANIK_START_DELAY_MS) {
			fix_PanikDelay = 0;
		}
		else {
			if (buttons_checkDisable() == 1) {
				fsm_setState(FSM_STATE_KALM);
			}
			
			actions_blinkAlarm();
			return;
		}
	}
	
	if (!dumbFix) {
		start = millis();
		dumbFix = true;
	}
	
	if (millis() - start >= PANIK_DURATION_MS) { //TODO: change delay
		dumbFix = false;
		fsm_setState(fsm_globalPreviousState);
	}
	
	if (buttons_checkDisable() == 1) {
		fsm_setState(FSM_STATE_KALM);
	}
	actions_setAlarmBlinkPeriod(100);
	
	actions_blinkAlarm();
	actions_WeeWooWeeWoo();
}

void fsm_setState(int state)
{
	fsm_globalAlarmState = state;
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