#define MOSFET1_PIN 5
#define MOSFET2_PIN 6
#define MOSFET3_PIN 9

void setup() {
	pinMode(MOSFET1_PIN, OUTPUT);
	pinMode(MOSFET2_PIN, OUTPUT);
	pinMode(MOSFET3_PIN, OUTPUT);
	Serial.begin(9600);
	while (!Serial) { }; // for Leos
}

void loop() {
	Serial.println("Switching ON MOSFET at pin 5");
	digitalWrite(MOSFET1_PIN, HIGH);
	delay(5000);
	Serial.println("Switching OFF MOSFET at pin 5");
	digitalWrite(MOSFET1_PIN, LOW);
	delay(1000);
	Serial.println();
	
	Serial.println("Switching ON MOSFET at pin 6");
	digitalWrite(MOSFET2_PIN, HIGH);
	delay(5000);
	Serial.println("Switching OFF MOSFET at pin 6");
	digitalWrite(MOSFET2_PIN, LOW);
	delay(1000);
	Serial.println();
	
	Serial.println("Switching ON MOSFET at pin 9");
	digitalWrite(MOSFET3_PIN, HIGH);
	delay(5000);
	Serial.println("Switching OFF MOSFET at pin 9");
	digitalWrite(MOSFET3_PIN, LOW);
	delay(1000);
	Serial.println();
}