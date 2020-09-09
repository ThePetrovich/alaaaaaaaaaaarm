#include "alarm.h"
#include "keys.h"
#include "devices.h"
#include <Wiegand.h>
#include <String.h>

extern WIEGAND wg;

void wiegand_setup() 
{
    wg.begin(WIEGAND_DATA1_PIN, WIEGAND_DATA2_PIN);
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
