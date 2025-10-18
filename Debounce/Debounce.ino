#define BUTTON_1 4
#define BUTTON_2 3
#define BUTTON_3 2
#define LED_1 12
#define LED_2 11
#define LED_3 10

#define DEBOUNCE_DELAY 10

void setup()
{
	pinMode(BUTTON_1, INPUT);
	pinMode(BUTTON_2, INPUT);
	pinMode(BUTTON_3, INPUT_PULLUP);
	pinMode(LED_1, OUTPUT);
	pinMode(LED_2, OUTPUT);
	pinMode(LED_3, OUTPUT);
}

void loop()
{
	toggle_btn_1();
	toggle_btn_2();
	toggle_btn_3();
}

void	toggle_btn_1()
{
	static int				buttonState = LOW;
	static int				lastButtonState = LOW;
	static unsigned long	lastDebounceTime = 0;
	static int				led_state = LOW;
	int 					reading;

	reading = digitalRead(BUTTON_1);
	if (reading != lastButtonState)
		lastDebounceTime = millis();

	if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
	{
		if (reading != buttonState)
		{
			buttonState = reading;
			if (buttonState == HIGH)
			{
				led_state = !led_state;
				digitalWrite(LED_1, led_state);
			}
		}
	}
	lastButtonState = reading;
}

void	toggle_btn_2()
{
	static int				buttonState = LOW;
	static int				lastButtonState = LOW;
	static unsigned long	lastDebounceTime = 0;
	static int				led_state = LOW;
	int 					reading;

	reading = !digitalRead(BUTTON_2);
	if (reading != lastButtonState)
		lastDebounceTime = millis();

	if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
	{
		if (reading != buttonState)
		{
			buttonState = reading;
			if (buttonState == HIGH)
			{
				led_state = !led_state;
				digitalWrite(LED_2, led_state);
			}
		}
	}
	lastButtonState = reading;
}

void	toggle_btn_3()
{
	static int				buttonState = LOW;
	static int				lastButtonState = LOW;
	static unsigned long	lastDebounceTime = 0;
	static int				led_state = LOW;
	int 					reading;

	reading = !digitalRead(BUTTON_3);
	if (reading != lastButtonState)
		lastDebounceTime = millis();

	if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
	{
		if (reading != buttonState)
		{
			buttonState = reading;
			if (buttonState == HIGH)
			{
				led_state = !led_state;
				digitalWrite(LED_3, led_state);
			}
		}
	}
	lastButtonState = reading;
}
