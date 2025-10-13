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

// If walkable in the direction walk then update cur_row and cur_col then return 1
int	walk(int speed, char path, int *direction, int board[BOARD_SIZE][BOARD_SIZE], int *cur_row, int *cur_col)
{
	int	target_row = *cur_row;
	int	target_col = *cur_col;
	
	face_direction(speed, path, direction);
	update_map(board, read_ultrasonic(), direction, *cur_row, *cur_col);

	// Calculate target position based on direction
	if (path == 'U')
		target_row = *cur_row - 1;
	else if (path == 'D')
		target_row = *cur_row + 1;
	else if (path == 'L')
		target_col = *cur_col - 1;
	else if (path == 'R')
		target_col = *cur_col + 1;

	// If the path is blocked
	if (!is_walkable(target_row, target_col, board))
		return (0);

	// If Block is unpushable
	if (board[target_row][target_col] == BLOCK)
	{
		if (!is_pushable(path, target_row, target_col, board))
			return (0);
	}
	move_one_block(speed);
	board[*cur_row][*cur_col] = SPACE;
	*cur_row = target_row;
	*cur_col = target_col;
	board[*cur_row][*cur_col] = CAR;
	return (1);
}

int	is_walkable(int target_row, int target_col, int board[BOARD_SIZE][BOARD_SIZE])
{
	return (target_row >= 0 && target_row < BOARD_SIZE \
		&& target_col >= 0 && target_col < BOARD_SIZE && \
		(board[target_row][target_col] == SPACE || \
		board[target_row][target_col] == BLOCK));
}

// Returns 1 if push successful, 0 if block cannot be pushed
int	is_pushable(char direction, int target_row, int target_col, int board[BOARD_SIZE][BOARD_SIZE])
{
	int	push_row;
	int	push_col;

	push_row = target_row;
	push_col = target_col;
	if (direction == 'U')
		push_row = target_row - 1;
	else if (direction == 'D')
		push_row = target_row + 1;
	else if (direction == 'L')
		push_col = target_col - 1;
	else if (direction == 'R')
		push_col = target_col + 1;
	if (!is_walkable(push_row, push_col, board) || board[push_row][push_col] != SPACE)
    	return (0);
	board[push_row][push_col] = BLOCK;
	return (1);
}
