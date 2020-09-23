#ifndef __F_S_MQTT_H_
#define __F_S_MQTT_H_

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "nvs.h"
#include "nvs_flash.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "mqtt_client.h"

#include "f_s_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event);
void mqtt_app_start(void);

#ifdef __cplusplus
}
#endif

#endif