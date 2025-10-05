#include "RobotCar.h"

void	read_ir(t_ir *ir)
{
    ir->ir_up = analogRead(IR_UP);
    ir->ir_ll = analogRead(IR_LL);
    ir->ir_lm = analogRead(IR_LM);
    ir->ir_rm = analogRead(IR_RM);
    ir->ir_rr = analogRead(IR_RR);
}

int	isWhite(int sensor_value)
{
	return sensor_value > WHITE_THRESHOLD;
}
