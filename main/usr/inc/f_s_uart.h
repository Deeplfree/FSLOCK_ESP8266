#ifndef __F_S_UART_H_
#define __F_S_UART_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"
#include "esp_log.h"

#include "oled.h"

static void uart_event_task(void *p);
void usr_uart_init();
void usr_uart_start();

#endif