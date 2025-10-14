#include "RobotCar.h"

void	update_map(int board[BOARD_SIZE][BOARD_SIZE], int block_distance, int *direction, int cur_row, int cur_col)
{
	int	blocks_away;
	int	target_row = cur_row;
	int	target_col = cur_col;

	if (block_distance < 0)
		return ;
	if (block_distance <= BLOCK1) // ~1 block (20cm ±15)
		blocks_away = 1;
	else if (block_distance <= BLOCK2) // ~2 blocks (50cm ±12)
		blocks_away = 2;
	else if (block_distance <= BLOCK3) // ~3 blocks (75cm ±14)
		blocks_away = 3;
	else if (block_distance <= BLOCK4) // ~4 blocks (103cm ±13)
		blocks_away = 4;
	else if (block_distance <= BLOCK5) // ~5 blocks (130cm+)
		blocks_away = 5;
	else
		return ;

	if (*direction == DIR_UP)
		target_row = cur_row - blocks_away;
	else if (*direction == DIR_RIGHT)
		target_col = cur_col + blocks_away;
	else if (*direction == DIR_DOWN)
		target_row = cur_row + blocks_away;
	else if (*direction == DIR_LEFT)
		target_col = cur_col - blocks_away;

	// Check if target position is within board boundaries
	if (target_row >= 0 && target_row < BOARD_SIZE && 
		target_col >= 0 && target_col < BOARD_SIZE)
	{
		if (board[target_row][target_col] == SPACE)
			board[target_row][target_col] = UNK;
	}
}
