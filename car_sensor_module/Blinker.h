

class Blinker {

private:
  unsigned long _lastChange;
  bool _isOn;

public:
  Blinker(){
    _lastChange = millis();
    _isOn = false;
  }

  void update(unsigned long interval){
    unsigned long currentTime = millis();
    if (currentTime - _lastChange >= interval){
      _isOn = !_isOn;
      _lastChange = currentTime;
    }
  }

  bool isOn(){
    return _isOn;
  }
  
};
