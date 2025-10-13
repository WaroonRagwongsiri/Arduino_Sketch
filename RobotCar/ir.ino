#include "RobotCar.h"

void	read_ir(t_ir *ir)
{
	ir->up = analogRead(IR_UP);
	ir->ll = analogRead(IR_LL);
	ir->lm = analogRead(IR_LM);
	ir->rm = analogRead(IR_RM);
	ir->rr = analogRead(IR_RR);
}

int	is_white(int sensor_value)
{
	return (sensor_value > WHITE_THRESHOLD);
}
