#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 10); // SoftwareSerial(rxPin, txPin)

static int	board[6][7] = {
	{9, 9, 9, 9, 9, 9, 9, },
	{9, 9, 9, 9, 9, 9, 9, },
	{9, 9, 9, 9, 9, 9, 9, },
	{9, 9, 9, 9, 9, 9, 9, },
	{9, 9, 9, 9, 9, 9, 9, },
	{9, 9, 9, 9, 9, 9, 9, },
};

void setup()
{
	Serial.begin(2400);
	mySerial.begin(2400);
	Serial.println("FSM");
}

void loop()
{
	String	msg;
	if (Serial.available() > 0)
	{
		String str = Serial.readString();
		if (str == "sent")
		{
			display_board_serial();
			Serial.print("Sented");
		}
	}
	delay(10);
}

void	display_board_serial(void)
{
	String	msg;

	msg = "";
	Serial.println("Board Array:");
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 7; col++)
		{
			Serial.print(board[row][col]);
			msg += (String) (board[row][col]);
			if (col < 6)
			{
				Serial.print(",");
				msg += ",";
			}
		}
		msg += "\n";
		Serial.println();
	}
	mySerial.print(msg);
	Serial.println();
}
