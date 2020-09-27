#include "f_s_mqtt.h"
#include <stdio.h>

extern void TimerCallback(void *arg);
extern void OpenDoor();
extern void CloseDoor();
extern void StartOTA();
extern void StopMQTT();

bool MQTT_Status = false;

static const char *TAG = "MQTT";

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id)
    {
    case MQTT_EVENT_BEFORE_CONNECT:
        break;
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        msg_id = esp_mqtt_client_publish(client, "FSLOCK", "FSLOCK CONNECTED OK", 0, 2, 0);
        ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
        MQTT_Status = true;

        // msg_id = esp_mqtt_client_subscribe(client, "/topic/qos0", 0);
        // ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

        // msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
        // ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

        // msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
        // ESP_LOGI(TAG, "sent unsubscribe successful, msg_id=%d", msg_id);

        msg_id = esp_mqtt_client_subscribe(client, "FSLOCK", 2);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        MQTT_Status = false;
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        msg_id = esp_mqtt_client_publish(client, "FSLOCK", "SUB THE FSLOCK OK", 0, 2, 0);
        ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
    {
        uint8_t mqttStatus = 0;
        char *open = &"QWEROPEN";
        char *close = &"QWERCLOSE";
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        printf("DATA=%s\r\n", event->data);
        if ((strncmp(event->data, open, event->data_len)) == 0)
        {
            printf("event->data == QWEROPEN\r\n");
            mqttStatus = 1;
        }
        else if ((strncmp(event->data, close, event->data_len)) == 0)
        {
            printf("event->data == QWERCLOSE\r\n");
            mqttStatus = 2;
        }
        else if ((strncmp(event->data, "QWEROTA", event->data_len) == 0))
        {
            StartOTA();
            // StopMQTT();
        }

        else
        {
            mqttStatus = 0;
            printf("event->data is wrong\r\n");
        }
        event->data = "";
        switch (mqttStatus)
        {
        case 1:
            OpenDoor();
            break;
        case 2:
            CloseDoor();
        default:
            break;
        }
        break;
    }
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        MQTT_Status = false;
        break;
    }
    return ESP_OK;
}

esp_mqtt_client_handle_t client;
void mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = "mqtt://139.155.83.114:1883",
        .event_handle = mqtt_event_handler,
        // .user_context = (void *)your_context
    };

    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);
}