// PWM Motor A (Left Motor)
#define ENA 10
#define INA 9
#define INB 8

// PWM Motor B (Right Motor)
#define ENB 6
#define INC 5
#define IND 4

#define LEFT_CALIBRATE 0.78
#define RIGHT_CALIBRATE 1

void	setup()
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

void	loop()
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		move_forward(255, 1000);
		delay(1000);
		turn_left(255, 375);
		delay(1000);
	}
}

void	set_zero()
{
	digitalWrite(INA, LOW);
	digitalWrite(INB, LOW);
	digitalWrite(INC, LOW);
	digitalWrite(IND, LOW);
	analogWrite(ENA, 0);
	analogWrite(ENB, 0);
}

void	move_forward(int speed, int time_ms)
{
	int	l_speed;
	int	r_speed;

	l_speed = speed * LEFT_CALIBRATE;
	r_speed = speed * RIGHT_CALIBRATE;
	analogWrite(ENA, speed);
	analogWrite(ENB, speed);
	digitalWrite(INA, HIGH);
	digitalWrite(INB, LOW);
	digitalWrite(INC, HIGH);
	digitalWrite(IND, LOW);
	delay(time_ms);
	set_zero();
}

void	turn_left(int speed, int time_ms)
{
	int	l_speed;
	int	r_speed;

	l_speed = speed * LEFT_CALIBRATE;
	r_speed = speed * RIGHT_CALIBRATE;
	analogWrite(ENA, speed);
	analogWrite(ENB, speed);
	digitalWrite(INA, LOW);
	digitalWrite(INB, LOW);
	digitalWrite(INC, HIGH);
	digitalWrite(IND, LOW);
	delay(time_ms);
	set_zero();
}

void	turn_right(int speed, int time_ms)
{
	int	l_speed;
	int	r_speed;

	l_speed = speed * LEFT_CALIBRATE;
	r_speed = speed * RIGHT_CALIBRATE;
	analogWrite(ENA, speed);
	analogWrite(ENB, speed);
	digitalWrite(INA, HIGH);
	digitalWrite(INB, LOW);
	digitalWrite(INC, LOW);
	digitalWrite(IND, LOW);
	delay(time_ms);
	set_zero();
}
