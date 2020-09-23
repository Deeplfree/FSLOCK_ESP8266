#include "f_s_uart.h"

#define EX_UART_NUM UART_NUM_0
#define BUF_SIZE (1024)
#define READ_BUF_SIZE (1024)

static QueueHandle_t uart0_queue;

uint8_t *uart_read_buf = &"No Received";
uint8_t queRenMa = 0xFF;

static void uart_event_task(void *p)
{
#define TAG "UART"

    uart_event_t uart_event;
    uint8_t *dtmp = (uint8_t *)malloc(READ_BUF_SIZE);

    for (;;)
    {
        if (xQueueReceive(uart0_queue, (void *)&uart_event, (portTickType)portMAX_DELAY))
        {
            bzero(dtmp, READ_BUF_SIZE);
            // ESP_LOGI(TAG, "uart[%d] event:", EX_UART_NUM);

            switch (uart_event.type)
            {
            // Event of UART receving data
            // We'd better handler data event fast, there would be much more data events than
            // other types of events. If we take too much time on data event, the queue might be full.
            case UART_DATA:
                // ESP_LOGI(TAG, "[UART DATA]: %d", uart_event.size);
                uart_read_bytes(EX_UART_NUM, dtmp, uart_event.size, portMAX_DELAY);
                if(dtmp != NULL) uart_read_buf = dtmp;

                unsigned char * ans = HEX_ToChar(uart_read_buf, uart_event.size);
                // OLED_ClearRectangularArea(0, 0, 127, 15);
                // OLED_ShowString(0, 0, (uint8_t *)(ans+12), 12);
                queRenMa = *(uart_read_buf + 9);
                switch (queRenMa)
                {
                case 0x00:
                    uart_read_buf = &"OK";
                    break;
                case 0x01:
                    uart_read_buf = &"Recive Error";
                    break;
                case 0x02:
                    uart_read_buf = &"No Finger";
                    break;
                case 0x03:
                    uart_read_buf = &"Scan Bad";
                    break;
                
                default:
                    uart_read_buf = &"QueRenMa Error";
                    break;
                }

                // ESP_LOGI(TAG, "[DATA EVT]:");
                // uart_write_bytes(EX_UART_NUM, (const char *) dtmp, uart_event.size);
                // break;

            // Event of HW FIFO overflow detected
            case UART_FIFO_OVF:
                // ESP_LOGI(TAG, "hw fifo overflow");
                // If fifo overflow happened, you should consider adding flow control for your application.
                // The ISR has already reset the rx FIFO,
                // As an example, we directly flush the rx buffer here in order to read more data.
                uart_flush_input(EX_UART_NUM);
                xQueueReset(uart0_queue);
                break;

            // Event of UART ring buffer full
            case UART_BUFFER_FULL:
                // ESP_LOGI(TAG, "ring buffer full");
                // If buffer full happened, you should consider encreasing your buffer size
                // As an example, we directly flush the rx buffer here in order to read more data.
                //uart_flush_input(EX_UART_NUM);
                xQueueReset(uart0_queue);
                break;

            case UART_PARITY_ERR:
                // ESP_LOGI(TAG, "uart parity error");
                break;

            // Event of UART frame erroruart_read_buf
            case UART_FRAME_ERR:
                // ESP_LOGI(TAG, "uart frame error");
                break;

                // Othersuart_read_buf
                // ESP_LOGI(TAG, "uart event type: %d", uart_event.type);
                break;
            case UART_EVENT_MAX:
                break;
            }
        }
    }

    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
}

void usr_uart_init()
{
    // Configure parameters of an UART driver,
    // communication pins and install the driver
    uart_config_t uart_config = {
        .baud_rate = 57600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};
    uart_param_config(EX_UART_NUM, &uart_config);

    // Install UART driver, and get the queue.
    uart_driver_install(EX_UART_NUM, BUF_SIZE * 2, BUF_SIZE * 2, 100, &uart0_queue, 0);
}

void usr_uart_start()
{
    // Create a task to handler UART event from ISR
    xTaskCreate(uart_event_task, "uart_event_task", 2048, NULL, 12, NULL);
}
