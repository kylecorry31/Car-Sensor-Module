#ifndef BACKUP_SENSOR_CAR_MODULE_H
#define BACKUP_SENSOR_CAR_MODULE_H

#include "CarModule.H"
#include "KalmanFilter.h"

class BackupSensorModule : public CarModule
{

private:

  Ultrasonic* _ultrasonic;
  Buzzer* _buzzer;
  double _distanceEstimate;
  double _distanceEstimate2;
  KalmanFilter* filter;

  bool outOfBounds = false;

  void updateDistanceEstimate()
  {
    double distance = _ultrasonic->getDistanceIn();

    if (distance == 0)
    {
      // Unable to get reading
      return;
    }

    _distanceEstimate = filter->filter((float) distance);

    Serial.print(distance,3);
    Serial.print(",");
    Serial.print(_distanceEstimate,3);
    Serial.println();
  }

public:

  BackupSensorModule(Ultrasonic* ultrasonic, Buzzer* buzzer)
  {
    _ultrasonic = ultrasonic;
    _buzzer = buzzer;
    _distanceEstimate = 0;
    filter = new KalmanFilter(0.4, 60, 60, 0.1);
  }

  ~BackupSensorModule()
  {
    free(filter);
  }

  void initialize()
  {
    _buzzer->off();
  }

  void update()
  {
    updateDistanceEstimate();

    if (_distanceEstimate < 90 && _distanceEstimate > 8){

      double minDist = 8;
      double maxDist = 90;

      double normalDistance = (_distanceEstimate - minDist) / (maxDist - minDist);

      if (normalDistance < 0.05)
      {
              _buzzer->setOffDuration(0);
      }
      else 
      {
        _buzzer->setOffDuration(long(normalDistance * 1000));
      }
      _buzzer->on();
    } else {
      _buzzer->off();
    }
  
    _buzzer->run();
  }
  
};

#endif
