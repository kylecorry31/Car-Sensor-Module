#ifndef ULTRASONIC_H
#define ULTRASONIC_H


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
  }

  /**
   * @return the current distance in meters
   */
  float distance(){
    pinMode(_triggerPin, OUTPUT);

    // Write the trigger
    digitalWrite(_triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_triggerPin, LOW);

    // Read the echo
    pinMode(_echoPin, INPUT);
    long duration = pulseIn(_echoPin, HIGH);

    // Calculating the distance in meters
    return duration * 0.00034 / 2;
  }
  
};

#endif
