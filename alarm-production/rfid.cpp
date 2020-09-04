#include "alarm.h"
#include <Wiegand.h>
#include <String.h>

extern WIEGAND wg;

uint32_t wg_authorized_keys[] = {0x69EE84}; //Debug key
char wg_names[][16] = {"Debug"};
const uint8_t wg_authorized_keys_num = 1;

void wiegand_setup() 
{
    wg.begin(WIEGAND_DATA1_PIN, WIEGAND_DATA2_PIN);
}

void wiegand_processCommand() 
{
    uint32_t code = wg.getCode();
    int result = 0;
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
                result = i;
                break;
            }
        }

        if (result) {
            Serial.println("Found keycard code in authorized keycards list");
            Serial.print("Username = ");
            Serial.println(wg_names[result]);
            pinMode(DOOR_OPEN_PIN, INPUT);
            digitalWrite(DOOR_OPEN_PIN, LOW);
            delay(500);
            pinMode(DOOR_OPEN_PIN, OUTPUT);
            digitalWrite(DOOR_OPEN_PIN, HIGH);
        }
        else {
            Serial.println("Unauthorized keycard");
        }
	}
}