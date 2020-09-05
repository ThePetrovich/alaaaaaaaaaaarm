#include "alarm.h"

struct command {
    (void*)() handler;
    char name[16];
};

struct cmdManager {
    char cmd_buf[64];
    uint8_t cmd_idx;
    uint8_t activeCommand;
    struct command regCmds[MAX_COMMAND_NUM];
    uint8_t regCmd_idx;
} cmdManager;

void controls_setup()
{

}

void controls_processCommand(char c)
{

}

void controls_waitForInput()
{
    char data = 0; 
    while (data != '\n' && data != '\r') {
        if (Serial.available()) {
            data = Serial.read();
            cmdManager.cmd_buf[cmdManager.cmd_idx] = data;
            cmdManager.cmd_idx++;
        }
    }
    cmdManager.cmd_buf[cmdManager.cmd_idx] = 0;
}