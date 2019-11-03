#ifndef LED_H
#define LED_H


class LED {

private:
int _pin;

public:
  LED(int pin){
    _pin = pin;
    pinMode(_pin, OUTPUT);
  }

  void on(){
    digitalWrite(_pin, HIGH);
  }

  void off(){
    digitalWrite(_pin, LOW);
  }

  void set(bool isOn){
    if (isOn){
      on();  
    } else {
      off();
    }
  }
  
};

#endif
