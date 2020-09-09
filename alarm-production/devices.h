#ifndef _DEVICES_H_
#define _DEVICES_H_

#include <Arduino.h>
#include "alarm.h"

void devices_setup();

void wiegand_setup();
void wiegand_processCommand();

#endif