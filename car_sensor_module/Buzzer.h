

class Buzzer {

private:
int _pin;

public:
  Buzzer(int pin){
    _pin = pin;
    pinMode(_pin, OUTPUT);
  }

  void on(int frequency){
    tone(_pin, frequency);
  }

  void off(){
    noTone(_pin);
  }

};
