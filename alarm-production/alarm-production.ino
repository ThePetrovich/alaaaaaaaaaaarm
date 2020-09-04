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
	
	radio_setup();
	actions_setup();
    buttons_setup();
    wiegand_setup();
	
	Serial.println(F("Debug: start-up finished"));
}

void loop() 
{
    //buttons_checkFailsafe();
    //radio_processCommand();

    wiegand_processCommand();
    
    /*
    if (digitalRead(BUTTON_OPEN_PIN)) {
        buttonOpen_pressed();
    }
    
    if (radio_getLastCommand() == 1) {
        buttonOpen_pressed();
        radio_dropLastCommand();
    }*/
  
	fsm_runStateMachine();
}
