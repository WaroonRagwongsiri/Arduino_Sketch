#include "RobotCar.h"

// 0 is space
// 1 is car
// 2 is UNK
// 3 is obstacle
// 4 is block
// static int	board[BOARD_SIZE][BOARD_SIZE] = {
// 	{0,		0,		0,		0,		0,		0},
// 	{0,		0,		0,		0,		0,		0},
// 	{0,		OBSTA,	BLOCK,	0,		0,		0},
// 	{0,		0,		0,		0,		OBSTA,	0},
// 	{0,		0,		0,		0,		0,		0},
// 	{CAR,	0,		0,		0,		0,		0},
// };
static int	board[BOARD_SIZE][BOARD_SIZE] = {
	{0,		0,		0,		0,		0,		0},
	{0,		0,		0,		0,		0,		0},
	{0,		0,		0,		0,		0,		0},
	{0,		0,		0,		0,		0,		0},
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
	// start_to_checkpoint(NORMAL_SPEED);
	// beep_buzzer(1);
	// beep_buzzer(1);
	// checkpoint_to_start(NORMAL_SPEED);
	// beep_buzzer(1);
	// beep_buzzer(1);
	turn_left(NORMAL_SPEED);
	delay(500);
}

void	loop(void)
{
}

void	start_to_checkpoint(int speed)
{
	char	s_to_c_path[LIMIT_PATH];
	int		i;

	update_map(board, read_ultrasonic(), &direction, cur_row, cur_col);
	log(0, board);
	while (cur_row != 0 || cur_col != BOARD_SIZE - 1)
	{
		memset(s_to_c_path, 0, sizeof(s_to_c_path));
		if (solve(s_to_c_path, cur_row, cur_col, 0, BOARD_SIZE - 1))
		{
			i = 0;
			while (s_to_c_path[i])
			{
				update_map(board, read_ultrasonic(), &direction, cur_row, cur_col);
				log(0, board);
				Serial.println(s_to_c_path);
				if (!walk(speed, s_to_c_path[i], &direction, board, &cur_row, &cur_col))
					break;
				i++;
			}
		}
		else
			break;
	}
}

void	checkpoint_to_start(int speed)
{
	char	c_to_s_path[LIMIT_PATH];
	int		i;

	update_map(board, read_ultrasonic(), &direction, cur_row, cur_col);
	log(0, board);
	while (cur_row != BOARD_SIZE - 1 || cur_col != 0)
	{
		memset(c_to_s_path, 0, sizeof(c_to_s_path));
		if (solve(c_to_s_path, cur_row, cur_col, BOARD_SIZE - 1, 0))
		{
			i = 0;
			while (c_to_s_path[i])
			{
				update_map(board, read_ultrasonic(), &direction, cur_row, cur_col);
				log(0, board);
				Serial.println(c_to_s_path);
				if (!walk(speed, c_to_s_path[i], &direction, board, &cur_row, &cur_col))
					break;
				i++;
			}
		}
		else
			break;
	}
}
