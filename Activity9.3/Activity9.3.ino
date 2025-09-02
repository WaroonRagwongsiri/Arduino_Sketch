// North -> South
#define N_BUTTON 3
#define LED_N_R 10
#define LED_N_Y 9
#define LED_N_G 8

// East -> West
#define E_BUTTON 2
#define LED_E_R 6
#define LED_E_Y 5
#define LED_E_G 4

// Walk
#define W_BUTTON 1
#define LED_W_R 12
#define LED_W_G 11

// State
#define goN 0
#define waitN 1
#define goE 2
#define waitE 3
#define walk 4
#define black 5
#define green 6
#define walk_end 7

typedef struct	s_fsm
{
	unsigned long	ST_Out;
	unsigned long	Time;
	unsigned long	NextST[8];
}	t_fsm;

void	setup()
{
	// North
	pinMode(N_BUTTON, INPUT_PULLUP);
	pinMode(LED_N_R, OUTPUT);
	pinMode(LED_N_Y, OUTPUT);
	pinMode(LED_N_G, OUTPUT);

	// East
	pinMode(E_BUTTON, INPUT_PULLUP);
	pinMode(LED_E_R, OUTPUT);
	pinMode(LED_E_Y, OUTPUT);
	pinMode(LED_E_G, OUTPUT);

	// Walk
	pinMode(W_BUTTON, INPUT_PULLUP);
	pinMode(LED_W_R, OUTPUT);
	pinMode(LED_W_G, OUTPUT);
}

const t_fsm	FSM[8] = {
	// W:RG N:RYG E:RYG
	{B10001100, 5000, {goN, waitN, goN, waitN, waitN, waitN, waitN, waitN}}, // goN
	{B10010100, 1000, {goE, goE, goE, goE, walk, walk, walk, walk}}, // waitN
	{B10100001, 5000, {goE, goE, waitE, waitE, waitE, waitE, waitE, waitE}}, // goE
	{B10100010, 1000, {goN, goN, goN, goN, walk, walk, walk, walk}}, // waitE
	{B01100100, 5000, {black, black, black, black, walk, walk, walk, walk}}, // walk
	{B00100100, 1000, {walk_end, walk_end, walk_end, walk_end, walk_end, walk_end, walk_end, walk_end}}, // black
	{B01100100, 1000, {walk_end, walk_end, walk_end, walk_end, walk_end, walk_end, walk_end, walk_end}}, // green
	{B10100100, 1000, {waitE, waitN, waitE, waitN, waitE, waitN, waitE, waitN}} // walk_end
};

static int	input = 0;
static int	input_n = 0;
static int	input_e = 0;
static int	input_w = 0;

static int	counter = 0;
static int	ST = goN;

void	loop()
{
	// State LED
	digitalWrite(LED_N_R, !(FSM[ST].ST_Out & B00100000));
	digitalWrite(LED_N_Y, !(FSM[ST].ST_Out & B00010000));
	digitalWrite(LED_N_G, !(FSM[ST].ST_Out & B00001000));

	digitalWrite(LED_E_R, !(FSM[ST].ST_Out & B00000100));
	digitalWrite(LED_E_Y, !(FSM[ST].ST_Out & B00000010));
	digitalWrite(LED_E_G, !(FSM[ST].ST_Out & B00000001));

	digitalWrite(LED_W_R, !(FSM[ST].ST_Out & B10000000));
	digitalWrite(LED_W_G, !(FSM[ST].ST_Out & B01000000));

	delay(FSM[ST].Time);

	// Handle blinking states (black and green)
	if (ST == black || ST == green)
	{
		if (counter < 6)
		{
			counter++;
			ST = (ST == black) ? green : black;
		}
		else
		{
			counter = 0;

			// Input State
			input_n = digitalRead(N_BUTTON);
			input_e = digitalRead(E_BUTTON);
			input_w = digitalRead(W_BUTTON);
			input = input_w * 4 + input_n * 2 + input_e;
			
			ST = FSM[ST].NextST[input];
		}
	}
	else
	{
		counter = 0;

		// Input State
		input_n = digitalRead(N_BUTTON);
		input_e = digitalRead(E_BUTTON);
		input_w = digitalRead(W_BUTTON);
		input = input_w * 4 + input_n * 2 + input_e;
		
		ST = FSM[ST].NextST[input];
	}
}
