#include "commands.h"
#include "statemachine.h"

void commands_test()
{
    Serial.println(F("Test command"));
}

void commands_forceEnable()
{
    Serial.println(F("Force enabling the alarm"));
    fsm_setState(FSM_STATE_ALARMED);
}

void commands_forceDisable()
{
    Serial.println(F("Force disabling the alarm"));
    fsm_setState(FSM_STATE_KALM);
}

void commands_forcePanik()
{
    Serial.println(F("Force switching to panic"));
    fsm_setState(FSM_STATE_PANIK);
}

void commands_setup()
{
    cmdparser_setup();
    cmdparser_registerCommand((char*)"test", commands_test);
    cmdparser_registerCommand((char*)"set_kalm", commands_forceDisable);
    cmdparser_registerCommand((char*)"set_alarmed", commands_forceEnable);
    cmdparser_registerCommand((char*)"set_panik", commands_forcePanik);
}