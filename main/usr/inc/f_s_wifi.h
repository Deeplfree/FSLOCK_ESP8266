#ifndef __F_S_WIFI_
#define __F_S_WIFI_

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "nvs.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "oled.h"
#include "f_s_mqtt.h"

#define EXAMPLE_ESP_WIFI_SSID      "Y2"
#define EXAMPLE_ESP_WIFI_PASS      "1998...1998"
#define EXAMPLE_ESP_MAXIMUM_RETRY  10

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

static void event_handler(void *arg, esp_event_base_t event_base,
                          int32_t event_id, void *event_data);
void wifi_init_sta(void);

#endif