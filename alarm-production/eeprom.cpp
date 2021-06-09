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
#include <avr/eeprom.h>
#include "alarm.h"
#include "eeprom.h"

const size_t headerStructSize = sizeof(alarm_eepromHeader);
const size_t keyStructSize = sizeof(alarm_eepromKey);

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

uint16_t eeprom_writeKey(struct key_ram *data)
{
	
}