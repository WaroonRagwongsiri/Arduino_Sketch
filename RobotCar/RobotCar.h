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
# define TRIGGER_PIN 7
# define ECHO_PIN 6

// Buzzer
# define BUZZER 5

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
# define OBSTA 3
# define BLOCK 4

# define LEFT_CALIBRATE 1
# define RIGHT_CALIBRATE 1.5

// Color
# define WHITE_THRESHOLD 400

typedef struct s_ir
{
	int	up;
	int	ll;
	int	lm;
	int	rm;
	int	rr;
} t_ir;

// Log
void	log(int buz);
void	beep_buzzer(int buz);

// Motor
void	setup_motor(void);
void	set_zero(void);
void	forward(int speed);
void	shift_right(int speed);
void	shift_left(int speed);
void	pivot_right(int speed);
void	pivot_left(int speed);

// Movement
void	move_one_block(int speed);
void	line_following(int speed, t_ir ir);
void	turn_right(int speed);
void	turn_left(int speed);
void	align_on_line(int speed);

// Ultrasonic
long	read_ultrasonic(void);
int		to_cm(long micro_seconds);

// IR sensor
void	read_ir(t_ir *ir);
int 	isWhite(int sensor_value);

#endif