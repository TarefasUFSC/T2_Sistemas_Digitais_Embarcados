#include <stdio.h>
#include <map>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "serial.hpp"
#include <inttypes.h>
#include "sensor.hpp"
#include "digital.h"

using namespace std;

extern "C" void app_main();
int v = 0;


Sensor sensor = Sensor(PIN16, PIN5);

void printMenu(){
    
    printf(" \n");
    printf("[1] - Ajusta set point\n");
    printf("[2] - Mede altura\n");
}

void ajustaSetPoint()
{
    printf("Ajustando SetPoint\n");
    printf("Voce quer ajustar o set point de modo manual?\n");
    printf("[S]im\n");
    printf("[N]ao\n");
    char choice[1];
    serial.readString((uint8_t *)choice, 1);
    if(choice[0] == 'S' || choice[0] == 's'){
        printf("A distancia máxima é de 300cm\n");
        printf("Digite o novo set point: ");
        char newSetPointStr[3];
        serial.readString((uint8_t *)newSetPointStr, 3);
        int newSetPoint = atof(newSetPointStr);
        printf("Novo set point: %d\n", newSetPoint);
        sensor.setupBaseHeight(newSetPoint);
    }
    else if(choice[0] == 'N' || choice[0] == 'n'){
        printf("Set point sendo definido de forma automatica...\n");
        int newSetPoint = sensor.getDistance();
        printf("Novo set point: %d\n", newSetPoint);
        sensor.setupBaseHeight(newSetPoint);
    }
    else{
        printf("Opcao invalida\n");
    }

}
void medeAltura()
{
    printf("Mede Altura\n");
    int altura = sensor.getDistance();
    printf("Altura: %d\n", altura);

}



void app_main()
{
    serial.begin(9600);

    typedef void (*funcP)();
    map<char, funcP> myMap;
    myMap['1'] = ajustaSetPoint;
    myMap['2'] = medeAltura;
    sensor.init();
    while (1)
    {
        printMenu();

        char choice[1] ;
        serial.readString((uint8_t *)choice, 1);
        if (myMap.find(choice[0]) != myMap.end())
        {
            printf("choice: %c\n", choice[0]);
            myMap[choice[0]]();
        }
        else
        {
            printf("Opcao invalida\n\n\n");
        }
    }
}