/*
 * eeprom.h
 * 
 * Created: 09.06.2021 07:30:41
 * Author: ThePetrovich
 */


#ifndef _EEPROM_ALARM_H_
#define _EEPROM_ALARM_H_

#define EEPROM_MAGIC 0xDEADC0DE

#include <stdint.h>

typedef struct eeprom_header 
{
	uint32_t magic;
	uint8_t storedKeys;
	uint8_t flags;
	uint16_t keyStoreStart;
} alarm_eepromHeader;

typedef struct eeprom_key 
{
	uint32_t id;
	char name[32];
	uint64_t validTill;
} alarm_eepromKey;

alarm_eepromHeader eeprom_readHeader();
void eeprom_writeHeader(alarm_eepromHeader *header);
uint16_t eeprom_searchKey(uint32_t id);
alarm_eepromKey eeprom_readKey(uint16_t position);
uint16_t eeprom_writeKey(struct key_ram *data);

#endif