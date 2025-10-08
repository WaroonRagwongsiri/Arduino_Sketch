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

static int	direction = DIR_UP;

static int	cur_row = 5;
static int	cur_col = 0;

void	setup(void)
{
	setup_motor();
	pinMode(BUZZER, OUTPUT);
	Serial.begin(9600);
	digitalWrite(BUZZER, HIGH);
	delay(1000);
}

void	loop(void)
{
	update_map(board, read_ultrasonic(), &direction, cur_row, cur_col);
	log(0, board);
	move_one_block(120);
	delay(3000);
}

void	start_to_check(void)
{
}

void	check_to_start(void)
{
}
