#include "alarm.h"

void setup() 
{
	Serial.begin(115200);
	Serial.println(F("Debug: starting up"));
	buttons_setup();
	radio_setup();
	actions_setup();
	Serial.println(F("Debug: start-up finished"));
}

void loop() 
{
	buttons_check();
	radio_processCommand();
	
	fsm_runStateMachine();
}