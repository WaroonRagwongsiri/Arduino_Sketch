/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motor.ino                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:26:47 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/09/30 12:27:01 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotCar.h"

void	setup_motor(void)
{
	// Set up Left Motor
	pinMode(ENA, OUTPUT);
	pinMode(INA, OUTPUT);
	pinMode(INB, OUTPUT);

	// Set up right Motor
	pinMode(ENB, OUTPUT);
	pinMode(INC, OUTPUT);
	pinMode(IND, OUTPUT);
}
