#include "alarm.h"

void setup() 
{
	Serial.begin(9600);
	buttons_setup();
}

void loop() 
{
	buttons_check();
	fsm_runStateMachine();
}