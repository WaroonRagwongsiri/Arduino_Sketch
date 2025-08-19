const int				rowPins[3] = {12, 11, 10};
const int				colPins[3] = {7, 6, 5};
static int				curr_pat = 0;
static unsigned long	lastChange = 0;

const int				patterns[][3][3] = {
	{ // X
		{1, 0, 1},
		{0, 1, 0},
		{1, 0, 1}
	},
	{ // O
		{1, 1, 1},
		{1, 0, 1},
		{1, 1, 1}
	},
};

void	setup()
{
	off();
}

void	loop()
{
	if (millis() - lastChange > 1000)
	{
		lastChange = millis();
		curr_pat++;
		curr_pat %= 2;
	}
	displayPattern(patterns[curr_pat]);
}

void	off()
{
	for (int i = 0; i < 3; i++)
	{
		pinMode(rowPins[i], OUTPUT);
		pinMode(colPins[i], OUTPUT);
	}
}

void	displayPattern(const int pattern[3][3])
{
	int	col;
	int	row;

	col = -1;
	while (++col < 3)
	{
		digitalWrite(colPins[col], LOW);
		row = -1;
		while (++row < 3)
		{
			if (pattern[row][col] == 1)
			{
				digitalWrite(rowPins[row], HIGH);
			}
			else
			{
				digitalWrite(rowPins[row], LOW);
			}
		}
		delay(2);
		digitalWrite(colPins[col], HIGH);
	}
}
