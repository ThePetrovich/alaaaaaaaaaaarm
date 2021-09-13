/*
 * eeprom.c
 * 
 * Created: 09.06.2021 07:30:41
 * Author: ThePetrovich
 */


#include <Arduino.h>
#include <String.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/crc16.h>
#include "alarm.h"
#include "eeprom.h"

const size_t headerStructSize = sizeof(alarm_eepromHeader) + 1;
const size_t keyStructSize = sizeof(alarm_eepromKey) + 1;

alarm_eepromHeader eeprom_readHeader()
{
	alarm_eepromHeader temp;

	eeprom_read_block((void*)&temp, (void*)(0), headerStructSize);
	eeprom_busy_wait();

	return temp;
}

void eeprom_writeHeader(alarm_eepromHeader *header)
{
	header->magic = EEPROM_MAGIC;
	eeprom_update_block((void*)header, (void*)(0), headerStructSize);
	eeprom_busy_wait();
}

int eeprom_checkHeader(alarm_eepromHeader *header)
{
	if (header->magic == EEPROM_MAGIC) {
		return 1;
	}
	return 0;
}

uint16_t eeprom_searchKey(uint32_t id)
{
	alarm_eepromHeader header = eeprom_readHeader();
	alarm_eepromKey temp;
	uint16_t position = 0;
	
	for (position = 0; position < header.storedKeys; position++) {
		temp = eeprom_readKey(position);
		if (temp.id == id) break;
	}

	if (position == header.storedKeys-1) return 0; 
	else return position;
}

alarm_eepromKey eeprom_readKey(uint16_t position)
{
	alarm_eepromKey temp;

	eeprom_read_block((void*)&temp, (void*)(headerStructSize + (keyStructSize * position)), keyStructSize);
	eeprom_busy_wait();

	return temp;
}

uint16_t eeprom_writeKey(alarm_eepromKey *key)
{
	uint16_t pos = eeprom_searchKey(key->id); // Looking for key with the same id as ours

	if (!pos) {
		pos = eeprom_searchKey(0); // Looking for first key with id=0, which is empty key
		if (!pos) {
			alarm_eepromHeader newHeader = eeprom_readHeader();

			newHeader.storedKeys++;
			pos = newHeader.storedKeys;

			eeprom_writeHeader(&newHeader);
		}
	}

	eeprom_update_block((void*)key, (void*)(headerStructSize + (keyStructSize * pos)), keyStructSize);

	return pos;
}