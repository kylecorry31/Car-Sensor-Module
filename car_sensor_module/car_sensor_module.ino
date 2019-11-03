#include "UltrasonicSensor.h"
#ifndef LED_H
#include "LED.h"
#endif

UltrasonicSensor leftSonar(9, 10);
UltrasonicSensor rightSonar(11, 12);

LED leftIndicator(5);
LED rightIndicator(6);

const float INDICATOR_THRESHOLD = 60.0f;

void setup() {
}

void loop() {
  float leftDistance = leftSonar.average_distance(5);//leftSonar.convert_in(leftSonar.ping_median());
  float rightDistance = rightSonar.average_distance(5);//convert_in(rightSonar.ping_median());

  if (leftDistance <= INDICATOR_THRESHOLD){
    leftIndicator.on();  
  } else {
    leftIndicator.off();  
  }

  if (rightDistance <= INDICATOR_THRESHOLD){
    rightIndicator.on();  
  } else {
    rightIndicator.off();  
  }
}
