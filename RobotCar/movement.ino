#include "RobotCar.h"

// Walk 1 block
void	move_one_block(int speed)
{
	t_ir	ir;

	// Walk until it white
	read_ir(&ir);
	while (!isWhite(ir.ir_ll) || !isWhite(ir.ir_rr))
	{
		read_ir(&ir);
		line_following(speed, ir);
	}
	set_zero();
	// Walk until it black
	read_ir(&ir);
	while (isWhite(ir.ir_ll) && isWhite(ir.ir_rr))
	{
		read_ir(&ir);
		line_following(speed, ir);
	}
	set_zero();
	// Allign head
	read_ir(&ir);
	while ( !isWhite(ir.ir_ll) && !isWhite(ir.ir_rr))
	{	
		read_ir(&ir);
		if (isWhite(ir.ir_ll) && !isWhite(ir.ir_rr))
			shift_right(speed);
		else if (!isWhite(ir.ir_ll) && isWhite(ir.ir_rr))
			shift_left(speed);
		else
			forward(speed);
	}
	set_zero();
}

// Tries to allign on black line
void	line_following(int speed, t_ir ir)
{
	if (!isWhite(ir.ir_lm) && !isWhite(ir.ir_rm))
		forward(speed);
	else if (isWhite(ir.ir_lm) && !isWhite(ir.ir_rm))
		shift_right(speed);
	else if (!isWhite(ir.ir_lm) && isWhite(ir.ir_rm))
		shift_left(speed);
	else
		forward(speed);
}

// Turn right
void	turn_right(int speed)
{
	t_ir	ir;

	// Shift until it got out of black
	read_ir(&ir);
	while (!isWhite(ir.ir_ll) || !isWhite(ir.ir_rr))
	{
		read_ir(&ir);
		shift_right(speed);
	}
	// Shift until it back to blakc
	read_ir(&ir);
	while (isWhite(ir.ir_ll) || isWhite(ir.ir_rr))
	{
		read_ir(&ir);
		shift_right(speed);
	}
	// Allign head
	read_ir(&ir);
	while (!isWhite(ir.ir_ll) && !isWhite(ir.ir_rr))
	{
		read_ir(&ir);
		if (isWhite(ir.ir_ll) && !isWhite(ir.ir_rr))
			shift_right(speed);
		else if (!isWhite(ir.ir_ll) && isWhite(ir.ir_rr))
			shift_left(speed);
	}
	set_zero();
}

// Turn left
void	turn_left(int speed)
{
	t_ir	ir;

	// Shift until it got out of black
	read_ir(&ir);
	while (!isWhite(ir.ir_ll) || !isWhite(ir.ir_rr))
	{
		read_ir(&ir);
		shift_left(speed);
	}
	// Shift until it back to blakc
	read_ir(&ir);
	while (isWhite(ir.ir_ll) || isWhite(ir.ir_rr))
	{
		read_ir(&ir);
		shift_left(speed);
	}
	// Allign head
	read_ir(&ir);
	while (!isWhite(ir.ir_ll) && !isWhite(ir.ir_rr))
	{
		read_ir(&ir);
		if (isWhite(ir.ir_ll) && !isWhite(ir.ir_rr))
			shift_right(speed);
		else if (!isWhite(ir.ir_ll) && isWhite(ir.ir_rr))
			shift_left(speed);
	}
	set_zero();
}
