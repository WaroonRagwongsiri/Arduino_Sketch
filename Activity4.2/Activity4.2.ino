#define SW_1 3
#define SW_2 4
#define SW_3 2

#define LED_1 12
#define LED_2 11
#define LED_3 10

static unsigned int	interrupt_1 = 0;
static unsigned int	interrupt_2 = 0;

void	setup() {
	pinMode(SW_1, INPUT);
	pinMode(SW_2, INPUT);
	pinMode(SW_3, INPUT_PULLUP);
	pinMode(LED_1, OUTPUT);
	pinMode(LED_2, OUTPUT);
	pinMode(LED_3, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(SW_1), EXT0_ISR, FALLING);
	attachInterrupt(digitalPinToInterrupt(SW_3), EXT1_ISR, FALLING);
	Serial.begin(9600);
}

void	loop() {
	digitalWrite(LED_3, LOW);
	digitalWrite(LED_2, LOW);
	digitalWrite(LED_1, LOW);

	digitalWrite(LED_3, HIGH);
	waitInterrupt(LED_3, 7000);
	digitalWrite(LED_3, LOW);
	digitalWrite(LED_2, LOW);
	digitalWrite(LED_1, LOW);

	digitalWrite(LED_2, HIGH);
	waitInterrupt(LED_2, 3000);
	digitalWrite(LED_3, LOW);
	digitalWrite(LED_2, LOW);
	digitalWrite(LED_1, LOW);

	digitalWrite(LED_1, HIGH);
	waitInterrupt(LED_1, 5000);
	digitalWrite(LED_3, LOW);
	digitalWrite(LED_2, LOW);
	digitalWrite(LED_1, LOW);
}

void	EXT0_ISR()
{
	digitalWrite(LED_3, LOW);
	digitalWrite(LED_2, LOW);
	digitalWrite(LED_1, HIGH);
	interrupt_1 = 1;
}

void	EXT1_ISR()
{
	digitalWrite(LED_3, LOW);
	digitalWrite(LED_2, LOW);
	digitalWrite(LED_1, LOW);
	interrupt_2 = 1;
}

void	waitInterrupt(int led, float wait_time)
{
	unsigned long	currentMillis;
	unsigned long	previousMillis = millis();
	float			deltaTime;
	while(wait_time > 0)
	{
		currentMillis = millis();
		deltaTime = currentMillis - previousMillis;
		previousMillis = currentMillis;
		wait_time -= deltaTime;
		Serial.println(wait_time);
		if (interrupt_1)
		{
			interrupt_1 = 0;
			digitalWrite(LED_2, LOW);
			digitalWrite(LED_3, LOW);
			waitInterrupt(led, 5000);
			digitalWrite(LED_1, LOW);
			previousMillis = millis();
			digitalWrite(led, HIGH);
			continue ;
		}
		else if (interrupt_2)
		{
			interrupt_2 = 0;
			digitalWrite(LED_2, LOW);
			digitalWrite(LED_3, LOW);
			waitInterrupt(led, 5000);
			digitalWrite(LED_1, LOW);
			previousMillis = millis();
			digitalWrite(led, HIGH);
			continue ;
		}
	}
}
