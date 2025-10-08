#include "RobotCar.h"

void	log(int buz, int board[BOARD_SIZE][BOARD_SIZE])
{
	t_ir	ir;

	digitalWrite(BUZZER, HIGH);
	Serial.println("========== Ultrasonic ==========");
	Serial.print("Ultrasonic : ");
	Serial.println(read_ultrasonic());
	Serial.println("");
	read_ir(&ir);
	Serial.println("========== IR ==========");
	Serial.print("LL : ");
	Serial.println(ir.ll);
	Serial.print("LM : ");
	Serial.println(ir.lm);
	Serial.print("UP : ");
	Serial.println(ir.up);
	Serial.print("RM : ");
	Serial.println(ir.rm);
	Serial.print("RR : ");
	Serial.println(ir.rr);
	Serial.println("");
	Serial.println("========== Board ==========");
	print_board(board);
	delay(1000);
	beep_buzzer(buz);
}

void	beep_buzzer(int buz)
{
	if (buz)
	{
		digitalWrite(BUZZER, LOW);
		delay(200);
		digitalWrite(BUZZER, HIGH);
		delay(200);
	}
}

void	print_board(int board[BOARD_SIZE][BOARD_SIZE])
{
	int	row;
	int	col;

	row = 0;
	while (row < BOARD_SIZE)
	{
		col = 0;
		while (col < BOARD_SIZE)
		{
			Serial.print(board[row][col]);
			if (col < 5)
				Serial.print(", ");
			col++;
		}
		Serial.println("");
		row++;
	}
}
