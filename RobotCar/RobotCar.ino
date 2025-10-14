#include "RobotCar.h"

// 0 is space
// 1 is car
// 2 is UNK
// 3 is block
static int	board[BOARD_SIZE][BOARD_SIZE] = {
	{0,		0,		0,		0,		0,		0},
	{0,		0,		0,		0,		0,		0},
	{0,		UNK,	BLOCK,	0,		0,		0},
	{0,		0,		0,		0,		UNK,	0},
	{0,		0,		0,		0,		0,		0},
	{CAR,	0,		0,		0,		0,		0},
};

static int	direction = DIR_UP;

static int	cur_row = 5;
static int	cur_col = 0;

void	setup(void)
{
	setup_motor();
	pinMode(TRIGGER_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
	pinMode(BUZZER, OUTPUT);
	Serial.begin(9600);
	Serial.flush();
	digitalWrite(BUZZER, HIGH);

	start_to_checkpoint(NORMAL_SPEED);
	checkpoint_to_start(NORMAL_SPEED);
	// push_a_block(NORMAL_SPEED);
	// checkpoint_to_start(NORMAL_SPEED);
}

void	loop(void)
{
	log(0, board);
	// car_to_point(NORMAL_SPEED, 5, 1);
	// push_walk('U');
	// car_to_point(NORMAL_SPEED, 5, 2);
	// car_to_point(NORMAL_SPEED, 5, 0);
	delay(1000);
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
		if (solve(walk_path, cur_row, cur_col, end_row, end_col, board))
		{
			i = 0;
			while (walk_path[i])
			{
				// log(0, board);
				// Serial.print("Walk Path : ");
				// Serial.println(walk_path);
				// Serial.print("Path going to take : ");
				// Serial.println(walk_path[i]);
				if (!walk(speed, walk_path[i], &direction, board, &cur_row, &cur_col))
					break;
				// log(0, board);
				// Serial.print("Walk Path : ");
				// Serial.println(walk_path);
				// Serial.print("Path taken : ");
				// Serial.println(walk_path[i]);
				i++;
			}
		}
		else
			break;
	}
}

// Stop 3 secs and beep 2 times
void	start_to_checkpoint(int speed)
{
	beep_buzzer();
	// Serial.println("Start");
	car_to_point(speed, 0, BOARD_SIZE - 1);
	// Serial.println("Check point");
	delay(3000);
	beep_buzzer();
	beep_buzzer();
}

// Stop and beep 3 times
void	checkpoint_to_start(int speed)
{
	// Serial.println("Check point 2");
	car_to_point(speed, BOARD_SIZE - 1, 0);
	// Serial.println("Start 2");
	delay(3000);
	beep_buzzer();
	beep_buzzer();
	beep_buzzer();
}

void	push_a_block(int speed)
{
	// First push
	car_to_point(WALK_SPEED, 1, 2);
	push_walk('D');

	// Second push
	car_to_point(WALK_SPEED, 3, 1);
	push_walk('R');

	// Third push
	car_to_point(WALK_SPEED, 4, 3);
	walk(PUSH_SPEED, 'U', &direction, board, &cur_row, &cur_col);
	push_walk('U');

	// Forth push
	car_to_point(WALK_SPEED, 1, 2);
	push_walk('R');
}

void	push_walk(char path)
{
	face_direction(WALK_SPEED, path, &direction);
	walk(PUSH_SPEED, path, &direction, board, &cur_row, &cur_col);
	delay(200);
	forward_time(PUSH_SPEED, PUSH_TIME);
	delay(200);
	walk_back_til_black(80);
	delay(200);
	move_one_block(WALK_SPEED);
	delay(200);
	forward_time(WALK_SPEED, 300);
	delay(200);
}
