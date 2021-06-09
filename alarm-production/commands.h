/*
 * commands.h
 * 
 * Created: 09.06.2021 07:30:41
 * Author: ThePetrovich
 */


#ifndef _SERIALCMD_ALARM_H_
#define _SERIALCMD_ALARM_H_

#include "alarm.h"

typedef struct command 
{
	void(*handler)();
	char name[MAX_COMMAND_LENGTH];
} alarm_SerialCommand;

typedef struct cmdManager 
{
	char cmd_buf[64];
	uint8_t cmd_idx;
	int activeCommand = -1;
	struct command regCmds[MAX_COMMAND_NUM];
	uint8_t regCmd_idx;
} alarm_SerialCmdManager;

void commands_setup();
void commands_processCommand();
char *commands_waitForInput();
void commands_registerCommand(char *cmdName, void(*handler)());
void commands_flushReceiveBuffer();

#endif