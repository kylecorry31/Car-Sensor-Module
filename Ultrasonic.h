#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#define CENTIMETERS_TO_INCHES 0.393701

class Ultrasonic {

private:
int _triggerPin;
int _echoPin;

public:
  Ultrasonic(int triggerPin, int echoPin){
    _triggerPin = triggerPin;
    _echoPin = echoPin;
    pinMode(_triggerPin, OUTPUT);
    pinMode(_echoPin, INPUT);
    digitalWrite(_echoPin, HIGH);
  }

  double getDistanceIn()
  {
    return getDistanceCm() * CENTIMETERS_TO_INCHES;
  }
  
  /**
   * @return the current distance in meters
   */
  double getDistanceCm(){
    // Write the trigger
    digitalWrite(_triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(20);
    digitalWrite(_triggerPin, LOW);

    // Read the echo
    long duration = pulseIn(_echoPin, HIGH, 38000); 

    // Calculating the distance in centimeters
    return duration * 0.034 / 2;
  }
  
};

#endif
