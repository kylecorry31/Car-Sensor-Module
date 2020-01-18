#include "Ultrasonic.h"
#include "Buzzer.h"
#include "CarModule.H"
#include "BackupSensorModule.h"

// Pins
#define TRIGGER_PIN 9
#define ECHO_PIN 8
#define BUZZER_PIN 11

#define LOOP_DELAY_MS 50

#define NUM_MODULES 1

// Create the backup sensor
#define BUZZER_ON_DURATION 200
#define DEFAULT_BUZZER_OFF_DURATION 1000
#define BUZZER_FREQUENCY 640

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
Buzzer buzzer(BUZZER_PIN, BUZZER_FREQUENCY, BUZZER_ON_DURATION, DEFAULT_BUZZER_OFF_DURATION);
BackupSensorModule backupSensors(&ultrasonic, &buzzer);

// Install the car modules
CarModule *const modules[NUM_MODULES] = { &backupSensors };

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < NUM_MODULES; i++)
  {
    modules[i]->initialize();
  }
}

void loop()
{
  long startTime = millis();
  for (int i = 0; i < NUM_MODULES; i++)
  {
    modules[i]->update();
  }
  delay(50);//getLoopDelay(startTime));
}


long getLoopDelay(long startTime)
{
  long dt = millis() - startTime;
  return min(LOOP_DELAY_MS - dt, LOOP_DELAY_MS);
}
