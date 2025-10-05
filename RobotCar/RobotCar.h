/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotCar.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:57:18 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/09/30 12:27:18 by waroonwork@      ###   ########.fr       */
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

# define LEFT_CALIBRATE 0.78
# define RIGHT_CALIBRATE 1

# define BOARD_SIZE 6

// Setup
void	setup_motor(void);

// Movement
void	set_zero(void);
void	move_forward(int speed, int time_ms);
void	turn_left(int speed, int time_ms);
void	turn_right(int speed, int time_ms);

#endif