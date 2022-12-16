#include "sensor.hpp"

Sensor::Sensor(gpio_num_t triggerPin, gpio_num_t echoPin, int baseSensorHeight)
{
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
    this->baseSensorHeight = baseSensorHeight;

    digital.pinMode(this->triggerPin, OUTPUT);
    digital.pinMode(this->echoPin, INPUT);
}

int Sensor::pulseIn(gpio_num_t pin, int value)
{
    // Wait for the specified value on the pin
    while (digital.digitalRead(pin) != value)
    {
    }

    // Measure the duration of the pulse
    int start = esp_timer_get_time();
    while (digital.digitalRead(pin) == value)
    {
    }
    int end = esp_timer_get_time();

    return end - start;
}

int Sensor::calculateHeight(int option)
{
    // Send a pulse to the trigger pin
    digital.digitalWrite(this->triggerPin, LOW);
    delay_ms(2);
    digital.digitalWrite(this->triggerPin, HIGH);
    delay_ms(10);
    digital.digitalWrite(this->triggerPin, LOW);

    // Measure the duration of the pulse on the echo pin
    int duration = pulseIn(this->echoPin, HIGH);

    // Calculate the distance to the nearest object in centimeters
    int distance = duration / 2 * 0.0343;

    if (distance <= 0)
    {
        // Handle error case
        return -1;
    }

    if (option == 1)
    {
        // Use the measured distance to be the known height of the sensor
        return distance;
    }

    int height = this->baseSensorHeight - distance;

    return height;
}