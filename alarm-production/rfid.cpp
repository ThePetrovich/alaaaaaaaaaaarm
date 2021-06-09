/*
 * rfid.cpp
 * 
 * Created: 09.06.2021 07:30:35
 * Author: ThePetrovich
 */


#include <Arduino.h>
#include <Wiegand.h>
#include <String.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include "rfid.h"
#include "alarm.h"
#include "keys.h"
#include "commands.h"
#include "eeprom.h"

extern WIEGAND wg;

void rfid_setup() 
{
	wg.begin(rfid_DATA1_PIN, rfid_DATA2_PIN);
	//commands_registerCommand((char*)"wg_add_key", rfid_cmdAddKey);
	//commands_registerCommand((char*)"wg_delete_key", rfid_cmdDeleteKey);
	//commands_registerCommand((char*)"wg_find_key", rfid_cmdFindKey);
	//commands_registerCommand((char*)"wg_find_name", rfid_cmdFindName);
}

void rfid_processCommand() 
{
	alarm_eepromKey key;
	uint16_t pos = 0;
	uint32_t code = 0;

	if (wg.available())
	{
		code = wg.getCode();
		Serial.print(F("[Debug] rfid: Wiegand HEX = "));
		Serial.print(code, HEX);
		Serial.print(F(", DECIMAL = "));
		Serial.print(code);
		Serial.print(F(", Type W"));
		Serial.println(wg.getWiegandType());	

		if (code != 0 && code != ~((uint32_t)(0))) {
			pos = eeprom_searchKey(code);
			if (pos) {
				key = eeprom_readKey(pos);
				if (key.id != 0 && key.id != ~((uint32_t)(0))) {
					Serial.println(F("[Debug] rfid: Found keycard code in authorized keycards list"));
					Serial.print(F("[Debug] rfid: Username = "));
					Serial.print(key.name);
					Serial.print(F(", Valid until = "));
					Serial.println((uint32_t)key.validTill); // TODO: fix this type cast
					pinMode(DOOR_OPEN_PIN, OUTPUT);
					delay(500);
				}
				else {
					Serial.println(F("[Debug] rfid: EEPROM key id = 0, keystore corruption"));
				}
			}
			else {
				Serial.println(F("[Debug] rfid: Unauthorized keycard"));
			}
		}	
		else {
			Serial.println(F("[Debug] rfid: Zero-id keycard"));
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
