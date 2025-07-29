#define SW_A 3
#define SW_G 2

const int	seg_pattern[] = {
	B00111111, // 0
	B00000110, // 1
	B01011011, // 2
	B01001111, // 3
	B01100110, // 4
	B01101101, // 5
	B01111101, // 6
	B00000111, // 7
	B01111111, // 8
	B01101111, // 9
	B00110001, // g_ans > g_guess
	B00111000, // g_ans < g_guess
};
const int	segment_pin[] = {5,6,7,8,9,10,11,12};

static int	g_ans = 1;
static int	g_guess = 0;

void	setup()
{
	pinMode(SW_A, INPUT_PULLUP);
	pinMode(SW_G, INPUT_PULLUP);
	for (int i = 0; i < 8; i++)
	{
		pinMode(segment_pin[i], OUTPUT);
	}
	Serial.begin(9600);
}

void	loop()
{
	// for (int j = 0; j < 9 ; j++)
	// {
	// 	for (int i = 0; i < 8; i++)
	// 	{
	// 		digitalWrite(segment_pin[i], bitRead(seg_pattern[j], i));
	// 	}
	// 	delay(2000);
	// 	set_zero();
	// }
	if (g_guess == 0)
	{
		randomSeed(0);
		g_guess = random(1, 10);
		Serial.println(g_guess);
	}
	for (int i = 0; i < 8; i++)
	{
		digitalWrite(segment_pin[i], bitRead(seg_pattern[g_ans], i));
	}
	handle_add_button();
	handle_guess_button();
}

void	set_zero()
{
	for (int i = 0; i < 8; i++)
	{
		digitalWrite(segment_pin[i], LOW);
	}
}

void	handle_add_button()
{
	int reading = digitalRead(SW_A);
	if (reading == LOW)
	{
		g_ans++;
		delay(250);
		if (g_ans > 9)
		{
			g_ans = 1;
		}
	}
}

void	handle_guess_button()
{
	int reading = digitalRead(SW_G);
	if (reading == LOW)
	{
		delay(250);
		if (g_ans == g_guess)
		{
			g_ans = 0;
			g_guess = random(1, 10);
			Serial.println(g_guess);
			return ;
		}
		else if (g_ans > g_guess)
		{
			g_ans = 10;
		}
		else if (g_ans < g_guess)
		{
			g_ans = 11;
		}
	}
}
