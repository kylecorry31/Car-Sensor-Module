#ifndef LED_H
#include "LED.h"
#endif

class LEDDistanceDisplay {

private:
  int _length;
  LED* _leds;
  float* _distances;

public:
  LEDDistanceDisplay(LED* leds, float* activationDistances, int numLEDs){
     _length = numLEDs;
     _leds = leds;
     _distances = activationDistances;
  }

  void update(float currentDistance){
    for (int i = 0; i < _length; i++){
      
      if (currentDistance < _distances[i]){
        // Turn the led on if the current distance is inside the activation threshold
        _leds[i].on();  
      } else {
        // Turn the led off if the current distance is outside the activation threshold
        _leds[i].off();
      }
      
    }
  }

  
};
