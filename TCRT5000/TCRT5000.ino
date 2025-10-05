#define T1_PIN A0

void setup(void)
{
	Serial.begin(9600);
}

void loop(void)
{
	int	val;

	val = analogRead(T1_PIN);
	Serial.println(val);
	delay(500);
}
