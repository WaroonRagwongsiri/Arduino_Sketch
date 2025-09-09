#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); // SoftwareSerial(rxPin, txPin)

void setup()
{
	Serial.begin(9600);
	Serial.println("Write 1 - 9 to blink LED n times");
	mySerial.begin(9600);
}
void loop()
{
	while (Serial.available() > 0)
	{
		mySerial.print((char) Serial.read());
	}
}
