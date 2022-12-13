#include "sensor.hpp"
#include "digital.h"
#include "delay.h"
#include <time.h>
#include <sys/time.h>

#include "esp_timer.h"
#include "delay.h"
#include <inttypes.h>

gpio_num_t trigPin;
gpio_num_t echoPin;

Sensor::Sensor(gpio_num_t pino_trigger, gpio_num_t pino_echo)
{
    this->baseHeightSet = false;
    this->baseHeight = 0;
    trigPin = pino_trigger;
    echoPin = pino_echo;
}
void Sensor::init()
{

    digital.pinMode(trigPin, OUTPUT);
    digital.pinMode(echoPin, INPUT);
    digital.digitalWrite(trigPin, LOW);
}

void Sensor::setupBaseHeight(int newHeight)
{
    this->baseHeight = newHeight;
    this->baseHeightSet = true;
}

int Sensor::getDistance()
{
    // envia um pulso de 10us no pino trig
    digital.digitalWrite(trigPin, HIGH);
    delay_us(10);
    digital.digitalWrite(trigPin, LOW);
    while (digital.digitalRead(echoPin) == LOW)
    {
    }

    // mede o tempo que o pino echo ficou em HIGH
    int t1 = esp_timer_get_time(); // pega o tempo atual em microsegundos

    int t2;
    int duracao = 0;
    while (digital.digitalRead(echoPin) == HIGH)
    {
    }
    t2 = esp_timer_get_time();
    duracao = (t2 - t1);
    // printf("duracao: %d \n", duracao);

    // calcula a distancia em cm
    int distancia;
    distancia = ((duracao) / 2) / 29.1;
    printf("distancia: %d \n", distancia);
    if (this->baseHeightSet)
    {
        distancia = this->baseHeight - distancia;
    }
    return distancia;
}

Sensor::~Sensor()
{
}