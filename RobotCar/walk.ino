#include "RobotCar.h"

void	walk_direction(int speed, char path)
{
	static int	direction = DIR_UP;
	if (path == 'U')
		walk_up(speed, &direction);
	else if (path == 'D')
		walk_down(speed, &direction);
	else if (path == 'L')
		walk_left(speed, &direction);
	else if (path == 'R')
		walk_right(speed, &direction);
}

void	walk_up(int speed, int *direction)
{
	if (*direction == DIR_UP)
		move_one_block(speed);
	else if (*direction == DIR_DOWN)
	{
		turn_around(speed);
		move_one_block(speed);
	}
	else if (*direction == DIR_LEFT)
	{
		turn_right(speed);
		move_one_block(speed);
	}
	else if (*direction == DIR_RIGHT)
	{
		turn_left(speed);
		move_one_block(speed);
	}
	*direction = DIR_UP;
}

void	walk_down(int speed, int *direction)
{
	if (*direction == DIR_DOWN)
		move_one_block(speed);
	else if (*direction == DIR_UP)
	{
		turn_around(speed);
		move_one_block(speed);
	}
	else if (*direction == DIR_LEFT)
	{
		turn_left(speed);
		move_one_block(speed);
	}
	else if (*direction == DIR_RIGHT)
	{
		turn_right(speed);
		move_one_block(speed);
	}
	*direction = DIR_DOWN;
}

void	walk_left(int speed, int *direction)
{
	if (*direction == DIR_LEFT)
		move_one_block(speed);
	else if (*direction == DIR_RIGHT)
	{
		turn_around(speed);
		move_one_block(speed);
	}
	else if (*direction == DIR_UP)
	{
		turn_left(speed);
		move_one_block(speed);
	}
	else if (*direction == DIR_DOWN)
	{
		turn_right(speed);
		move_one_block(speed);
	}
	*direction = DIR_LEFT;
}

void	walk_right(int speed, int *direction)
{
	if (*direction == DIR_RIGHT)
		move_one_block(speed);
	else if (*direction == DIR_LEFT)
	{
		turn_around(speed);
		move_one_block(speed);
	}
	else if (*direction == DIR_UP)
	{
		turn_right(speed);
		move_one_block(speed);
	}
	else if (*direction == DIR_DOWN)
	{
		turn_left(speed);
		move_one_block(speed);
	}
	*direction = DIR_RIGHT;
}
