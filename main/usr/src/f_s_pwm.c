#include "f_s_pwm.h"

//pwm_init(uint32_t period, uint32_t *duties, uint8_t channel_num, const uint32_t *pin_num);

#define PWM_PERIOD    (1000)

uint8_t channel_num = 1;
uint32_t duties[1] = {500};
const uint32_t pin_num[1] = {4};    //NodeMCU----D2

int16_t phase[1] = {0};

void usr_pwm_init()
{
    esp_err_t pwminit = pwm_init(PWM_PERIOD, duties, 1, pin_num);
    pwm_set_phases(phase);
   //  esp_err_t pwmphases = pwm_set_phases(phase);
    ESP_LOGI("PWM", "PWM_INIT");
    ESP_LOGI("PWM", "PWM_INIT: %d/n", pwminit);
   //  ESP_LOGI("PWM", "PWM_PHASES: %d/n", pwmphases);

    esp_err_t pwmstart = pwm_start();
    ESP_LOGI("PWM", "PWM_START");
    ESP_LOGI("PWM", "PWM_START: %d/n", pwmstart);
}

void usr_pwm_start()
{
}
