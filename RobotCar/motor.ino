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
	delay(5);
}

// Both motor forward
void	forward(int speed)
{
	set_zero();
	delay(5);
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
	set_zero();
	delay(5);
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
	set_zero();
	delay(5);
	analogWrite(ENA, 0);
	analogWrite(ENB, speed * RIGHT_CALIBRATE);
	digitalWrite(INA, LOW);
	digitalWrite(INB, LOW);
	digitalWrite(INC, HIGH);
	digitalWrite(IND, LOW);
}

// Proper pivot right (for turns)
void	pivot_right(int speed)
{
	set_zero();
	delay(5);
	analogWrite(ENA, speed * LEFT_CALIBRATE);
	analogWrite(ENB, speed * RIGHT_CALIBRATE);
	digitalWrite(INA, HIGH);
	digitalWrite(INB, LOW);
	digitalWrite(INC, LOW);
	digitalWrite(IND, HIGH);
}

// Proper pivot left (for turns)
void	pivot_left(int speed)
{
	set_zero();
	delay(5);
	analogWrite(ENA, speed * LEFT_CALIBRATE);
	analogWrite(ENB, speed * RIGHT_CALIBRATE);
	digitalWrite(INA, LOW);
	digitalWrite(INB, HIGH);
	digitalWrite(INC, HIGH);
	digitalWrite(IND, LOW);
}

// Both motor backward
void	backward(int speed)
{
	set_zero();
	delay(5);
	analogWrite(ENA, speed * LEFT_CALIBRATE);
	analogWrite(ENB, speed * RIGHT_CALIBRATE);
	digitalWrite(INA, LOW);
	digitalWrite(INB, HIGH);
	digitalWrite(INC, LOW);
	digitalWrite(IND, HIGH);
}

// Motor shift right while moving backward
void	shift_right_backward(int speed)
{
	set_zero();
	delay(5);
	analogWrite(ENA, speed * LEFT_CALIBRATE);
	analogWrite(ENB, 0);
	digitalWrite(INA, LOW);
	digitalWrite(INB, HIGH);
	digitalWrite(INC, LOW);
	digitalWrite(IND, LOW);
}

// Motor shift left while moving backward
void	shift_left_backward(int speed)
{
	set_zero();
	delay(5);
	analogWrite(ENA, 0);
	analogWrite(ENB, speed * RIGHT_CALIBRATE);
	digitalWrite(INA, LOW);
	digitalWrite(INB, LOW);
	digitalWrite(INC, LOW);
	digitalWrite(IND, HIGH);
}
