#ifndef _SERIALCMD_H_
#define _SERIALCMD_H_

#include <Arduino.h>
#include "alarm.h"

void commands_setup();
void commands_processCommand();
char* commands_waitForInput();
void commands_registerCommand(char* cmdName, void(*handler)());
void commands_flushReceiveBuffer();

#endif