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
int v=0;

void app_main()
{
    serial.begin(9600);
    while(1){
        
    printf("Inicio\n");
    }
    
}