#ifndef _TIMER_
#define _TIMER_

#include <sys/time.h>
#include <inttypes.h>
#include <time.h>
#include "esp_timer.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "digital.h"
#include "timer.h"

unsigned long pulseIn(gpio_num_t pin, int value, unsigned long timeout)
{
  // Wait for the specified value on the pin
  while (digital.digitalRead(pin) != value)
  {
    if (timeout-- == 0)
    {
      return 0;
    }
  }

  // Measure the duration of the pulse
  unsigned long start = esp_timer_get_time();
  while (digital.digitalRead(pin) == value)
  {
    if (timeout-- == 0)
    {
      return 0;
    }
  }
  unsigned long end = esp_timer_get_time();

  return end - start;
};

#endif