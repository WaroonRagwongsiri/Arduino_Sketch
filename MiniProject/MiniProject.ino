// Define Input Button
#define BUTTON_0 13
#define BUTTON_1 12
#define BUTTON_2 11
#define BUTTON_3 10
#define BUTTON_4 9
#define BUTTON_5 8
#define BUTTON_6 7

// Define Out
#define OUT_1 4
#define OUT_2 3
#define OUT_3 2

// Define State
#define col0_p1 0
#define col1_p1 1
#define col2_p1 2
#define col3_p1 3
#define col4_p1 4
#define col5_p1 5
#define col6_p1 6
#define col0_p2 7
#define col1_p2 8
#define col2_p2 9
#define col3_p2 10
#define col4_p2 11
#define col5_p2 12
#define col6_p2 13

typedef struct s_fsm
{
	int	col;
	int	player;
	int	time;
	int	next_st[8];
}	t_fsm;

static int	board[6][7] = {
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
};

t_fsm	FSM[15] = {
	{0, 1, 5000, {col0_p1, col0_p2, col1_p2, col2_p2, col3_p2, col4_p2, col5_p2, col6_p2, }}, 	//col0_p1
	{1, 1, 5000, {col1_p1, col0_p2, col1_p2, col2_p2, col3_p2, col4_p2, col5_p2, col6_p2, }},	//col1_p1
	{2, 1, 5000, {col2_p1, col0_p2, col1_p2, col2_p2, col3_p2, col4_p2, col5_p2, col6_p2, }},	//col2_p1
	{3, 1, 5000, {col3_p1, col0_p2, col1_p2, col2_p2, col3_p2, col4_p2, col5_p2, col6_p2, }},	//col3_p1
	{4, 1, 5000, {col4_p1, col0_p2, col1_p2, col2_p2, col3_p2, col4_p2, col5_p2, col6_p2, }},	//col4_p1
	{5, 1, 5000, {col5_p1, col0_p2, col1_p2, col2_p2, col3_p2, col4_p2, col5_p2, col6_p2, }},	//col5_p1
	{6, 1, 5000, {col6_p1, col0_p2, col1_p2, col2_p2, col3_p2, col4_p2, col5_p2, col6_p2, }},	//col6_p1

	{7, 2, 5000, {col0_p2, col0_p1, col1_p1, col2_p1, col3_p1, col4_p1, col5_p1, col6_p1, }}, 	//col0_p2
	{8, 2, 5000, {col1_p2, col0_p1, col1_p1, col2_p1, col3_p1, col4_p1, col5_p1, col6_p1, }}, 	//col1_p2
	{9, 2, 5000, {col2_p2, col0_p1, col1_p1, col2_p1, col3_p1, col4_p1, col5_p1, col6_p1, }}, 	//col2_p2
	{10, 2, 5000, {col3_p2, col0_p1, col1_p1, col2_p1, col3_p1, col4_p1, col5_p1, col6_p1, }}, 	//col3_p2
	{11, 2, 5000, {col4_p2, col0_p1, col1_p1, col2_p1, col3_p1, col4_p1, col5_p1, col6_p1, }}, 	//col4_p2
	{12, 2, 5000, {col5_p2, col0_p1, col1_p1, col2_p1, col3_p1, col4_p1, col5_p1, col6_p1, }}, 	//col5_p2
	{13, 2, 5000, {col6_p2, col0_p1, col1_p1, col2_p1, col3_p1, col4_p1, col5_p1, col6_p1, }}, 	//col6_p2
};

static int	ST = 0;

static int	last_ST = 0;

void	setup()
{
	// Setup Button
	pinMode(BUTTON_0, INPUT_PULLUP);
	pinMode(BUTTON_1, INPUT_PULLUP);
	pinMode(BUTTON_2, INPUT_PULLUP);
	pinMode(BUTTON_3, INPUT_PULLUP);
	pinMode(BUTTON_4, INPUT_PULLUP);
	pinMode(BUTTON_5, INPUT_PULLUP);
	pinMode(BUTTON_6, INPUT_PULLUP);

	// Setup Out
	pinMode(OUT_1, OUTPUT);
	pinMode(OUT_2, OUTPUT);
	pinMode(OUT_3, OUTPUT);
	Serial.begin(9600);
}

void	loop()
{
	int	input;

	if (last_ST != ST)
	{
		put_coin(FSM[ST].col, FSM[ST].player);
		last_ST = ST;
	}
	display_board_serial();
	delay(FSM[ST].time);

	// Input State
	input = get_input();
	ST = FSM[ST].next_st[input];
}

int	get_input()
{
	int	input0;
	int	input1;
	int	input2;
	int	input3;
	int	input4;
	int	input5;
	int	input6;
	int	input;

	input0 = !(digitalRead(BUTTON_0)) * 1;
	input1 = !(digitalRead(BUTTON_1)) * 2;
	input2 = !(digitalRead(BUTTON_2)) * 4;
	input3 = !(digitalRead(BUTTON_3)) * 8;
	input4 = !(digitalRead(BUTTON_4)) * 16;
	input5 = !(digitalRead(BUTTON_5)) * 32;
	input6 = !(digitalRead(BUTTON_6)) * 64;

	input = input0 + input1 + input2 + input3 + input4 + input5 + input6;
	if (input == 1)
		return (1);
	else if (input == 2)
		return (2);
	else if (input == 4)
		return (3);
	else if (input == 8)
		return (4);
	else if (input == 16)
		return (5);
	else if (input == 32)
		return (6);
	else if (input == 64)
		return (7);
	else
		return (0);
}

void	put_coin(int col, int player)
{
    int	i;

	i = 5;
    while (i >= 0)
	{
		if (board[i][col] == 0)
		{
			board[i][col] = player;
			return ;
		}
		--i;
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
				Serial.print(",");
		}
		Serial.println();
	}
	Serial.println();
}
