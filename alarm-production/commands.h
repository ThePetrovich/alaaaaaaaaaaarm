#ifndef _SERIALCMD_H_
#define _SERIALCMD_H_

#include <Arduino.h>
#include "alarm.h"

void cmdparser_setup();
void cmdparser_processCommand();
char* cmdparser_waitForInput();
void cmdparser_registerCommand(char* cmdName, void(*handler)());
void cmdparser_flushReceiveBuffer();

void commands_setup();

#endif