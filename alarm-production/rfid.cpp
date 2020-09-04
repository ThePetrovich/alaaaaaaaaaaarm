#include "alarm.h"
#include <Wiegand.h>

extern WIEGAND wg;

uint32_t wg_authorized_keys[] = {0x69EE84}; //Debug key
const uint8_t wg_authorized_keys_num = 1;

void wiegand_setup() 
{
    wg.begin(WIEGAND_DATA1_PIN, WIEGAND_DATA2_PIN);
}

void wiegand_processCommand() 
{
    uint32_t code = wg.getCode();
    uint8_t result = 0;
    if(wg.available())
	{
		Serial.print("Wiegand HEX = ");
		Serial.print(code, HEX);
		Serial.print(", DECIMAL = ");
		Serial.print(code);
		Serial.print(", Type W");
		Serial.println(wg.getWiegandType());    

        for (int i = 0; i < wg_authorized_keys_num; i++) {
            if (code == wg_authorized_keys[i]) {
                result = 1;
                break;
            }
        }

        if (result) {
            Serial.println("Found keycard code in authorized keycards list");
            actions_openDoor();
            delay(500);
            actions_closeDoor();
        }
        else {
            Serial.println("Unauthorized keycard");
        }
	}
}