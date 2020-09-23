#ifndef __DELAY_H_
#define __DELAY_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "esp_log.h"
#include "esp_system.h"

void delay_50ms();
void delay_50x_ms(uint16_t n);

#endif