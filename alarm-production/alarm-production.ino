/*
 * alarm-production.ino
 * 
 * Created: 09.06.2021 07:30:35
 * Author: ThePetrovich
 */


#include <Arduino.h>
#include <Wiegand.h>
#include "alarm.h"
#include "rfid.h"
#include "actions.h"
#include "commands.h"
#include "statemachine.h"
#include "sched.h"

void setup() 
{
	Serial.begin(9600);
	Serial.println(F("[Debug] init: starting up"));
	Serial.print(F("[Debug] init: alarm-production version "));
	Serial.print(VERSION);
	Serial.print(F(" built "));
	Serial.println(TIMESTAMP);
	
	actions_setup();
	commands_setup();
	rfid_setup();
	
	Serial.println(F("[Debug] init: start-up finished"));
}

void loop() 
{
	commands_processCommand();
	actions_readAllButtons();
	rfid_processCommand();

	fsm_runStateMachine();
}
