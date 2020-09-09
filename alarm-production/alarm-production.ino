#include "alarm.h"
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
   // buttons_setup();
    wiegand_setup();
	
	Serial.println(F("Debug: start-up finished"));
}

void loop() 
{
    wiegand_processCommand();
  
//	fsm_runStateMachine();
}
