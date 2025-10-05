#include "RobotCar.h"

long	read_ultrasonic(void)
{
	pinMode(TRIGGER_PIN, OUTPUT);
	digitalWrite(TRIGGER_PIN, LOW);
	delayMicroseconds(2);
	digitalWrite(TRIGGER_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIGGER_PIN, LOW);
	pinMode(ECHO_PIN, INPUT);
	return (pulseIn(ECHO_PIN, HIGH));
}

// Speed of sound is 340 m/s or 29.4 microseconds / cm
int	to_cm(long micro_seconds)
{
	return ((int) micro_seconds / 29.4 / 2);
}
