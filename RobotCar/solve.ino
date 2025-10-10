#include "RobotCar.h"

int	solve(char path_to_end[LIMIT_PATH], int start_row, int start_col, \
	int end_row, int end_col, int board[BOARD_SIZE][BOARD_SIZE])
{
	const int	directions[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
	const char	dir_chars[4] = { 'U', 'R', 'D', 'L' };
	int			visited[BOARD_SIZE][BOARD_SIZE] = {0};
	Node		parent[BOARD_SIZE][BOARD_SIZE];
	char		move_from_parent[BOARD_SIZE][BOARD_SIZE];
	Node		queue[BOARD_SIZE * BOARD_SIZE];
	int			front = 0;
	int			rear = 0;

	// Initialize BFS
	queue[rear++] = (Node){ start_row, start_col };
	visited[start_row][start_col] = 1;
	parent[start_row][start_col] = (Node){ -1, -1 };

	// --- BFS Loop ---
	while (front < rear) {
		Node cur = queue[front++];

		if (cur.row == end_row && cur.col == end_col)
			break;

		for (int i = 0; i < 4; i++) {
			int nr = cur.row + directions[i][0];
			int nc = cur.col + directions[i][1];

			if (nr < 0 || nr >= BOARD_SIZE || nc < 0 || nc >= BOARD_SIZE)
				continue;
			if (visited[nr][nc])
				continue;
			if (board[nr][nc] != SPACE && board[nr][nc] != BLOCK)
				continue;

			visited[nr][nc] = 1;
			parent[nr][nc] = cur;
			move_from_parent[nr][nc] = dir_chars[i];
			queue[rear++] = (Node){ nr, nc };

			if (rear >= BOARD_SIZE * BOARD_SIZE)
				break; // safety cap
		}
	}

	// --- Backtrack path ---
	Node	cur = { end_row, end_col };
	char	rev_path[LIMIT_PATH];
	int		len = 0;

	while (parent[cur.row][cur.col].row != -1 && len < LIMIT_PATH - 1) {
		rev_path[len++] = move_from_parent[cur.row][cur.col];
		cur = parent[cur.row][cur.col];
	}

	// If no path found
	if (len == 0) {
		path_to_end[0] = '\0';
		return (0);
	}

	// Reverse the path to correct order
	for (int i = 0; i < len; i++)
		path_to_end[i] = rev_path[len - 1 - i];
	path_to_end[len] = '\0';

	return (1);
}

int	can_move(int row, int col, int visited[BOARD_SIZE][BOARD_SIZE], int board[BOARD_SIZE][BOARD_SIZE])
{
	if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
		return (0);
	if ((board[row][col] != SPACE && board[row][col] != BLOCK) || visited[row][col])
		return (0);
	return (1);
}
