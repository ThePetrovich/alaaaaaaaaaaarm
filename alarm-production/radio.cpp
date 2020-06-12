#include "alarm.h"


void radio_setup()
{
	vw_set_rx_pin(RADIO_RX_PIN);
    vw_setup(RADIO_SPEED);
	
	vw_set_ptt_inverted(RADIO_RX_IS_INVERTED);
	
	vw_rx_start();
}

void radio_processCommand()
{
	uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) {
		Serial.print(F("Debug: got: "));
		
		for (int i = 0; i < buflen; i++) {
			Serial.print(buf[i]);
		}
		Serial.println("");
		
		if (!strcmp(RADIO_CMD_OPEN, buf)) {
			Serial.println(F("Debug: received a valid OPEN command"));
			actions_openDoor();
		}
		
		if (!strcmp(RADIO_CMD_PANIK, buf)) {
			Serial.println(F("Debug: received a valid PANIK command"));
			fsm_setState(FSM_STATE_PANIK);
		}
		
		if (!strcmp(RADIO_CMD_DROP, buf)) {
			Serial.println(F("Debug: received a valid DROP command"));
			if (fsm_getState() == FSM_STATE_PANIK) {
				fsm_setPreviousState();
			}
		}
	}
}
