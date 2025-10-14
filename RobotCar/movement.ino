#include "RobotCar.h"

// Walk 1 block
void	move_one_block(int speed)
{
	t_ir	ir;
	unsigned long startTime;

	// Check if we're starting on an intersection
	read_ir(&ir);
	if (!is_white(ir.ll) || !is_white(ir.rr))
		forward_time(speed, WALK_TIME);

	// Walk until it white
	read_ir(&ir);
	while (!is_white(ir.ll) || !is_white(ir.rr))
	{
		read_ir(&ir);
		line_following(speed, ir);
	}
	set_zero();

	// Walk until it black
	read_ir(&ir);
	while (is_white(ir.ll) && is_white(ir.rr))
	{
		read_ir(&ir);
		line_following(speed, ir);
	}
	set_zero();

	// Align head
	read_ir(&ir);
	while (!is_white(ir.ll) && !is_white(ir.rr))
	{
		read_ir(&ir);
		if (is_white(ir.ll) && !is_white(ir.rr))
			shift_right(speed);
		else if (!is_white(ir.ll) && is_white(ir.rr))
			shift_left(speed);
		else
			forward(speed);
	}
	set_zero();
}

// Enhanced line following with more sensor combinations
void	line_following(int speed, t_ir ir)
{
	if (!is_white(ir.lm) && !is_white(ir.rm))
		forward(speed);
	else if (is_white(ir.lm) && !is_white(ir.rm) && is_white(ir.ll))
		shift_right(speed * 0.7);
	else if (!is_white(ir.lm) && is_white(ir.rm) && is_white(ir.rr))
		shift_left(speed * 0.7);
	else if (is_white(ir.lm) && !is_white(ir.rm))
		shift_right(speed * 0.9);
	else if (!is_white(ir.lm) && is_white(ir.rm))
		shift_left(speed * 0.9);
	else if (is_white(ir.lm) && is_white(ir.rm))
	{
		if (!is_white(ir.ll) && is_white(ir.rr))
			shift_left(speed * 0.6);
		else if (is_white(ir.ll) && !is_white(ir.rr))
			shift_right(speed * 0.6);
		else
			forward(speed * 0.8);
	}
	else
		forward(speed * 0.8);
}

// Align robot centered on the black line
void	align_on_line(int speed)
{
	t_ir	ir;

	read_ir(&ir);
	while (!is_white(ir.lm) || !is_white(ir.rm))
	{
		read_ir(&ir);
		
		if (is_white(ir.lm) && !is_white(ir.rm))
			shift_right(speed);
		else if (!is_white(ir.lm) && is_white(ir.rm))
			shift_left(speed);
		else
			forward(speed);
	}
	set_zero();
}

// Turn left 90 degree
void turn_left(int speed)
{
	t_ir				ir;
	unsigned long		startTime;
		
	// If starting on intersection, use line_following to move forward first
	read_ir(&ir);
	if (!is_white(ir.ll) && !is_white(ir.rr))
	{
		read_ir(&ir);
		line_following(speed, ir);
		while (!is_white(ir.ll) || !is_white(ir.rr))
		{
			read_ir(&ir);
			line_following(speed, ir);
		}
		set_zero();
	}

	// Walk a bit
	forward_time(speed, TURN_WALK);

	// Turn left a little
	startTime = millis();
	while (millis() - startTime < TURN_TIME)
	{
		read_ir(&ir);
		pivot_left(speed * 0.8);
	}
	set_zero();

	// Pivot until it leaves black (both middle sensors on white)
	read_ir(&ir);
	while (!is_white(ir.lm) || !is_white(ir.rm))
	{
		read_ir(&ir);
		pivot_left(speed * 0.8);
	}
	set_zero();

	// Pivot until it finds the perpendicular black line
	read_ir(&ir);
	while (is_white(ir.lm) && is_white(ir.rm))
	{
		read_ir(&ir);
		pivot_left(speed * 0.8);
	}
	set_zero();
}

// Turn right 90 degree
void turn_right(int speed)
{
	t_ir			ir;
	unsigned long	startTime;
		
	// If starting on intersection, use line_following to move forward first
	read_ir(&ir);
	if (!is_white(ir.ll) && !is_white(ir.rr))
	{
		read_ir(&ir);
		line_following(speed, ir);
		while (!is_white(ir.ll) || !is_white(ir.rr))
		{
			read_ir(&ir);
			line_following(speed, ir);
		}
		set_zero();
	}

	// Walk a bit
	forward_time(speed, TURN_WALK);

	// Turn right a little
	startTime = millis();
	while (millis() - startTime < TURN_TIME)
	{
		read_ir(&ir);
		pivot_right(speed * 0.8);
	}
	set_zero();

	// Pivot until it leaves black (both middle sensors on white)
	read_ir(&ir);
	while (!is_white(ir.lm) || !is_white(ir.rm))
	{
		read_ir(&ir);
		pivot_right(speed * 0.8);
	}
	set_zero();

	// Pivot until it finds the perpendicular black line
	read_ir(&ir);
	while (is_white(ir.lm) && is_white(ir.rm))
	{
		read_ir(&ir);
		pivot_right(speed * 0.8);
	}
	set_zero();
}

// Walk backward until black line is detected
void	walk_back_til_black(int speed)
{
	t_ir	ir;

	// Walk back till one of it is black
	read_ir(&ir);
	while (is_white(ir.ll) && is_white(ir.rr))
	{
		read_ir(&ir);
		line_following_backward(speed, ir);
	}
	set_zero();
}

// Line following but backward
void	line_following_backward(int speed, t_ir ir)
{
	if (!is_white(ir.lm) && !is_white(ir.rm))
		backward(speed);
	else if (is_white(ir.lm) && !is_white(ir.rm))
		shift_left_backward(speed);
	else if (!is_white(ir.lm) && is_white(ir.rm))
		shift_right_backward(speed);
	else
		backward(speed);
}

// Turn 180 degree
void	turn_around(int speed)
{
	turn_right(speed);
	turn_right(speed);
	set_zero();
}

// Align backward
void	align_backward(int speed)
{
	t_ir	ir;

	read_ir(&ir);

	while (!is_white(ir.ll) || !is_white(ir.lm) || !is_white(ir.rm) || !is_white(ir.rr))
	{
		read_ir(&ir);

		if (!is_white(ir.lm) && !is_white(ir.rm))
		{
			if (is_white(ir.ll) && !is_white(ir.rr))
				shift_left_backward(speed);
			else if (!is_white(ir.ll) && is_white(ir.rr))
				shift_right_backward(speed);
			else
				backward(speed);
		}
		else if (!is_white(ir.lm) && is_white(ir.rm))
			shift_right_backward(speed);
		else if (is_white(ir.lm) && !is_white(ir.rm))
			shift_left_backward(speed);
		else
			line_following_backward(speed, ir);
	}
	set_zero();
}

// Back for X seconds
void	backward_time(int speed, int time)
{
	t_ir			ir;
	unsigned long	time_start;

	time_start = millis();
	while (millis() - time_start < time)
	{
		read_ir(&ir);
		line_following_backward(speed, ir);
	}
	set_zero();
}

// Forward for X seconds
void	forward_time(int speed, int time)
{
	t_ir			ir;
	unsigned long	time_start;

	time_start = millis();
	while (millis() - time_start < time)
	{
		read_ir(&ir);
		line_following(speed, ir);
	}
	set_zero();
}
