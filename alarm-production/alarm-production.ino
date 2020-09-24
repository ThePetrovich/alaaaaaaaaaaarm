#include "alarm.h"
#include "actions.h"
#include "commands.h"
#include "devices.h"
#include "statemachine.h"
#include <Wiegand.h>

void setup() 
{
	Serial.begin(9600);
	Serial.println(F("Debug: starting up"));
	Serial.print(F("Debug: alarm-production version "));
	Serial.print(VERSION);
	Serial.print(F(" built "));
	Serial.println(TIMESTAMP);
	
	actions_setup();
    commands_setup();
    rfid_setup();
	
	Serial.println(F("Debug: start-up finished"));
}

void loop() 
{
    cmdparser_processCommand();
    actions_readAllButtons();
    rfid_processCommand();

	fsm_runStateMachine();
}
