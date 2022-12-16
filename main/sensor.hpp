#ifndef __SENSOR__
#define __SENSOR__

#include <stdio.h>
#include "driver/gpio.h"

class Sensor{
private:
    gpio_num_t trigger;
    gpio_num_t echo;
    int setPoint = 300;
public:
    Sensor(gpio_num_t, gpio_num_t);
    void getPoint(int x);
    void medeAltura(void);
    void AutoSetPoint(void);
};

#endif