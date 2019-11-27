#include "LED.h"
#include <NewPing.h>

#define LEFT_TRIGGER_PIN 10
#define LEFT_ECHO_PIN 10
#define RIGHT_TRIGGER_PIN 9
#define RIGHT_ECHO_PIN 9
#define LEFT_LED_PIN 5
#define RIGHT_LED_PIN 6
#define BUZZER_PIN 4
#define THERMISTER_PIN A0
#include <NewTone.h>

#define INDICATOR_THRESHOLD (12.0f * 5.0f)

NewPing leftUltrasonic(LEFT_TRIGGER_PIN, LEFT_ECHO_PIN);
NewPing rightUltrasonic(RIGHT_TRIGGER_PIN, RIGHT_TRIGGER_PIN);

LED leftIndicator(LEFT_LED_PIN);
LED rightIndicator(RIGHT_LED_PIN);

void setup() {
  Serial.begin(9600);
  pinMode(THERMISTER_PIN, INPUT);
}

void loop() {
 parkingSensors(); 
}

float getAverageTemperature(int iterations){
  float t = 0;
  for (int i = 0; i < iterations; i++){
    t += getTemperature();
  }
  return t / iterations;
}

float getTemperature(){
  int Vo = analogRead(THERMISTER_PIN);
  float R2 = 100000 * (1023.0 / (float)Vo - 1.0);
  float logR2 = log(R2);
  float T = (1.0 / (1.009249522e-03 + 2.378405444e-04*logR2 + 2.019202697e-07*logR2*logR2*logR2));
  T = T - 273.15;
  return T;
}


void parkingSensors(){
  float duration = rightUltrasonic.ping_median();
  const float speedOfSound = 0.393701 * (331.4 + 0.606 * 20/*getAverageTemperature(20)*/) / 10000.0;
  float distance = duration * speedOfSound / 2.0;

  float maxDistance = 200;

  if (distance < maxDistance && distance > 0.001){
    int buzzFreq = int((distance / maxDistance) * 1000);
    NewTone(BUZZER_PIN, 640, buzzFreq);
    delay(buzzFreq);
  } else {
    noNewTone(BUZZER_PIN);
  }
}

void blindSpotDetection(){
  float leftDuration = leftUltrasonic.ping_median();
  float rightDuration = rightUltrasonic.ping_median();

  const float microsecondsToInches = 0.0135039;

  float leftDistance = leftDuration * microsecondsToInches / 2.0;
  float rightDistance = rightDuration * microsecondsToInches / 2.0;
  
  leftIndicator.set(leftDistance <= INDICATOR_THRESHOLD);
  rightIndicator.set(rightDistance <= INDICATOR_THRESHOLD);

  
  Serial.print("Left: ");
  Serial.print(leftDistance);
  Serial.print(" inches, ");

  Serial.print("Right: ");
  Serial.print(rightDistance);
  Serial.println(" inches, ");

  delay(20);  
}
