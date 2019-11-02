


class UltrasonicSensor {

private:
int _trigger;
int _echo;

public:
  UltrasonicSensor(int trigger, int echo){
    _trigger = trigger;
    _echo = echo;

    pinMode(_trigger, OUTPUT);
    pinMode(_echo, INPUT);
  }

  float distance(){
    const float INCHES_PER_MICROSECOND = 0.0135039;
  
    // Send the pulse out
    digitalWrite(_trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigger, LOW);
  
    // Read the pulse
    unsigned long duration = pulseIn(_echo, HIGH);
    return (duration * INCHES_PER_MICROSECOND) / 2.0f;
  }
  
};
