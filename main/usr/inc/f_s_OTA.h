#ifndef __F_S_OTA_H_
#define __F_S_OTA_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "protocol_examples_common.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"

#include "f_s_mqtt.h"
#include "string.h"

esp_err_t _http_event_handler(esp_http_client_event_t *evt);
void simple_ota_example_task(void * pvParameter);
void StartOTA();

#endif