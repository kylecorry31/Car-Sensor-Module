#include "UltrasonicSensor.h"
#ifndef LED_H
#include "LED.h"
#endif
#include "LEDDistanceDisplay.h"

UltrasonicSensor frontUltrasonic(9, 10);

// Create the front display
LED frontLEDs[] = { LED(2) };
float frontDistances[] = { 12.0 };
LEDDistanceDisplay frontDisplay(frontLEDs, frontDistances, 1);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  float frontDistance = frontUltrasonic.distance();
  frontDisplay.update(frontDistance);
}
