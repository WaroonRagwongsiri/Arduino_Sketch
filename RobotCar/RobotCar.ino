#include "RobotCar.h"

// 0 is space
// 1 is car
// 2 is UNK
// 3 is obstacle
// 4 is block
static int	board[BOARD_SIZE][BOARD_SIZE] = {
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0},
	{CAR, 0, 0, 0, 0, 0},
};

static int	cur_row = 5;
static int	cur_col = 0;

void	setup(void)
{
	setup_motor();
	pinMode(BUZZER, OUTPUT);
	pinMode(TRIGGER_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
	Serial.begin(9600);
	digitalWrite(BUZZER, HIGH);
	delay(1000);
}

void	loop(void)
{
	log(0);
	// walk_direction(120, 'U');
	// delay(500);
	walk_direction(120, 'R');
	delay(500);
	// walk_direction(120, 'D');
	// delay(500);
	walk_direction(120, 'L');
	delay(500);
}

void	start_to_check(void)
{
}

void	check_to_start(void)
{
}
