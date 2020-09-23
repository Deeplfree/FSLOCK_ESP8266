#ifndef __F_S_GPIO_H_
#define __F_S_GPIO_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"

#include "esp_log.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "f_s_communicat.h"
#include "oled.h"
#include "delay.h"

#define TimerONE_SHOT false // testing will be done without auto reload (one-shot)
#define TimerRELOAD true    // testing will be done with auto reload

#define KEY_SELECT GPIO_Pin_15
#define StopTimer (timerStatus = 0;)
#define RecountTimer (timerStatus = 5;)

void MotorRun_Open();
void MotorRun_Close();
void MotorStop();
void TimerCallback(void *arg);
static void gpio_isr_handler(void *arg);
static void gpio_task_interupt(void *arg);
void GPIO_init();

#endif