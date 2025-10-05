// HT16K33 display - Adafruit Library
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"

// Button
#define START_BTN 13
#define END_BTN 12
#define CONFIG_BTN 11
#define MODE_BTN 10

// Piezo (buzzer)
#define PIEZO 3

// Debounce Delay
#define DEBOUNCE_DELAY 50

// Setup initial time
static int				study_time = 30;
static int				rest_time = 5;
static int				mode = 0;

// Timer variables
static unsigned long	previousMillis = 0;
static unsigned long	currentMillis = 0;
static int				remainingSeconds = 0;
static bool				isRunning = false;
static bool				isStudyTime = true;
static bool				isConfigMode = false;
static bool				configStudyTime = true;

// Button state variables
static bool				lastStartBtnState = HIGH;
static bool				lastEndBtnState = HIGH;
static bool				lastConfigBtnState = HIGH;
static bool				lastModeBtnState = HIGH;

// Button debounce variables
static unsigned long	lastStartDebounce = 0;
static unsigned long	lastEndDebounce = 0;
static unsigned long	lastConfigDebounce = 0;
static unsigned long	lastModeDebounce = 0;

// 7 Segment
Adafruit_7segment		matrix = Adafruit_7segment();

void	setup(void)
{
	Serial.begin(9600);
	Wire.begin();
	pinMode(START_BTN, INPUT_PULLUP);
	pinMode(END_BTN, INPUT_PULLUP);
	pinMode(CONFIG_BTN, INPUT_PULLUP);
	pinMode(MODE_BTN, INPUT_PULLUP);

	// Initialize HT16K33 display
	matrix.begin(0x70);			// Default I2C address
	matrix.setBrightness(15);	// Brightness 0-15
	matrix.blinkRate(0);		// No blinking
	matrix.writeDisplay();

	// Set initial time to 00:00
	resetDisplayToZero();
}

void	loop(void)
{
	currentMillis = millis();

	checkStartButton();
	checkEndButton();

	// Only check config and mode buttons if NOT in running Pomodoro state
	if (!isRunning)
	{
		checkConfigButton();
		checkModeButton();
	}
	
	if (isRunning && !isConfigMode)
	{
		updateTimer();
	}
}

void	resetDisplayToZero()
{
	matrix.writeDigitNum(0, 0);	// First digit: 0
	matrix.writeDigitNum(1, 0);	// Second digit: 0
	matrix.writeDigitNum(3, 0);	// Fourth digit: 0 (skip colon position)
	matrix.writeDigitNum(4, 0);	// Fifth digit: 0
	matrix.drawColon(true);
	matrix.writeDisplay();
}

void	checkStartButton()
{
	bool currentState = digitalRead(START_BTN);

	if (currentState == LOW && lastStartBtnState == HIGH)
	{
		if (currentMillis - lastStartDebounce > DEBOUNCE_DELAY)
		{
			handleStartButton();
			lastStartDebounce = currentMillis;
		}
	}
	lastStartBtnState = currentState;
}

void	checkEndButton()
{
	bool currentState = digitalRead(END_BTN);

	if (currentState == LOW && lastEndBtnState == HIGH)
	{
		if (currentMillis - lastEndDebounce > DEBOUNCE_DELAY)
		{
			handleEndButton();
			lastEndDebounce = currentMillis;
		}
	}
	lastEndBtnState = currentState;
}

void	checkConfigButton()
{
	bool currentState = digitalRead(CONFIG_BTN);

	if (currentState == LOW && lastConfigBtnState == HIGH)
	{
		if (currentMillis - lastConfigDebounce > DEBOUNCE_DELAY)
		{
			handleConfigButton();
			lastConfigDebounce = currentMillis;
		}
	}
	lastConfigBtnState = currentState;
}

void	checkModeButton()
{
	bool currentState = digitalRead(MODE_BTN);

	if (currentState == LOW && lastModeBtnState == HIGH)
	{
		if (currentMillis - lastModeDebounce > DEBOUNCE_DELAY)
		{
			handleModeButton();
			lastModeDebounce = currentMillis;
		}
	}
	lastModeBtnState = currentState;
}

