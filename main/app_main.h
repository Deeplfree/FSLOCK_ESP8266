#ifndef __APP_MAIN_H_
#define __APP_MAIN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "esp_log.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "driver/uart.h"
// #include "driver/pwm.h"

#include "f_s_uart.h"
#include "f_s_gpio.h"
#include "oled.h"
#include "f_s_wifi.h"

void OLEDTask(uint8_t parmToPass);
void CreateOLEDTask();
void app_main();

#endif