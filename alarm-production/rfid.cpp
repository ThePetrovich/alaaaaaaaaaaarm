#include "alarm.h"
#include "keys.h"
#include "devices.h"
#include "commands.h"
#include <Wiegand.h>
#include <String.h>

#define EEPROM_MAGIC 0xDEADC0DE

extern WIEGAND wg;

struct key {
    uint32_t id;
    char name[20];
    struct key *next;
};

struct eeprom_header {
    uint32_t magic;
    uint8_t stored_keys;
    uint8_t flags;
};

struct key_eeprom {
    uint32_t id;
    char name[20];
};

struct key *list_head;

int wiegand_updateHeader()
{
    
}

int wiegand_searchKey()
{

}

struct key wiegand_readKey(uint16_t addr)
{

}

int wiegand_writeKey(uint16_t addr, struct key data)
{
    
}

void wiegand_setup() 
{
    wg.begin(WIEGAND_DATA1_PIN, WIEGAND_DATA2_PIN);
    cmdparser_registerCommand((char*)"wg_add_key", wiegand_cmdAddKey);
    cmdparser_registerCommand((char*)"wg_delete_key", wiegand_cmdDeleteKey);
    cmdparser_registerCommand((char*)"wg_find_key", wiegand_cmdFindKey);
    cmdparser_registerCommand((char*)"wg_find_name", wiegand_cmdFindName);
}

void wiegand_processCommand() 
{
    uint32_t code = 0;
    int result = 0, index = 0;
    if(wg.available())
	{
        code = wg.getCode();
		Serial.print(F("Wiegand HEX = "));
		Serial.print(code, HEX);
		Serial.print(F(", DECIMAL = "));
		Serial.print(code);
		Serial.print(F(", Type W"));
		Serial.println(wg.getWiegandType());    

        for (int i = 0; i < wg_authorized_keys_num; i++) {
            if (code == wg_authorized_keys[i]) {
                result = 1;
                index = i;
                break;
            }
        }

        if (result) {
            Serial.println(F("Found keycard code in authorized keycards list"));
            Serial.print(F("Username = "));
            Serial.println(wg_names[index]);
            pinMode(DOOR_OPEN_PIN, OUTPUT);
            delay(500);
        }
        else {
            Serial.println("Unauthorized keycard");
        }
	}
    pinMode(DOOR_OPEN_PIN, INPUT);
    digitalWrite(DOOR_OPEN_PIN, LOW);
}

void wiegand_cmdAddKey()
{

}

void wiegand_cmdDeleteKey()
{
    
}

void wiegand_cmdFindKey()
{
    
}

void wiegand_cmdFindName()
{
    
}
