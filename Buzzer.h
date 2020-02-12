#ifndef BUZZER_H
#define BUZZER_H


class Buzzer 
{

private:
  int _pin;
  unsigned long _onDuration;
  unsigned long _offDuration;
  bool _isEnabled;
  bool _isPlaying;

  unsigned int _frequency;
  
  unsigned long _timer;

  void turnOn()
  {
    if (_isPlaying)
    {
      return;
    }
    tone(_pin, _frequency);
    _isPlaying = true;
    _timer = millis();
  }

  void turnOff()
  {
    if (!_isPlaying)
    {
      return;
    }
    noTone(_pin);
    _isPlaying = false;
    _timer = millis();
  }

  bool shouldTurnOff()
  {
    if (!_isPlaying)
    {
      return false;  
    }

    if (_offDuration == 0)
    {
      return false;
    }

    return millis() - _timer >= _onDuration;
  }

  bool shouldTurnOn()
  {
    if (_isPlaying)
    {
      return false;  
    }

    return millis() - _timer >= _offDuration;
  }

public:
  Buzzer(int pin, unsigned int frequency, unsigned long onDuration, unsigned long offDuration)
  {
    _pin = pin;
    _onDuration = onDuration;
    _offDuration = offDuration;
    _frequency = frequency;
    pinMode(_pin, OUTPUT);
  }

  void run()
  {
    if (!_isEnabled)
    {
      turnOff();
      return;
    }

    if (shouldTurnOff())
    {
      turnOff();
    } else if (shouldTurnOn())
    {
      turnOn();  
    }
  }

  void on()
  {
    _isEnabled = true;
  }

  void off()
  {
    _isEnabled = false;
    turnOff();
  }

  void setOnDuration(unsigned long onDuration)
  {
    _onDuration = onDuration;
  }

  void setOffDuration(unsigned long offDuration)
  {
    _offDuration = offDuration;
  }
  
};

#endif
