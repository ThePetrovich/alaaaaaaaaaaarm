/*
 * rfid.h
 * 
 * Created: 09.06.2021 07:30:41
 * Author: ThePetrovich
 */


#ifndef _RFID_ALARM_H_
#define _RFID_ALARM_H_

typedef struct ram_key
{
	uint32_t id;
	uint64_t validTill;
	char name[32];
	struct ram_key *next;
	uint16_t eepromPosition;
} alarm_doorKey;

void rfid_setup();
void rfid_processCommand();

#endif