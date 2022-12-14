#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/uart.h"
#include "driver/gpio.h"

#include "digital.h"
#include "delay.h"

class Sensor
{
private:
    gpio_num_t trigPin;
    gpio_num_t echoPin;
    int baseHeight;
    bool baseHeightSet;

public:
    Sensor();
    Sensor(gpio_num_t pino_trigger, gpio_num_t pino_echo);
    ~Sensor();

    void init();
    void setupBaseHeight(int newHeight);
    int getDistance();

private:
    int getTimeDelta();
    int calculateDistance(int timeDelta);
    void waitPulseChangeTo(int targetState);
    void triggerMeasurement();
    int convertToBaseHeight(int distance);
};

#endif