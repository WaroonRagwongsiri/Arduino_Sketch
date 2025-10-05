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
# define ENA 10
# define INA 9
# define INB 8

// PWM Motor B (Right Motor)
# define ENB 6
# define INC 5
# define IND 4

# define LEFT_CALIBRATE 1
# define RIGHT_CALIBRATE 1

// Ultrasonic
# define TRIGGER_PIN 12
# define ECHO_PIN 11

// IR
# define IR_LL A0
# define IR_LM A1
# define IR_RR A2
# define IR_RM A3
# define IR_UP A4

// Piezo (buzzer)
# define PIEZO 13

// Board
# define BOARD_SIZE 6
# define SPACE 0
# define CAR 1
# define UNK 2
# define OBSTA 3
# define BLOCK 4

// Color
# define WHITE_THRESHOLD 100

typedef struct s_ir
{
	int	ir_up;
	int	ir_ll;
	int	ir_lm;
	int	ir_rm;
	int	ir_rr;
} t_ir;

// Motor
void	setup_motor(void);
void	set_zero(void);
void	forward(int speed);
void	shift_right(int speed);

// Movement
void	move_forward(int speed, int time_ms);

// Ultrasonic
long	read_ultrasonic(void);
int		to_cm(long micro_seconds);

// IR sensor
void	read_ir(t_ir *ir);
int 	isWhite(int sensor_value);

#endif