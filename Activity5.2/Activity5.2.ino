#define LED_1 8
#define LED_2 9
#define LED_3 10
#define LED_4 11

void setup() {
	Serial.begin(9600);
	pinMode(LED_1, OUTPUT);
	pinMode(LED_2, OUTPUT);
	pinMode(LED_3, OUTPUT);
	pinMode(LED_4, OUTPUT);
}

// S1 -> 852
// S2 -> 731
// S3 -> 568
// S4 -> 393
void loop() {
	int analog = analogRead(A0);
	if (analog < 450 && analog >= 300)
	{
		digitalWrite(LED_1, HIGH);
	}
	else if (analog < 650  && analog >= 500)
	{
		digitalWrite(LED_2, HIGH);
	}
	else if (analog < 750  && analog >= 700)
	{
		digitalWrite(LED_3, HIGH);
	}
	else if (analog < 950  && analog >= 800)
	{
		digitalWrite(LED_4, HIGH);
	}
	digitalWrite(LED_1, LOW);
	digitalWrite(LED_2, LOW);
	digitalWrite(LED_3, LOW);
	digitalWrite(LED_4, LOW);
}
