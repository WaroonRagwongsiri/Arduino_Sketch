#define PIN1 10
#define PIN2 11
#define PIN3 12

void setup() {
	allOff();
}

void loop() {
	lightLED(1);
	delay(500);
	
	lightLED(2);
	delay(500);
	
	lightLED(3);
	delay(500);
	
	lightLED(4);
	delay(500);
	
	lightLED(5);
	delay(500);
	
	lightLED(6);
	delay(500);

	lightLED(5);
	delay(500);

	lightLED(4);
	delay(500);

	lightLED(3);
	delay(500);

	lightLED(2);
	delay(500);
}

void lightLED(int ledNumber) {
	allOff();
	
	switch(ledNumber)
	{
		// LED between PIN3(+) and PIN1(-)
		case 1:
			pinMode(PIN1, OUTPUT);
			pinMode(PIN3, OUTPUT);
			digitalWrite(PIN1, LOW);
			digitalWrite(PIN3, HIGH);
			break;
		// LED between PIN1(+) and PIN3(-)
		case 2:
			pinMode(PIN1, OUTPUT);
			pinMode(PIN3, OUTPUT);
			digitalWrite(PIN1, HIGH);
			digitalWrite(PIN3, LOW);
			break;
		// LED between PIN1(+) and PIN2(-)
		case 3:
			pinMode(PIN1, OUTPUT);
			pinMode(PIN2, OUTPUT);
			digitalWrite(PIN1, HIGH);
			digitalWrite(PIN2, LOW);
			break;
		// LED between PIN2(+) and PIN1(-)
		case 4:
			pinMode(PIN1, OUTPUT);
			pinMode(PIN2, OUTPUT);
			digitalWrite(PIN1, LOW);
			digitalWrite(PIN2, HIGH);
			break;
		// LED between PIN2(+) and PIN3(-)
		case 5:
			pinMode(PIN2, OUTPUT);
			pinMode(PIN3, OUTPUT);
			digitalWrite(PIN2, HIGH);
			digitalWrite(PIN3, LOW);
			break;
		// LED between PIN3(+) and PIN2(-)
		case 6:
			pinMode(PIN2, OUTPUT);
			pinMode(PIN3, OUTPUT);
			digitalWrite(PIN2, LOW);
			digitalWrite(PIN3, HIGH);
			break;
	}
}

void allOff() {
	// Set all pins to input (high impedance) to turn off all LEDs
	pinMode(PIN1, INPUT);
	pinMode(PIN2, INPUT);
	pinMode(PIN3, INPUT);
}
