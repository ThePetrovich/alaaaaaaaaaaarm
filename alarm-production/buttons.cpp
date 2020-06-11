#include "alarm.h"

Button buttonEnable(13);
Button buttonDisable(12);
Button buttonFailsafe(11);
Button buttonOpen(4);
Button buttonDetector(3);

void button_setup()
{
	buttonEnable.begin();
	buttonDisable.begin();
	buttonFailsafe.begin();
	buttonOpen.begin();
	buttonDetector.begin();
}

void buttonEnable_pressed() 
{
	int currentState = fsm_getState();
	
	if (currentState == FSM_STATE_KALM) {
		fsm_setState(FSM_STATE_ALARMED);
	}
}

void buttonDisable_pressed() 
{	
	fsm_setState(FSM_STATE_KALM);
}

void buttonFailsafe_pressed() 
{
	actions_openDoor();
	delay(20000); //Hate this
	actions_closeDoor();
}

void buttonOpen_pressed() 
{
	actions_openDoor();
	delay(5000);
	actions_closeDoor();
}

void buttonDetector_pressed() 
{
	if (currentState == FSM_STATE_ALARMED) {
		fsm_setState(FSM_STATE_PANIK);
	}
}

void button_check()
{
	
}