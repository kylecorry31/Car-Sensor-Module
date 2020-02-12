#include "Ultrasonic.h"
#include "Buzzer.h"
#include <KalmanFilter.h>

// Pins
#define TRIGGER_PIN 9
#define ECHO_PIN 8
#define BUZZER_PIN 11

// Create the backup sensor
#define BUZZER_ON_DURATION 200
#define DEFAULT_BUZZER_OFF_DURATION 1000
#define BUZZER_FREQUENCY 640

#define MIN_BEEP_DISTANCE 8
#define MAX_BEEP_DISTANCE 90
#define SUPER_CLOSE_THRESHOLD 0.05
#define BUZZER_FREQUENCY_SCALE 1000
#define LOOP_DELAY_MS 50

Ultrasonic ultrasonic {TRIGGER_PIN, ECHO_PIN};
Buzzer buzzer {BUZZER_PIN, BUZZER_FREQUENCY, BUZZER_ON_DURATION, DEFAULT_BUZZER_OFF_DURATION};
KalmanFilter filter {0.4, 60, 60, 0.1};

double lastDistance = 0;

bool outOfBounds = false;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    double distance = getDistance();

    if (distance < MAX_BEEP_DISTANCE && distance > MIN_BEEP_DISTANCE)
    {
        double normalDistance = (distance - MIN_BEEP_DISTANCE) / (MAX_BEEP_DISTANCE - MIN_BEEP_DISTANCE);

        if (normalDistance < SUPER_CLOSE_THRESHOLD)
        {
            buzzer.setOffDuration(0);
        }
        else 
        {
            buzzer.setOffDuration(long(normalDistance * BUZZER_FREQUENCY_SCALE));
        }

        buzzer.on();
    } 
    else 
    {
        buzzer.off();
    }

    buzzer.run();
    delay(LOOP_DELAY_MS);
}


// Logic
double getDistance()
{
    double distance = ultrasonic.getDistanceIn();

    if (distance == 0)
    {
        // Unable to get reading
        return lastDistance;
    }

    lastDistance = filter.filter((float) distance);
    return lastDistance;
}
