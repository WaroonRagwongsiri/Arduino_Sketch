/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotCar.ino                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:58:03 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/09/30 22:23:39 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotCar.h"

static int	board[BOARD_SIZE][BOARD_SIZE] = {
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0},
};

void	setup(void)
{
	setup_motor();
}

void	loop(void)
{
	start_to_check();
	check_to_start();
}

void	start_to_check(void)
{
	
}

void	check_to_start(void)
{
	
}