void	handleStartButton()
{
	if (isConfigMode)
	{
		// Increase time in config mode
		if (configStudyTime)
		{
			study_time = min(99, study_time + 1);
		}
		else
		{
			rest_time = min(99, rest_time + 1);
		}
		updateDisplay();
	}
	else
	{
		// Start/Pause timer in Pomodoro mode
		if (!isRunning)
		{
			// First start - initialize timer with current study/rest time
			if (remainingSeconds == 0)
			{
				remainingSeconds = isStudyTime ? study_time * 60 : rest_time * 60;
			}
			isRunning = true;
			previousMillis = currentMillis;
		}
		else
		{
			// Pause current session
			isRunning = false;
		}
	}
}

void	handleEndButton()
{
	if (isConfigMode)
	{
		// Decrease time in config mode
		if (configStudyTime)
		{
			study_time = max(1, study_time - 1);
		}
		else
		{
			rest_time = max(1, rest_time - 1);
		}
		updateDisplay();
	}
	else
	{
		// End current pomodoro session - reset to 00:00
		isRunning = false;
		remainingSeconds = 0;
		resetDisplayToZero();
	}
}

void	handleConfigButton()
{
	if (!isConfigMode)
	{
		// Enter config mode - show current study time
		isConfigMode = true;
		isRunning = false;
		configStudyTime = true;  // Always start with study time
		updateDisplay();
		Serial.println("Entered config mode - editing STUDY time");
	}
	else
	{
		// Confirm and exit config mode - reset to 00:00
		isConfigMode = false;
		remainingSeconds = 0;
		resetDisplayToZero();
		Serial.println("Exited config mode");
	}
}

void	handleModeButton()
{
	if (isConfigMode)
	{
		// Switch between study and rest time configuration
		configStudyTime = !configStudyTime;
		updateDisplay();
		Serial.print("Now editing: ");
		Serial.println(configStudyTime ? "STUDY time" : "REST time");
	}
	else
	{
		// Change operation mode (Normal/Long/Long Long)
		change_mode();
		remainingSeconds = 0;
		resetDisplayToZero();
		Serial.print("Mode changed to: ");
		Serial.println(mode);
	}
}

void	change_mode(void)
{
	mode = (mode + 1) % 3;
	if (mode == 0)
	{
		study_time = 30;
		rest_time = 5;
	}
	else if (mode == 1)
	{
		study_time = 60;
		rest_time = 10;
	}
	else if (mode == 2)
	{
		study_time = 90;
		rest_time = 15;
	}
}

void	updateTimer()
{
	if (currentMillis - previousMillis >= 1000)
	{
		previousMillis = currentMillis;

		if (remainingSeconds > 0)
		{
			remainingSeconds--;
			updateDisplay();
		}
		else
		{
			// Time's up - switch between study and rest
			isStudyTime = !isStudyTime;
			remainingSeconds = isStudyTime ? study_time * 60 : rest_time * 60;
			playAlarm();
			updateDisplay();
		}
	}
}

void	updateDisplay()
{
	if (isConfigMode)
	{
		// Show configuration time (minutes only)
		int minutes = configStudyTime ? study_time : rest_time;
		matrix.print(minutes * 100); // Format as MM00
		matrix.drawColon(false);	 // Turn off colon in config mode
		matrix.writeDisplay();
	}
	else
	{
		// Show timer in MM:SS format
		int minutes = remainingSeconds / 60;
		int seconds = remainingSeconds % 60;
		matrix.print(minutes * 100 + seconds);
		matrix.drawColon(true); // Enable colon for time display
		matrix.writeDisplay();
	}
}

void	playAlarm()
{
	for (int i = 0; i < 3; i++)
	{
		tone(PIEZO, 1000, 500);
		delay(600);
	}
}
