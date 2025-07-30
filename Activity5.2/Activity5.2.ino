#define LED_1 11
#define LED_2 10
#define LED_3 9
#define LED_4 8

void setup() {
	Serial.begin(9600);
	pinMode(LED_1, OUTPUT);
	pinMode(LED_2, OUTPUT);
	pinMode(LED_3, OUTPUT);
	pinMode(LED_4, OUTPUT);
}

// pulldown 220
// S1 220 -> 504
// S2 470 -> 317
// S3 1000 -> 181
// S4 4700 -> 43
void loop() {
	int analog = analogRead(A0);
	digitalWrite(LED_1, LOW);
	digitalWrite(LED_2, LOW);
	digitalWrite(LED_3, LOW);
	digitalWrite(LED_4, LOW);
	if (analog > 500)
	{
		digitalWrite(LED_1, HIGH);	
	}
	else if (analog > 300)
	{
		digitalWrite(LED_2, HIGH);
	}
	else if (analog > 150)
	{
		digitalWrite(LED_3, HIGH);
	}
	else if (analog > 20)
	{
		digitalWrite(LED_4, HIGH);
	}
	Serial.println(analog);
}
