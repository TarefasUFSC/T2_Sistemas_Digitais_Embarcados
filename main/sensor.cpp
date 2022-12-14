#include "sensor.hpp"
#include "esp_timer.h"
#include "delay.h"
#include "digital.h"
#include <stdio.h>

Sensor::Sensor(gpio_num_t TRIGGER_PIN, gpio_num_t ECHO_PIN){
    this->trigger = TRIGGER_PIN;
    this->echo = ECHO_PIN;
    digital.pinMode(TRIGGER_PIN, OUTPUT);
    digital.pinMode(ECHO_PIN, INPUT);
    digital.digitalWrite(TRIGGER_PIN, LOW);
    digital.digitalWrite(ECHO_PIN, LOW);
}

void Sensor::getPoint(int x){
    setPoint = x;
}

void Sensor::medeAltura(void){
    int64_t inicio = 0, fim = 0;
    digital.digitalWrite(this->trigger, HIGH);
    delay_us(20);
    digital.digitalWrite(this->trigger, LOW);

    while (digital.digitalRead(this->echo) == 0){}
    inicio = esp_timer_get_time();
    while (digital.digitalRead(this->echo) == 1){}
    fim = esp_timer_get_time();    

    int distancia = setPoint - ((fim - inicio) / 2 * 0.0343);
    printf("Distancia: %i \n", distancia);
}