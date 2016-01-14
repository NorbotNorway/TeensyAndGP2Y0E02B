/*
 Name:		Sketch1.ino
 Created:	1/14/2016 8:59:44 PM
 Author:	nordband
 
 Code is mostly inspired from: http://www.robot-electronics.co.uk/gp2y0e02b.html
*/

#include <Wire.h>

int shift = 0;
byte hi, low;
int distance;

int count = 0;
int max_count = 100000;
long totalMillis = 0;

int t0 = 0;

#define ADDRESS      0x80 >> 1
#define DISTANCE_REG 0x5E
#define SHIFT        0x35

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(19200);

	Wire.begin();
	delay(50);
	Serial.println("Hallo");
	Wire.beginTransmission(ADDRESS);
	Wire.write(SHIFT);
	Wire.endTransmission();

	Wire.requestFrom(ADDRESS, 1);
	while (Wire.available() == 0);
	Serial.println("Wire available!");
	shift = Wire.read();
}

// the loop function runs over and over again until power down or reset
void loop() {

	if (count == 0)
		t0 = millis();

	if (count++ < max_count) {

		

		Wire.beginTransmission(ADDRESS);
		Wire.write(DISTANCE_REG);
		Wire.endTransmission();

		Wire.requestFrom(ADDRESS, 2);
		while (Wire.available() < 2);

		hi = Wire.read();
		low = Wire.read();

		distance = (hi * 16 + low) / 16 / (int)pow(2, shift);

		//int t1 = millis() - t0;
		//totalMillis += t1;

		if (count >= max_count) {
			int t1 = millis();
			//Serial.println(totalMillis / max_count);
			Serial.println(t1 - t0);
		}
	}

}
