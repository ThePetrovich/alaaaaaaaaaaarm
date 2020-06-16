#include "alarm.h"
#include <VirtualWire.h>

static uint8_t buf[VW_MAX_MESSAGE_LEN];
static uint8_t buflen = VW_MAX_MESSAGE_LEN;

void radio_setup()
{
	vw_set_rx_pin(RADIO_RX_PIN);
    vw_setup(RADIO_SPEED);
	
	vw_set_ptt_inverted(RADIO_RX_IS_INVERTED);
	
	vw_rx_start();
}

int radio_checkOpen()
{
	if (vw_get_message(buf, &buflen)) {
		Serial.print(F("Debug: got: "));
		
		for (int i = 0; i < buflen; i++) {
			Serial.print(buf[i]);
		}
		Serial.println("");
		
		if (!strcmp(RADIO_CMD_OPEN, (const char*)buf)) {
			Serial.println(F("Debug: received a valid OPEN command"));
			return 1;
		}
	}
	return 0;
}

int radio_checkPanik()
{
	if (vw_get_message(buf, &buflen)) {
		Serial.print(F("Debug: got: "));
		
		for (int i = 0; i < buflen; i++) {
			Serial.print(buf[i]);
		}
		Serial.println("");

		if (!strcmp(RADIO_CMD_PANIK, (const char*)buf)) {
			Serial.println(F("Debug: received a valid PANIK command"));
			return 1;
		}
	}
	return 0;
}

int radio_checkDrop()
{
	if (vw_get_message(buf, &buflen)) {
		Serial.print(F("Debug: got: "));
		
		for (int i = 0; i < buflen; i++) {
			Serial.print(buf[i]);
		}
		Serial.println("");
		
		if (!strcmp(RADIO_CMD_DROP, (const char*)buf)) {
			Serial.println(F("Debug: received a valid DROP command"));
			return 1;
		}
	}
	return 0;
}
