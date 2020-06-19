#include <ButtonArduino.h>
#include <VirtualWire.h>

#define RADIO_CMD_OPEN "FBIOPNUP"
#define RADIO_CMD_PANIK "HHAALLPP"
#define RADIO_CMD_DROP "IDCANMRE"

#define BUTTON_PANIK_PIN 2
#define BUTTON_OPEN_PIN 3

#define RADIO_TX_PIN 4
#define RADIO_SPEED 1000
#define RADIO_RX_IS_INVERTED 0

Button panik(2, 5000);
Button open(3, 5000);

void setup() 
{
	Serial.begin(9600);
    Serial.println("setup");
	
	vw_set_tx_pin(RADIO_TX_PIN);
	
	vw_set_ptt_inverted(RADIO_RX_IS_INVERTED);
	
    vw_setup(RADIO_SPEED);
	
	Serial.begin(9600);
}

void loop() 
{
	const char *msgOpen = RADIO_CMD_OPEN;
	const char *msgDrop = RADIO_CMD_DROP;
	const char *msgPanik = RADIO_CMD_PANIK;
	
	if (panik.checkPress() == -1) {
        Serial.println("Debug: PANIK long press");
		
		digitalWrite(13, true);
        
        for (int i = 0; i < 10; i++) {
            vw_send((uint8_t *)msgPanik, strlen(msgPanik));
            vw_wait_tx();
        }
		
		digitalWrite(13, false);
    } 
	else if (panik.checkPress() == 1)	{
        Serial.println("Debug: PANIK short press");
		
		digitalWrite(13, true);
        
        for (int i = 0; i < 10; i++) {
            vw_send((uint8_t *)msgDrop, strlen(msgDrop));
            vw_wait_tx();
        }
        
		digitalWrite(13, false);
    }
	
	if (open.checkPress() == 1) {
        Serial.println("Debug: OPEN short press");
		
		digitalWrite(13, true);
        
        for (int i = 0; i < 10; i++) {
            vw_send((uint8_t *)msgOpen, strlen(msgOpen));
            vw_wait_tx();
        }
        
		digitalWrite(13, false);
    } 
}