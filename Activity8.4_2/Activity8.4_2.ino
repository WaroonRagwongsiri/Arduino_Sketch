#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 10); // SoftwareSerial(rxPin, txPin)

void setup()
{
	Serial.begin(2400);
	mySerial.begin(2400);
	Serial.println("I'm B");
}

void loop()
{
	if (mySerial.available() > 0)
	{
		String str = mySerial.readString();
		Serial.print("A : ");
		Serial.print(str);
	}
	if (Serial.available() > 0)
	{
		String str = Serial.readString();
		mySerial.println(str);
		Serial.print("ME : ");
		Serial.println(str);
	}
	delay(10);
}
