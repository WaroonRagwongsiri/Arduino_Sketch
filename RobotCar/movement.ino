/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.ino                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:17:28 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/09/30 12:11:07 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotCar.h"


// Set left and right motor to low;
void	set_zero(void)
{
	digitalWrite(INA, LOW);
	digitalWrite(INB, LOW);
	digitalWrite(INC, LOW);
	digitalWrite(IND, LOW);
	analogWrite(ENA, 0);
	analogWrite(ENB, 0);
}

// Move forward for a X second;
void	move_forward(int speed, int time_ms)
{
	int	l_speed;
	int	r_speed;

	l_speed = speed * LEFT_CALIBRATE;
	r_speed = speed * RIGHT_CALIBRATE;
	analogWrite(ENA, speed);
	analogWrite(ENB, speed);
	digitalWrite(INA, HIGH);
	digitalWrite(INB, LOW);
	digitalWrite(INC, HIGH);
	digitalWrite(IND, LOW);
	delay(time_ms);
	set_zero();
}


// Turn Left
void	turn_left(int speed, int time_ms)
{
	int	l_speed;
	int	r_speed;

	l_speed = speed * LEFT_CALIBRATE;
	r_speed = speed * RIGHT_CALIBRATE;
	analogWrite(ENA, speed);
	analogWrite(ENB, speed);
	digitalWrite(INA, LOW);
	digitalWrite(INB, LOW);
	digitalWrite(INC, HIGH);
	digitalWrite(IND, LOW);
	delay(time_ms);
	set_zero();
}

// Turn Right
void	turn_right(int speed, int time_ms)
{
	int	l_speed;
	int	r_speed;

	l_speed = speed * LEFT_CALIBRATE;
	r_speed = speed * RIGHT_CALIBRATE;
	analogWrite(ENA, speed);
	analogWrite(ENB, speed);
	digitalWrite(INA, HIGH);
	digitalWrite(INB, LOW);
	digitalWrite(INC, LOW);
	digitalWrite(IND, LOW);
	delay(time_ms);
	set_zero();
}
