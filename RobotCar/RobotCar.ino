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
	// move_one_block(100);
	// delay(500);
	// turn_left(100);
	// delay(500);
	// turn_right(100);
	// delay(500);
	// move_one_block(100);
	// delay(500);
}

void	loop(void)
{
	log(0);

	move_one_block(130);
	delay(500);
	turn_right(100);
	delay(500);
}

void	start_to_check(void)
{
}

void	check_to_start(void)
{
}
