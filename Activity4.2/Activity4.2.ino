#define SW_1 4
#define SW_2 3
#define SW_3 2

#define LED_1 12
#define LED_2 11
#define LED_3 10

void	setup() {
	pinMode(SW_1, INPUT);
	pinMode(SW_2, INPUT);
	pinMode(SW_3, INPUT_PULLUP);
	pinMode(LED_1, OUTPUT);
	pinMode(LED_2, OUTPUT);
	pinMode(LED_3, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(SW_2), EXT0_ISR, FALLING);
	attachInterrupt(digitalPinToInterrupt(SW_3), EXT1_ISR, FALLING);
}

void	loop() {
	digitalWrite(LED_3, HIGH);
	delay(7000);
	digitalWrite(LED_3, LOW);

	digitalWrite(LED_2, HIGH);
	delay(3000);
	digitalWrite(LED_2, LOW);

	digitalWrite(LED_1, HIGH);
	delay(5000);
	digitalWrite(LED_1, LOW);
}

void	EXT0_ISR()
{
	digitalWrite(LED_3, LOW);
	digitalWrite(LED_2, LOW);
	digitalWrite(LED_1, HIGH);
	delay(5000);
}

void	EXT1_ISR()
{
	digitalWrite(LED_3, LOW);
	digitalWrite(LED_2, LOW);
	digitalWrite(LED_1, LOW);
	delay(5000);
}
