#include "RobotCar.h"

// Setup motor
void	setup_motor(void)
{
	// Set up Left Motor
	pinMode(ENA, OUTPUT);
	pinMode(INA, OUTPUT);
	pinMode(INB, OUTPUT);

	// Set up right Motor
	pinMode(ENB, OUTPUT);
	pinMode(INC, OUTPUT);
	pinMode(IND, OUTPUT);
}

// Set left and right motor to low;
void	set_zero(void)
{
	digitalWrite(INA, LOW);
	digitalWrite(INB, LOW);
	digitalWrite(INC, LOW);
	digitalWrite(IND, LOW);
	analogWrite(ENA, 0);
	analogWrite(ENB, 0);
}

// Both motor forward
void	forward(int speed)
{
	analogWrite(ENA, speed * LEFT_CALIBRATE);
	analogWrite(ENB, speed * RIGHT_CALIBRATE);
	digitalWrite(INA, HIGH);
	digitalWrite(INB, LOW);
	digitalWrite(INC, HIGH);
	digitalWrite(IND, LOW);
}

// Motor turn right
void	shift_right(int speed)
{
	analogWrite(ENA, speed * LEFT_CALIBRATE);
	analogWrite(ENB, 0);
	digitalWrite(INA, HIGH);
	digitalWrite(INB, LOW);
	digitalWrite(INC, LOW);
	digitalWrite(IND, LOW);
}

// Motor turn left
void	shift_left(int speed)
{
	analogWrite(ENA, 0);
	analogWrite(ENB, speed * RIGHT_CALIBRATE);
	digitalWrite(INA, LOW);
	digitalWrite(INB, LOW);
	digitalWrite(INC, HIGH);
	digitalWrite(IND, LOW);
}
