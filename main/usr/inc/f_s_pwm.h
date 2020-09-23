#ifndef __F_S_PWM_H_
#define __F_S_PWM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "esp_log.h"

#include "driver/pwm.h"

void usr_pwm_init();
void usr_pwm_start();

#endif