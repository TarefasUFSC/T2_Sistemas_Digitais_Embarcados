#include "sensor.hpp"
#include "digital.h"
#include "delay.h"
#include <time.h>
#include <sys/time.h>

#include "esp_timer.h"
#include "delay.h"
#include <inttypes.h>



Sensor::Sensor(gpio_num_t pino_trigger, gpio_num_t pino_echo)
{
    this->baseHeightSet = false;
    this->baseHeight = 0;
    this->trigPin = pino_trigger;
    this->echoPin = pino_echo;
}
void Sensor::init()
{

    digital.pinMode(this->trigPin, OUTPUT);
    digital.pinMode(this->echoPin, INPUT);
    digital.digitalWrite(this->trigPin, LOW);
}

void Sensor::setupBaseHeight(int newHeight)
{
    this->baseHeight = newHeight;
    this->baseHeightSet = true;
}
int Sensor::getTimeDelta()
{
    int t1 = esp_timer_get_time(); // pega o tempo atual em microsegundos
    int t2;
    int duracao = 0;
    this->waitPulseChangeTo(LOW);
    t2 = esp_timer_get_time();
    duracao = (t2 - t1);
    return duracao;
}
int Sensor::calculateDistance(int timeDelta)
{
    int distancia;
    distancia = ((timeDelta) / 2) / 29.1;
    return distancia;
}
void Sensor::waitPulseChangeTo(int targetState)
{
    while (digital.digitalRead(this->echoPin) != targetState)
    {
    }
}
void Sensor::triggerMeasurement()
{
    digital.digitalWrite(this->trigPin, HIGH);
    delay_us(10);
    digital.digitalWrite(this->trigPin, LOW);
}
int Sensor::convertToBaseHeight(int distance)
{
    if (this->baseHeightSet)
    {
        distance = distance - this->baseHeight;
    }
    return distance;
}
int Sensor::getDistance()
{
    // envia um pulso de 10us no pino trig
    this->triggerMeasurement();
    this->waitPulseChangeTo(HIGH);

    // mede o tempo que o pino echo ficou em HIGH

    int duracao = this->getTimeDelta();

    // calcula a distancia em cm
    int distancia = this->calculateDistance(duracao);
    distancia = this->convertToBaseHeight(distancia);
    return distancia;
}

Sensor::~Sensor()
{
}