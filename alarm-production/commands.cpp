/*
 * commands.cpp
 * 
 * Created: 09.06.2021 07:30:41
 * Author: ThePetrovich
 */


#include <Arduino.h>
#include <string.h>
#include "commands.h"
#include "statemachine.h"
#include "alarm.h"

static struct cmdManager cmdManager;

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
	cmdManager.activeCommand = -1;
	commands_registerCommand((char*)"test", commands_test);
	commands_registerCommand((char*)"set_kalm", commands_forceDisable);
	commands_registerCommand((char*)"set_alarmed", commands_forceEnable);
	commands_registerCommand((char*)"set_panik", commands_forcePanik);
}

void commands_registerCommand(char *cmdName, void(*handler)())
{
	if (cmdManager.regCmd_idx < MAX_COMMAND_NUM) {
		cmdManager.regCmds[cmdManager.regCmd_idx].handler = handler;
		strncpy(cmdManager.regCmds[cmdManager.regCmd_idx].name, cmdName, MAX_COMMAND_LENGTH);
		cmdManager.regCmd_idx++;
	}
}

void commands_flushReceiveBuffer()
{
	cmdManager.cmd_idx = 0;
	cmdManager.cmd_buf[0] = 0;
}

void commands_processCommand()
{
	if (cmdManager.activeCommand != -1) {
		if (cmdManager.regCmds[cmdManager.activeCommand].handler != NULL) {
			(cmdManager.regCmds[cmdManager.activeCommand].handler)();
		}
		else {
			Serial.println("[Debug] commands: ERROR - attempt to execute a NULL command");
		}
	}
	cmdManager.activeCommand = -1;
}

static void commands_processChar(char c)
{
	if (c == '\n' || c == '\r') {
		cmdManager.cmd_buf[cmdManager.cmd_idx] = 0;
		for (int i = 0; i < cmdManager.regCmd_idx; i++) {
			if (strncmp(cmdManager.cmd_buf, cmdManager.regCmds[i].name, MAX_COMMAND_LENGTH) == 0) {
				cmdManager.activeCommand = i;
				break;
			}
		}
		commands_flushReceiveBuffer();
	}
	else {
		if (cmdManager.cmd_idx < 64) {
			cmdManager.cmd_buf[cmdManager.cmd_idx] = c;
			cmdManager.cmd_idx++;
		}
	}
}

void serialEvent()
{
	char data = 0; 
	while (Serial.available()) {
		data = (char)Serial.read();
		commands_processChar(data);
	}
}

char *commands_waitForInput()
{
	char data = 0; 
	while (data != '\n' && data != '\r') {
		if (Serial.available()) {
			data = (char)Serial.read();
			if (cmdManager.cmd_idx < 64) {
				cmdManager.cmd_buf[cmdManager.cmd_idx] = data;
				cmdManager.cmd_idx++;
			}
		}
	}
	cmdManager.cmd_buf[cmdManager.cmd_idx + 1] = 0;

	return cmdManager.cmd_buf;
}