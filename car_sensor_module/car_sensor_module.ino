#include "UltrasonicSensor.h"
#include "ProximitySensor.h"
#include "LED.h"
#include <NewPing.h>

#define LEFT_TRIGGER_PIN 10
#define LEFT_ECHO_PIN 10
#define RIGHT_TRIGGER_PIN 9
#define RIGHT_ECHO_PIN 9
#define LEFT_LED_PIN 5
#define RIGHT_LED_PIN 6

#define INDICATOR_THRESHOLD (12.0f * 5.0f)

NewPing leftUltrasonic(LEFT_TRIGGER_PIN, LEFT_ECHO_PIN);
NewPing rightUltrasonic(RIGHT_TRIGGER_PIN, RIGHT_TRIGGER_PIN);

LED leftIndicator(LEFT_LED_PIN);
LED rightIndicator(RIGHT_LED_PIN);

void setup() {
  Serial.begin(9600);
}

void loop() {
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
