#include "RobotCar.h"

void	log(int buz)
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
