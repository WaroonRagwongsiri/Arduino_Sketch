#include "RobotCar.h"

// Walk 1 block
void	move_one_block(int speed)
{
	t_ir	ir;

	// Check if we're starting on an intersection
	read_ir(&ir);
	if (!isWhite(ir.ll) && !isWhite(ir.rr))
	{
		// We're on intersection, use line_following until we leave it
		read_ir(&ir);
		line_following(speed, ir);
		while (!isWhite(ir.ll) || !isWhite(ir.rr))
		{
			read_ir(&ir);
			line_following(speed, ir);
		}
		set_zero();
	}
	// Walk until it white (should already be true from above)
	read_ir(&ir);
	while (!isWhite(ir.ll) || !isWhite(ir.rr))
	{
		read_ir(&ir);
		line_following(speed, ir);
	}
	set_zero();
	
	// Walk until it black  
	read_ir(&ir);
	while (isWhite(ir.ll) && isWhite(ir.rr))
	{
		read_ir(&ir);
		line_following(speed, ir);
	}
	set_zero();
	
	// Align head
	read_ir(&ir);
	while (!isWhite(ir.ll) && !isWhite(ir.rr))
	{	
		read_ir(&ir);
		if (isWhite(ir.ll) && !isWhite(ir.rr))
			shift_right(speed);
		else if (!isWhite(ir.ll) && isWhite(ir.rr))
			shift_left(speed);
		else
			forward(speed);
	}
	set_zero();
}

// Tries to allign on black line
void	line_following(int speed, t_ir	ir)
{
	if (!isWhite(ir.lm) && !isWhite(ir.rm))
		forward(speed);
	else if (isWhite(ir.lm) && !isWhite(ir.rm))
		shift_right(speed);
	else if (!isWhite(ir.lm) && isWhite(ir.rm))
		shift_left(speed);
	else
		forward(speed);
}

// Align
void	align_on_line(int speed)
{
	t_ir	ir;

	read_ir(&ir);
	while (!isWhite(ir.lm) || !isWhite(ir.rm))
	{
		read_ir(&ir);
		
		if (isWhite(ir.lm) && !isWhite(ir.rm))
		{
			// Left sensor on white, right on black - shift right
			shift_right(speed);
		}
		else if (!isWhite(ir.lm) && isWhite(ir.rm))
		{
			// Right sensor on white, left on black - shift left
			shift_left(speed);
		}
		else
		{
			// Both sensors same state - move forward slowly
			line_following(speed, ir);
		}
	}
	set_zero();
}

// Turn left 90 degree - SENSOR-ONLY VERSION
void	turn_left(int speed)
{
	t_ir	ir;
	unsigned long startTime;
		
	// If starting on intersection, move forward first
	read_ir(&ir);
	if (!isWhite(ir.ll) && !isWhite(ir.rr))
	{
		startTime = millis();
		while (millis() - startTime < TURN_WALK)
		{
			read_ir(&ir);
			line_following(speed, ir);
		}
		set_zero();
		delay(100);
	}

	// Pivot black -> white
	read_ir(&ir);
	while (!isWhite(ir.lm) || !isWhite(ir.rm))
	{
		read_ir(&ir);
		pivot_left(speed);
	}
	set_zero();

	// Pivot white -> left
	read_ir(&ir);
	while (isWhite(ir.lm) || isWhite(ir.rm))
	{
		read_ir(&ir);
		pivot_left(speed);
	}

	// Align back to intersect
	align_backward(speed);
	set_zero();
}

// Turn right 90 degree - SENSOR-ONLY VERSION
void	turn_right(int speed)
{
	t_ir	ir;
	unsigned long startTime;
		
	// If starting on intersection, move forward first
	read_ir(&ir);
	if (!isWhite(ir.ll) && !isWhite(ir.rr))
	{
		startTime = millis();
		while (millis() - startTime < TURN_WALK)
		{
			read_ir(&ir);
			line_following(speed, ir);
		}
		set_zero();
		delay(100);
	}

	// Pivot black -> white
	read_ir(&ir);
	while (!isWhite(ir.lm) || !isWhite(ir.rm))
	{
		read_ir(&ir);
		pivot_right(speed);
	}

	// Pivot white -> black
	read_ir(&ir);
	while (isWhite(ir.lm) || isWhite(ir.rm))
	{
		read_ir(&ir);
		pivot_right(speed);
	}
		
	// Align back to intersect
	align_backward(speed);
	set_zero();
}

// Walk backward until black line is detected
void	walk_back_til_black(int speed)
{
	t_ir	ir;

	read_ir(&ir);
	while (isWhite(ir.ll) && isWhite(ir.rr))
	{
		read_ir(&ir);
		line_following_backward(speed, ir);
	}
	set_zero();
}

// Line following but backward
void	line_following_backward(int speed, t_ir ir)
{
	if (!isWhite(ir.lm) && !isWhite(ir.rm))
		backward(speed);
	else if (isWhite(ir.lm) && !isWhite(ir.rm))
		shift_right_backward(speed);
	else if (!isWhite(ir.lm) && isWhite(ir.rm))
		shift_left_backward(speed);
	else
		backward(speed);
}

// Turn around 180 degree - SENSOR-ONLY VERSION
void	turn_around(int speed)
{
	turn_left(speed);
	delay(200); // Small pause between turns
	turn_left(speed);
}

// Align backward
void	align_backward(int speed)
{
	t_ir	ir;

	read_ir(&ir);

	while (!isWhite(ir.ll) || !isWhite(ir.lm) || !isWhite(ir.rm) || !isWhite(ir.rr))
	{
		read_ir(&ir);
		line_following_backward(speed, ir);
	}
	set_zero();
}
