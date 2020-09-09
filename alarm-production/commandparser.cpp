#include "commands.h"
#include "alarm.h"
#include <string.h>

struct command {
    void(*handler)();
    char name[MAX_COMMAND_LENGTH];
};

static struct cmdManager {
    char cmd_buf[64];
    uint8_t cmd_idx;
    int activeCommand = -1;
    struct command regCmds[MAX_COMMAND_NUM];
    uint8_t regCmd_idx;
} cmdManager;

void cmdparser_setup()
{
    cmdManager.activeCommand = -1;
}

void cmdparser_registerCommand(char* cmdName, void(*handler)())
{
    if (cmdManager.regCmd_idx < MAX_COMMAND_NUM) {
        cmdManager.regCmds[cmdManager.regCmd_idx].handler = handler;
        strncpy(cmdManager.regCmds[cmdManager.regCmd_idx].name, cmdName, MAX_COMMAND_LENGTH);
        cmdManager.regCmd_idx++;
    }
}

void cmdparser_flushReceiveBuffer()
{
    cmdManager.cmd_idx = 0;
    cmdManager.cmd_buf[0] = 0;
}

void cmdparser_processCommand()
{
    if (cmdManager.activeCommand != -1) {
        if (cmdManager.regCmds[cmdManager.activeCommand].handler != NULL) {
            (cmdManager.regCmds[cmdManager.activeCommand].handler)();
        }
        else {
            Serial.println("Debug: ERROR - attempt to execute a NULL command");
        }
    }
    cmdManager.activeCommand = -1;
}

static void cmdparser_processChar(char c)
{
    if (c == '\n' || c == '\r') {
        cmdManager.cmd_buf[cmdManager.cmd_idx] = 0;
        for (int i = 0; i < cmdManager.regCmd_idx; i++) {
            if (strncmp(cmdManager.cmd_buf, cmdManager.regCmds[i].name, MAX_COMMAND_LENGTH) == 0) {
                cmdManager.activeCommand = i;
                break;
            }
        }
        cmdparser_flushReceiveBuffer();
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
        cmdparser_processChar(data);
    }
}

char* cmdparser_waitForInput()
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