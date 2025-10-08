#include "RobotCar.h"

int	solve(char path_to_end[LIMIT_PATH], int start_row, int start_col, int end_row, int end_col)
{
	int	visited[BOARD_SIZE][BOARD_SIZE] = {0};

	if (solve_helper(path_to_end, start_row, start_col, end_row, end_col, visited, 0))
		return 1;

	path_to_end[0] = '\0';
	return 0;
}

int	solve_helper(char path[LIMIT_PATH], int row, int col, int end_row, int end_col, int visited[BOARD_SIZE][BOARD_SIZE], int depth)
{
	const int	directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	const char	dir_chars[4] = {'U', 'R', 'D', 'L'};
	int			new_row;
	int			new_col;
	int			i;

	if (row == end_row && col == end_col)
	{
		path[depth] = '\0';
		return 1;
	}
	visited[row][col] = 1;
	i = -1;
	while (++i < 4)
	{
		new_row = row + directions[i][0];
		new_col = col + directions[i][1];

		if (new_row >= 0 && new_row < BOARD_SIZE && 
			new_col >= 0 && new_col < BOARD_SIZE &&
			(board[new_row][new_col] == SPACE || board[new_row][new_col] == UNK) && 
			!visited[new_row][new_col])
		{
			path[depth] = dir_chars[i];
			if (solve_helper(path, new_row, new_col, end_row, end_col, visited, depth + 1))
				return 1;
		}
	}
	visited[row][col] = 0;
	return 0;
}
