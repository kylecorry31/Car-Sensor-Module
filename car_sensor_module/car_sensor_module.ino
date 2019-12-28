#include "Ultrasonic.h"

#define TRIGGER_PIN 9
#define ECHO_PIN 9
#define BUZZER_PIN 4

#define NUM_SAMPLES 5
#define METERS_TO_INCHES 39.3701
#define INDICATOR_THRESHOLD (12.0f * 5.0f)

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

void setup() {
}

void loop() {
 parkingSensors(); 
}


void parkingSensors(){

  float distance = 0;
  for (int i = 0; i < NUM_SAMPLES; i++){
      distance += ultrasonic.distance();
  }
  distance /= NUM_SAMPLES;

  distance *= METERS_TO_INCHES;

  float maxDistance = 200;

  if (distance < maxDistance && distance > 0.001){
    int buzzFreq = int((distance / maxDistance) * 1000);
    tone(BUZZER_PIN, 640);
    delay(buzzFreq);
  } else {
    noTone(BUZZER_PIN);
  }
}
