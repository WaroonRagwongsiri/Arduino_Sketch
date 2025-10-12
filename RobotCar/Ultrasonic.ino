#include "RobotCar.h"

long	read_ultrasonic(void)
{
	long duration;

	pinMode(TRIGGER_PIN, OUTPUT);
	digitalWrite(TRIGGER_PIN, LOW);
	delayMicroseconds(2);
	digitalWrite(TRIGGER_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIGGER_PIN, LOW);
	pinMode(ECHO_PIN, INPUT);
		
	// ADD TIMEOUT
	duration = pulseIn(ECHO_PIN, HIGH, 20000);
	if (duration == 0)
		return (0);
	return to_cm(duration);
}

// Speed of sound is 340 m/s or 29.4 microseconds / cm
int	to_cm(long micro_seconds)
{
	return ((int) micro_seconds / 29.4 / 2);
}
