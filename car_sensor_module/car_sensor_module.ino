#include "Ultrasonic.h"
#include "Buzzer.h"

#define TRIGGER_PIN 9
#define ECHO_PIN 9
#define BUZZER_PIN 4

#define NUM_SAMPLES 5
#define CENTIMETERS_TO_INCHES 0.393701

#define BUZZER_ON_DURATION 500
#define DEFAULT_BUZZER_OFF_DURATION 1000
#define BUZZER_FREQUENCY 640

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
Buzzer buzzer(BUZZER_PIN, BUZZER_FREQUENCY, BUZZER_ON_DURATION, DEFAULT_BUZZER_OFF_DURATION);

void setup() {
  Serial.begin(9600);
}


void loop() {
 parkingSensors(); 
}


void parkingSensors(){

  double distance = ultrasonic.distance();
  distance *= CENTIMETERS_TO_INCHES;

  Serial.println(distance);

  float maxDistance = 100;

  if (distance < maxDistance && distance > 0.001){
    buzzer.setOffDuration(long((distance / maxDistance) * 1000));
    buzzer.on();
  } else {
    buzzer.off();
  }

  delay(50);

}
