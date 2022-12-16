#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <inttypes.h>
#include <sys/time.h>
#include <string.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "serial.hpp"
#include "delay.h"
#include "digital.h"

class Sensor
{
private:
    gpio_num_t triggerPin;
    gpio_num_t echoPin;
    int baseSensorHeight;

public:
    Sensor(gpio_num_t triggerPin, gpio_num_t echoPin, int baseSensorHeight);
    int pulseIn(gpio_num_t pin, int value);
    int calculateHeight(int option);
};