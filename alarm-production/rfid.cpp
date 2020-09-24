#include "alarm.h"
#include "keys.h"
#include "devices.h"
#include "commands.h"
#include <Wiegand.h>
#include <String.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/eeprom.h>

#define EEPROM_MAGIC 0xDEADC0DE

extern WIEGAND wg;

struct key_ram {
    uint32_t id;
    char name[20];
    struct key *next;
    uint16_t eepromPosition;
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

struct key_ram *list_head;

const size_t headerStructSize = sizeof(struct eeprom_header);
const size_t keyStructSize = sizeof(struct key_eeprom);

struct eeprom_header rfid_readHeader()
{
    struct eeprom_header temp;

    eeprom_read_block((void*)&temp, (void*)(0), headerStructSize);
    eeprom_busy_wait();

    return temp;
}

void rfid_writeHeader(struct eeprom_header *header)
{
    header->magic = EEPROM_MAGIC;
    eeprom_update_block((void*)header, (void*)(0), headerStructSize);
    eeprom_busy_wait();
}

uint16_t rfid_searchKey(uint32_t id)
{
    struct eeprom_header header = rfid_readHeader();
    struct key_eeprom temp;
    uint16_t position = 0;
    
    for (position = 0; position < header.stored_keys; position++) {
        temp = rfid_readKey(position);
        if (temp.id == id) break;
    }

    if (position == header.stored_keys-1) return 0; 
    else return position;
}

struct key_eeprom rfid_readKey(uint16_t position)
{
    struct key_eeprom temp;

    eeprom_read_block((void*)&temp, (void*)(headerStructSize + (keyStructSize * position)), keyStructSize);
    eeprom_busy_wait();

    return temp;
}

uint16_t rfid_writeKey(struct key_ram *data)
{
    
}

void rfid_setup() 
{
    wg.begin(rfid_DATA1_PIN, rfid_DATA2_PIN);
    cmdparser_registerCommand((char*)"wg_add_key", rfid_cmdAddKey);
    cmdparser_registerCommand((char*)"wg_delete_key", rfid_cmdDeleteKey);
    cmdparser_registerCommand((char*)"wg_find_key", rfid_cmdFindKey);
    cmdparser_registerCommand((char*)"wg_find_name", rfid_cmdFindName);
}

void rfid_processCommand() 
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

void rfid_cmdAddKey()
{

}

void rfid_cmdDeleteKey()
{
    
}

void rfid_cmdFindKey()
{
    
}

void rfid_cmdFindName()
{
    
}
