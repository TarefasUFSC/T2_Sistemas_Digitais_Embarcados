#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "serial.hpp"
#include "delay.h"
#include <inttypes.h> 
#include "digital.h"
#include "esp_timer.h"
#include "sensor.hpp"

extern "C" void app_main();

void app_main(){
  delay_ms(2000);
  serial.begin(9600);
  printf("\n\nRODANDO\n\n");

  Sensor ultrasom(PIN16, PIN5);

  while (1){
    printf("----------MENU----------\n");
    printf("[1] Ajusta set point\n");
    printf("[2] Mede altura\n");
    printf("[3] Auto set point\n");
    printf("----------------------------\n");

    char input = serial.readChar();
    if(input == '1'){
      printf("Digite o set point em cm:\n");
      char setPoint[3];
      serial.readString((uint8_t *)setPoint, 3);
      printf("Novo set point: %s\n", setPoint);
      ultrasom.getPoint(atoi(setPoint));
    }
    else if(input == '2'){
      ultrasom.medeAltura();
    }
    else if(input == '3'){
      ultrasom.AutoSetPoint();
    }
    else{
      printf("Opcao invalida\n");
    }
   	vTaskDelay(2000/portTICK_PERIOD_MS);
  }
}

