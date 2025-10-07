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
void	line_following(int speed, t_ir ir)
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

// Align robot centered on the black line
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
			forward(speed);
		}
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
	if (!isWhite(ir.ll) && !isWhite(ir.rr))
	{
		read_ir(&ir);
		line_following(speed, ir);
		while (!isWhite(ir.ll) || !isWhite(ir.rr))
		{
			read_ir(&ir);
			line_following(speed, ir);
		}
		set_zero();
		delay(100);
	}

	// Move forward using line_following for 500ms to clear the intersection
	startTime = millis();
	while (millis() - startTime < 500)
	{
		read_ir(&ir);
		line_following(speed, ir);
	}
	set_zero();

	// Pivot until it leaves black (both middle sensors on white)
	read_ir(&ir);
	while (!isWhite(ir.lm) || !isWhite(ir.rm))
	{
		read_ir(&ir);
		pivot_left(speed);
	}
	set_zero();

	// Pivot until it finds the perpendicular black line
	read_ir(&ir);
	while (isWhite(ir.lm) && isWhite(ir.rm))
	{
		read_ir(&ir);
		pivot_left(speed);
	}
	set_zero();

	// Align on black
	align_on_line(speed);
	set_zero();
}

// Turn right 90 degree
void turn_right(int speed)
{
	t_ir			ir;
	unsigned long	startTime;
		
	// If starting on intersection, use line_following to move forward first
	read_ir(&ir);
	if (!isWhite(ir.ll) && !isWhite(ir.rr))
	{
		read_ir(&ir);
		line_following(speed, ir);
		while (!isWhite(ir.ll) || !isWhite(ir.rr))
		{
			read_ir(&ir);
			line_following(speed, ir);
		}
		set_zero();
		delay(100);
	}

	// Move forward using line_following for 500ms to clear the intersection
	startTime = millis();
	while (millis() - startTime < 500)
	{
		read_ir(&ir);
		line_following(speed, ir);
	}
	set_zero();

	// Pivot until it leaves black (both middle sensors on white)
	read_ir(&ir);
	while (!isWhite(ir.lm) || !isWhite(ir.rm))
	{
		read_ir(&ir);
		pivot_right(speed);
	}
	set_zero();

	// Pivot until it finds the perpendicular black line
	read_ir(&ir);
	while (isWhite(ir.lm) && isWhite(ir.rm))
	{
		read_ir(&ir);
		pivot_right(speed);
	}
	set_zero();

	// Align on black
	align_on_line(speed);
	set_zero();
}
