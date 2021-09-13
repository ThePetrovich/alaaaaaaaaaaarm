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
#include "timer2.h"

sSched_t schedMain;
sJob_t fsm;

void setup() 
{
	Serial.begin(9600);
	Serial.println(F("[Debug] init: starting up"));
	Serial.print(F("[Debug] init: alarm-production version "));
	Serial.print(VERSION);
	Serial.print(F(" built "));
	Serial.println(TIMESTAMP);

	sched_initScheduler(&schedMain);
	timer2_init(&schedMain);

	sched_createJob(&schedMain, &fsm, (void(*)(void*))fsm_runStateMachine, NULL, 10, 10, 0, "fsm_main");
	sched_activateJob(&fsm);
	
	fsm_init();

	actions_setup();
	commands_setup();
	rfid_setup();

	timer2_enable();
	
	Serial.println(F("[Debug] init: start-up finished"));
}

void loop() 
{
	commands_processCommand();
	actions_readAllButtons();
	rfid_processCommand();

	sched_run(&schedMain);
}
