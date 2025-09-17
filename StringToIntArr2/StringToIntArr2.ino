#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 10); // SoftwareSerial(rxPin, txPin)

static int	board[6][7] = {
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
};

void setup()
{
	Serial.begin(2400);
	mySerial.begin(2400);
	Serial.println("Recieve");
}

void loop()
{
	if (mySerial.available() > 0)
	{
		serial_to_board();
		display_board_serial();
	}
	delay(10);
}

void	serial_to_board()
{
	String	str;
	int		row;
	int		col;
	int		num;

	str = mySerial.readString();
	row = 0;
	num = 0;
	while (row < 6)
	{
		col = 0;
		while (col < 7)
		{
			board[row][col] = str[num] - '0';
			col++;
			num += 2;
		}
		row++;
	}
}

void	display_board_serial(void)
{
	Serial.println("Board Array:");
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 7; col++)
		{
			Serial.print(board[row][col]);
			if (col < 6)
			{
				Serial.print(",");
			}
		}
		Serial.println();
	}
	Serial.println();
}
