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
}

void	loop(void)
{
	start_to_check();
	check_to_start();
}

void	start_to_check(void)
{
	while (cur_col != 5 && cur_row != 0)
	{

	}
}

void	check_to_start(void)
{
	
}
