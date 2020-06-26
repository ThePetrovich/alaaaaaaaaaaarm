#include "alarm.h"

void setup() 
{
	Serial.begin(9600);
	Serial.println(F("Debug: starting up"));
	Serial.print(F("Debug: alarm-production version "));
	Serial.print(VERSION);
	Serial.print(F(" built "));
	Serial.println(TIMESTAMP);
	
	buttons_setup();
	radio_setup();
	actions_setup();
	
	Serial.println(F("Debug: start-up finished"));
}

void loop() 
{
    buttons_checkFailsafe();
	buttons_checkOpen();
    radio_processCommand();
    
    if (radio_getLastCommand() == 1) {
        buttonOpen_pressed();
        radio_dropLastCommand();
    }
  
	fsm_runStateMachine();
}
