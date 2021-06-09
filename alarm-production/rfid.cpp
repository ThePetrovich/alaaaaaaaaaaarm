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

struct key_ram *list_head;

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
	uint32_t code = 0;
	int result = 0, index = 0;
	if (wg.available())
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
