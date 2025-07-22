#define	SW_1 4
#define	SW_2 3
#define	SW_3 2

#define	LED_1 12
#define	LED_2 11
#define	LED_3 10

// State for toggle
static int		led_state[3] = {LOW, LOW, LOW};
static int		sw_state[3];
static int		last_sw_state[3] = {LOW, HIGH, HIGH};
unsigned long	lastDebounceTime[3] = {0, 0, 0}; 
unsigned long	debounceDelay = 10;
static int		reading[3] = {0, 0, 0};

void	setup() {
	pinMode(SW_1, INPUT);
	pinMode(SW_2, INPUT);
	pinMode(SW_3, INPUT_PULLUP);
	pinMode(LED_1, OUTPUT);
	pinMode(LED_2, OUTPUT);
	pinMode(LED_3, OUTPUT);
	digitalWrite(LED_1, led_state[0]);
	digitalWrite(LED_2, led_state[1]);
	digitalWrite(LED_3, led_state[2]);
}

void	loop() {
	// press_once();
	toggle();
}

void	press_once()
{
	if (digitalRead(SW_1) == HIGH)
	{
		digitalWrite(LED_1, HIGH);
	}
	if (digitalRead(SW_2) == LOW)
	{
		digitalWrite(LED_2, HIGH);
	}
	if (digitalRead(SW_3) == LOW)
	{
		digitalWrite(LED_3, HIGH);
	}
}

void	toggle()
{
	reading[0] = digitalRead(SW_1);
	reading[1] = digitalRead(SW_2);
	reading[2] = digitalRead(SW_3);

	pulldown(0);
	pullup(1);
	pullup(2);
	digitalWrite(LED_1, led_state[0]);
	digitalWrite(LED_2, led_state[1]);
	digitalWrite(LED_3, led_state[2]);
}

void	pulldown(int sw)
{
	if (reading[sw] != last_sw_state[sw])
	{
		lastDebounceTime[sw] = millis();
	}

	if (millis() - lastDebounceTime[sw] > debounceDelay)
	{
		if (reading[sw] != sw_state[sw])
		{
			sw_state[sw] = reading[sw];

			if (sw_state[sw] == HIGH)
			{
				led_state[sw] = !led_state[sw];
			}
		}
	}
	last_sw_state[sw] = reading[sw];
}

void	pullup(int sw)
{
	if (reading[sw] != last_sw_state[sw])
	{
		lastDebounceTime[sw] = millis();
	}

	if (millis() - lastDebounceTime[sw] > debounceDelay)
	{
		if (reading[sw] != sw_state[sw])
		{
			sw_state[sw] = reading[sw];

			if (sw_state[sw] == LOW)
			{
				led_state[sw] = !led_state[sw];
			}
		}
	}
	last_sw_state[sw] = reading[sw];
}
