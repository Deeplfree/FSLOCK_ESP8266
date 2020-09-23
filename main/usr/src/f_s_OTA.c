#include "f_s_OTA.h"

extern bool MQTT_Status;
extern esp_mqtt_client_handle_t client;

extern QueueHandle_t OLEDhandle;

TaskHandle_t stopMQTT = NULL;

static const char *TAG = "OTA";
extern const uint8_t server_cert_pem_start[] asm("_binary_ca_cert_pem_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_ca_cert_pem_end");

esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ERROR:
        ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
        // esp_mqtt_client_publish(client, "FSLOCK", "HTTP_EVENT_ERROR", 0, 2, 0);
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
        // esp_mqtt_client_publish(client, "FSLOCK", "HTTP_EVENT_ON_CONNECTED", 0, 2, 0);
        break;
    case HTTP_EVENT_HEADER_SENT:
        ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
        // esp_mqtt_client_publish(client, "FSLOCK", "HTTP_EVENT_HEADER_SENT", 0, 2, 0);
        break;
    case HTTP_EVENT_ON_HEADER:
    {
        ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
        char *s = "HTTP_EVENT_ON_HEADER, key=";
        strcat(s, evt->header_key);
        strcat(s, ", value=");
        strcat(s, evt->header_value);
        // esp_mqtt_client_publish(client, "FSLOCK", s, 0, 2, 0);
        break;
    }
    case HTTP_EVENT_ON_DATA:
    {
        ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
        char *s = "HTTP_EVENT_ON_DATA, len=";
        strcat(s, evt->data_len);
        // esp_mqtt_client_publish(client, "FSLOCK", s, 0, 2, 0);
        break;
    }
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
        // esp_mqtt_client_publish(client, "FSLOCK", "HTTP_EVENT_ON_FINISH", 0, 2, 0);
        break;
    case HTTP_EVENT_DISCONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_DISCONNECTED");
        // esp_mqtt_client_publish(client, "FSLOCK", "HTTP_EVENT_DISCONNECTED", 0, 2, 0);
        break;
    }
    return ESP_OK;
}

void simple_ota_example_task(void *pvParameter)
{
    ESP_LOGE(TAG, "6");

    static bool isMQTT = false;
    // if (MQTT_Status)
        // esp_mqtt_client_publish(client, "FSLOCK", "Starting OTA example...", 0, 2, 0);
        ESP_LOGI(TAG, "Starting OTA example...");
    ESP_LOGE(TAG, "7");

    esp_http_client_config_t config = {
        .url = CONFIG_FIRMWARE_UPGRADE_URL,
        .cert_pem = (char *)server_cert_pem_start,
        .event_handler = _http_event_handler,
    };
    esp_err_t ret = esp_https_ota(&config);
    ESP_LOGE(TAG, "8");
    if (ret == ESP_OK)
    {
        esp_restart();
    }
    else
    {
        ESP_LOGE(TAG, "Firmware Upgrades Failed");
        // esp_mqtt_client_publish(client, "FSLOCK", "Firmware Upgrades Failed", 0, 2, 0);
    }
    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void StartOTA()
{
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_LOGE(TAG, "1");
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_LOGE(TAG, "2");
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_LOGE(TAG, "3");

    ESP_ERROR_CHECK(example_connect());
    ESP_LOGE(TAG, "4");

    xTaskCreate(&simple_ota_example_task, "ota_example_task", 8192, NULL, 4, NULL);
    ESP_LOGE(TAG, "5");
    if (MQTT_Status)
    {
        // esp_mqtt_client_publish(client, "FSLOCK", "ota_example_task start", 0, 2, 0);
    }
}

// void StopMQTTtask()
// {
//     static uint8_t a = 0;
//     if(a == 0)
//     {
//     vTaskDelay(5000 / portTICK_PERIOD_MS);
//     // esp_mqtt_client_stop(client);
//     StartOTA();
//     vTaskDelay(5000 / portTICK_PERIOD_MS);
//     StartOTA();
//     vTaskDelay(5000 / portTICK_PERIOD_MS);
//     a = 1;
//     }
//     vTaskDelay(100 / portTICK_PERIOD_MS);
// }

// void StopMQTT()
// {
//     xTaskCreate(&StopMQTTtask, "StopMQTTtask", 1024, NULL, 5, stopMQTT);
// }