// #include "pitches.h"

#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440

// define sw
#define SW_1 12 // 6 % 6 // 0
#define SW_2 11 // 5 % 6 // 1
#define SW_3 10 // 4 % 6 // 2
#define SW_4 9 // 3 % 6 // 3
#define SW_5 8 // 2 % 6 // 4
#define SW_6 7 // 1 % 6 // 5

// define speaker
#define PIEZO 3

static	int	read = 0;
static	int	recorded[100] = {0};
const	int	note[6] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4};

void setup()
{
	pinMode(SW_1, INPUT);
	pinMode(SW_2, INPUT);
	pinMode(SW_3, INPUT);
	pinMode(SW_4, INPUT);
	pinMode(SW_5, INPUT);
	pinMode(SW_6, INPUT);
	Serial.begin(9600);
	Serial.println("1 : Play Record");
	Serial.println("2 : Record");
}

void loop()
{
	// Check read
	if (Serial.available())
	{
		read = Serial.read();
		// read
		Serial.println(read);
		if (read == '1')
		{
			Serial.println("-------------------");
			Serial.println("Playing from record");
			Serial.println("-------------------");
			play_record();
			read = 0;
		}
		else if (read == '2')
		{
			Serial.println("-------------------");
			Serial.println("Recording");
			Serial.println("-------------------");
			record();
			read = 0;
		}
	}
	
	if (read == 0 || read == '0')
	{
		// normal sw
		if (digitalRead(SW_1) == HIGH)
			play_tune(SW_1);
		else if (digitalRead(SW_2) == HIGH)
			play_tune(SW_2);
		else if (digitalRead(SW_3) == HIGH)
			play_tune(SW_3);
		else if (digitalRead(SW_4) == HIGH)
			play_tune(SW_4);
		else if (digitalRead(SW_5) == HIGH)
			play_tune(SW_5);
		else if (digitalRead(SW_6) == HIGH)
			play_tune(SW_6);
	}
}

void record()
{
	int note;
	int record_index = 0;

	while (true)
	{
		if (Serial.available())
		{
			char input = Serial.read();
			if (input != '2')
			{
				read = input;
				return ;
			}
		}

		note = press_sw();
		if (note != 0)
		{
			if (record_index < sizeof(recorded) / sizeof(recorded[0]))
			{
				recorded[record_index++] = note;
				play_tune(note);
				delay(200);
			}
		}
	}
}

void	play_record()
{
	int	i;

	i = 0;
	for(i = 0; i < sizeof(recorded) / sizeof(recorded[0]); i++)
	{
		if (recorded[i] == 0)
			return ;
		play_tune(recorded[i]);
		delay(200);
	}
	read = 0;
}

int	press_sw()
{
	if (digitalRead(SW_1) == HIGH)
		return SW_1;
	else if (digitalRead(SW_2) == HIGH)
		return SW_2;
	else if (digitalRead(SW_3) == HIGH)
		return SW_3;
	else if (digitalRead(SW_4) == HIGH)
		return SW_4;
	else if (digitalRead(SW_5) == HIGH)
		return SW_5;
	else if (digitalRead(SW_6) == HIGH)
		return SW_6;
	return 0;
}

int	play_tune(int sw)
{
	int	index;

	index = (sw - 6) % 6;
	tone(PIEZO, note[index], 200);
	delay(200);
	return index;
}
