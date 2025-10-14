/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotCar.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:57:18 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/10/05 16:47:57 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOT_CAR
# define ROBOT_CAR

// PWM Motor A (Left Motor)
# define ENA 9
# define INA 8
# define INB 11

// PWM Motor B (Right Motor)
# define ENB 10
# define INC 12
# define IND 13

// Ultrasonic
# define TRIGGER_PIN 6
# define ECHO_PIN 5

// Buzzer
# define BUZZER 4

// IR
# define IR_LL A5
# define IR_LM A4
# define IR_UP A3
# define IR_RM A2
# define IR_RR A1

// Board
# define BOARD_SIZE 6
# define SPACE 0
# define CAR 1
# define UNK 2
# define BLOCK 3

# define LEFT_CALIBRATE 1
# define RIGHT_CALIBRATE 1

// Color
# define WHITE_THRESHOLD 450

// Direction
# define DIR_UP 0
# define DIR_DOWN 1
# define DIR_LEFT 2
# define DIR_RIGHT 3

# define LIMIT_PATH 100

# define NORMAL_SPEED 130

// Turn Time
# define TURN_WALK 100
# define TURN_TIME 180
# define WALK_TIME 150

// Walk speed (Push a block)
# define WALK_SPEED 130
# define PUSH_SPEED 160

// Push Time
# define PUSH_TIME 850

// Block Distance
# define BLOCK1 35
# define BLOCK2 62
# define BLOCK3 89
# define BLOCK4 116
# define BLOCK5 145

typedef struct s_ir
{
	int	up;
	int	ll;
	int	lm;
	int	rm;
	int	rr;
} t_ir;

// Log
void	log(int buz, int board[BOARD_SIZE][BOARD_SIZE]);
void	beep_buzzer(void);
void	print_board(int board[BOARD_SIZE][BOARD_SIZE]);

// Motor
void	setup_motor(void);
void	set_zero(void);
void	forward(int speed);
void	shift_right(int speed);
void	shift_left(int speed);
void	pivot_right(int speed);
void	pivot_left(int speed);
void	backward(int speed);
void	shift_right_backward(int speed);
void	shift_left_backward(int speed);

// Movement
void	move_one_block(int speed);
void	line_following(int speed, t_ir ir);
void	turn_right(int speed);
void	turn_left(int speed);
void	align_on_line(int speed);
void	walk_back_til_black(int speed);
void	line_following_backward(int speed, t_ir ir);
void	turn_around(int speed);
void	backward_time(int speed, int time);
void	forward_time(int speed, int time);

// Ultrasonic
long	read_ultrasonic(void);
int		to_cm(long micro_seconds);

// IR sensor
void	read_ir(t_ir *ir);
int 	is_white(int sensor_value);

// Walk Direction
void	face_direction(int speed, char path, int *direction);
void	face_up(int speed, int *direction);
void	face_down(int speed, int *direction);
void	face_left(int speed, int *direction);
void	face_right(int speed, int *direction);
int		walk(int speed, char path, int *direction, int board[BOARD_SIZE][BOARD_SIZE], int *cur_row, int *cur_col);
int		is_walkable(int target_row, int target_col, int board[BOARD_SIZE][BOARD_SIZE]);
int		is_pushable(char direction, int target_row, int target_col, int board[BOARD_SIZE][BOARD_SIZE]);

// Map
void	update_map(int board[BOARD_SIZE][BOARD_SIZE], int block_distance, int *direction, int cur_row, int cur_col);

typedef struct {
	int	row;
	int	col;
} Node;

// Solver
int	solve(char path_to_end[LIMIT_PATH], int start_row, int start_col, \
		int end_row, int end_col, int board[BOARD_SIZE][BOARD_SIZE]);
int	can_move(int row, int col, int visited[BOARD_SIZE][BOARD_SIZE], int board[BOARD_SIZE][BOARD_SIZE]);

// Mandatory
void	car_to_point(int speed, int end_row, int end_col);
void	start_to_checkpoint(int speed);
void	checkpoint_to_start(int speed);
void	push_a_block(int speed);
void	push_walk(char path);

// Ram Utility
int		free_ram(void);

#endif