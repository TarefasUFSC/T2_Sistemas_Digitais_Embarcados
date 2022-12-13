#include <stdio.h>
#include <map>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "serial.hpp"
#include <inttypes.h>

extern "C" void app_main();
int v = 0;

using namespace std;

void printMenu(){
    
    printf(" \n");
    printf("[1] - Ajusta set point\n");
    printf("[2] - Mede altura\n");
}

void ajustaSetPoint()
{
    printf("Ajusta SetPoint\n");
}
void medeAltura()
{
    printf("Mede Altura\n");
}



void app_main()
{
    serial.begin(9600);

    typedef void (*funcP)();
    map<char, funcP> myMap;
    myMap['1'] = ajustaSetPoint;
    myMap['2'] = medeAltura;

    while (1)
    {
        printMenu();

        char choice = serial.readChar();
        if (myMap.find(choice) != myMap.end())
        {
            printf("choice: %c\n", choice);
            myMap[choice]();
        }
        else
        {
            printf("Opcao invalida\n\n\n");
        }
    }
}