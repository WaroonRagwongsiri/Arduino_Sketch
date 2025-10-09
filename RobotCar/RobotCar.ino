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
	// beep_buzzer();
	// delay(500);
	start_to_checkpoint(NORMAL_SPEED);
	// delay(500);
	checkpoint_to_start(NORMAL_SPEED);
	// delay(500);
}

void	loop(void)
{
	log(0, board);
	delay(1000);
	// walk(NORMAL_SPEED, 'U', &direction, board, &cur_row, &cur_col);
	// delay(500);
	// walk(NORMAL_SPEED, 'R', &direction, board, &cur_row, &cur_col);
	// delay(500);
	// walk(NORMAL_SPEED, 'D', &direction, board, &cur_row, &cur_col);
	// delay(500);
	// walk(NORMAL_SPEED, 'L', &direction, board, &cur_row, &cur_col);
	// delay(500);
	// delay(500);
}

void	car_to_point(int speed, int end_row, int end_col)
{
	char	walk_path[LIMIT_PATH];
	int		i;

	update_map(board, read_ultrasonic(), &direction, cur_row, cur_col);
	log(0, board);
	while (cur_row != end_row || cur_col != end_col)
	{
		memset(walk_path, 0, sizeof(walk_path));
		if (solve(walk_path, cur_row, cur_col, end_row, end_col))
		{
			i = 0;
			while (walk_path[i])
			{
				update_map(board, read_ultrasonic(), &direction, cur_row, cur_col);
				log(0, board);
				Serial.println(walk_path);
				if (!walk(speed, walk_path[i], &direction, board, &cur_row, &cur_col))
					break;
				i++;
			}
		}
		else
			break;
	}
}

void	start_to_checkpoint(int speed)
{
	car_to_point(speed, 0, BOARD_SIZE - 1);
	beep_buzzer();
	beep_buzzer();
}

void	checkpoint_to_start(int speed)
{
	car_to_point(speed, BOARD_SIZE - 1, 0);
	beep_buzzer();
	beep_buzzer();
}

void	push_a_block(int speed)
{
	cat_to_point(speed, 3, 2);
	walk(speed, 'U', &direction, board, &cur_row, &cur_col);
	cat_to_point(speed, 1, 1);
	walk(speed, 'R', &direction, board, &cur_row, &cur_col);
	walk(speed, 'R', &direction, board, &cur_row, &cur_col);
}
