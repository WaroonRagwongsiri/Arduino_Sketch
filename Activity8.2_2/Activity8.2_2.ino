#define LED 13

#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); // SoftwareSerial(rxPin, txPin)

void setup()
{
	Serial.begin(9600);
	pinMode(LED,OUTPUT);
	mySerial.begin(9600);
	digitalWrite(LED, LOW);
}

void loop()
{
	char	n;

	n = '\0';
	while (mySerial.available() > 0)
	{
		n = (char) mySerial.read();
		while (n > '0')
		{
			digitalWrite(LED, HIGH);
			delay(500);
			digitalWrite(LED, LOW);
			delay(500);
			--n;
		}
	}
	delay(500);
}
