#include "RobotCar.h"

void	face_direction(int speed, char path, int *direction)
{
	if (path == 'U')
		face_up(speed, direction);
	else if (path == 'D')
		face_down(speed, direction);
	else if (path == 'L')
		face_left(speed, direction);
	else if (path == 'R')
		face_right(speed, direction);
}

void	face_up(int speed, int *direction)
{
	if (*direction == DIR_UP)
		return ;
	else if (*direction == DIR_DOWN)
		turn_around(speed);
	else if (*direction == DIR_LEFT)
		turn_right(speed);
	else if (*direction == DIR_RIGHT)
		turn_left(speed);
	*direction = DIR_UP;
}

void	face_down(int speed, int *direction)
{
	if (*direction == DIR_DOWN)
		return ;
	else if (*direction == DIR_UP)
		turn_around(speed);
	else if (*direction == DIR_LEFT)
		turn_left(speed);
	else if (*direction == DIR_RIGHT)
		turn_right(speed);
	*direction = DIR_DOWN;
}

void	face_left(int speed, int *direction)
{
	if (*direction == DIR_LEFT)
		return ;
	else if (*direction == DIR_RIGHT)
		turn_around(speed);
	else if (*direction == DIR_UP)
		turn_left(speed);
	else if (*direction == DIR_DOWN)
		turn_right(speed);
	*direction = DIR_LEFT;
}

void	face_right(int speed, int *direction)
{
	if (*direction == DIR_RIGHT)
		return ;
	else if (*direction == DIR_LEFT)
		turn_around(speed);
	else if (*direction == DIR_UP)
		turn_right(speed);
	else if (*direction == DIR_DOWN)
		turn_left(speed);
	*direction = DIR_RIGHT;
}
