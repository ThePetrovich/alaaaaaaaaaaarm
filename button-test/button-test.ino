#include <Button.h>

Button button1(13); // Connect your button between pin 2 and GND
Button button2(12); // Connect your button between pin 3 and GND
Button button3(11); // Connect your button between pin 4 and GND
Button button4(4); // Connect your button between pin 3 and GND
Button button5(3); // Connect your button between pin 4 and GND

void setup() {
	button1.begin();
	button2.begin();
	button3.begin();
	button4.begin();
	button5.begin();
	
	while (!Serial) { }; // for Leos
	Serial.begin(9600);
}

void loop() {
	if (button1.toggled()) {
		if (button1.read() == Button::PRESSED)
			Serial.println("Button on pin 13 has been pressed");
		else
			Serial.println("Button on pin 13 has been released");
	}
	if (button2.toggled()) {
		if (button2.read() == Button::PRESSED)
			Serial.println("Button on pin 12 has been pressed");
		else
			Serial.println("Button on pin 12 has been released");
	}
	if (button3.toggled()) {
		if (button3.read() == Button::PRESSED)
			Serial.println("Button on pin 11 has been pressed");
		else
			Serial.println("Button on pin 11 has been released");
	}
	if (button4.toggled()) {
		if (button4.read() == Button::PRESSED)
			Serial.println("Button on pin 4 has been pressed");
		else
			Serial.println("Button on pin 4 has been released");
	}
	if (button5.toggled()) {
		if (button5.read() == Button::PRESSED)
			Serial.println("Button on pin 3 has been pressed");
		else
			Serial.println("Button on pin 3 has been released");
	}
}