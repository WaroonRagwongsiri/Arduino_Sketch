#include "RobotCar.h"

// 0 is space
// 1 is car
// 2 is UNK
// 3 is obstacle
// 4 is block
static int	board[BOARD_SIZE][BOARD_SIZE] = {
	{0,		0,		0,		0,		0,		0},
	{0,		0,		0,		0,		0,		0},
	{0,		OBSTA,	BLOCK,	0,		0,		0},
	{0,		0,		0,		0,		OBSTA,	0},
	{0,		0,		0,		0,		0,		0},
	{CAR,	0,		0,		0,		0,		0},
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
	start_to_checkpoint();
}

void	loop(void)
{
	log(0, board);
}

void	start_to_checkpoint(void)
{
	char	s_to_c_path[LIMIT_PATH];
	int		i;

	update_map(board, read_ultrasonic(), &direction, cur_row, cur_col);
	while (cur_row != 0 || cur_col != BOARD_SIZE - 1)
	{
		memset(s_to_c_path, 0, sizeof(s_to_c_path));
		if (solve(s_to_c_path, cur_row, cur_col, 0, BOARD_SIZE - 1))
		{
			Serial.println(s_to_c_path);
			i = 0;
			while (s_to_c_path[i])
			{
				if (!walk(100, s_to_c_path[i], &direction, board, &cur_row, &cur_col))
					break;
				i++;
			}
		}
		else
			break;
	}
}

void	checkpoint_to_start(void)
{
}
