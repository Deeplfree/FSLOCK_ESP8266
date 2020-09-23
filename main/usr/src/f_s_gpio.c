#include "f_s_gpio.h"

extern uint8_t queRenMa;
extern QueueHandle_t OLEDhandle;

uint8_t timerStatus = 0;
uint16_t timerCount = 0;

// ESP_LOGI输出的标志字符
static const char *TAG = "GPIO_INIT";
static os_timer_t timer;
bool doorStatus = false; // false：门已锁 true：门已开
bool openAndCloseLock = false;

void MotorRun_Open()
{
    printf("MotorRun Open\r\n");
    gpio_set_level(GPIO_NUM_4, 1);
    gpio_set_level(GPIO_NUM_5, 0);
}

void MotorRun_Close()
{
    printf("MotorRun Close\r\n");
    gpio_set_level(GPIO_NUM_4, 0);
    gpio_set_level(GPIO_NUM_5, 1);
}

void MotorStop()
{
    printf("MotorStop\r\n");
    gpio_set_level(GPIO_NUM_4, 0);
    gpio_set_level(GPIO_NUM_5, 0);
}

void TimerCallback(void *arg)
{
    timerCount++;
    switch (timerStatus)
    {
    case 1:
        MotorRun_Open();
        timerStatus = 2;
        break;
    case 2:
        if (timerCount >= 250)
        {
            timerCount = 0;
            MotorStop();
            openAndCloseLock = false;
            timerStatus = 3;
        }
        break;
    case 3:
        if (timerCount >= 1000)
        {
            timerCount = 0;
            MotorRun_Close();
            timerStatus = 4;
        }
        break;
    case 4:
        if (timerCount >= 250)
        {
            timerCount = 0;
            MotorStop();
            openAndCloseLock = false;
            timerStatus = 0;
        }
        break;
    case 5:
        timerCount = 0;
        timerStatus = 3;
        break;
    case 0:
        printf("Timer Close\r\n");
        doorStatus = false;
        os_timer_disarm(&timer);
        break;

    default:
        break;
    }
}

void OpenDoor()
{
    if (doorStatus || openAndCloseLock)
        return;
    openAndCloseLock = true;
    timerStatus = 1;
    timerCount = 0;
    printf("Timer Enable Begin\r\n");
    os_timer_arm(&timer, 10, TimerRELOAD);
    printf("Timer Enable End\r\n");
    doorStatus = true;
}
void CloseDoor()
{
    if (!doorStatus || openAndCloseLock)
        return;
    openAndCloseLock = true;
    timerStatus = 3;
    timerCount = 1000 - 10;
    printf("Timer Enable Begin\r\n");
    os_timer_arm(&timer, 10, TimerRELOAD);
    printf("Timer Enable End\r\n");
    doorStatus = false;
}

// 实例化一个gpio事件队列的句柄
static xQueueHandle key_select_evt_queue = NULL;
// gpio_isr句柄，引用于 gpio_isr_handler_add 方法，将isr送至gpio事件队列
static void gpio_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t)arg;
    xQueueSendFromISR(key_select_evt_queue, &gpio_num, NULL);
}
// 中断服务程序，需要将此方法创建为一个FreeRTOS任务
static void gpio_task_interupt(void *arg)
{
    uint32_t io_num;
    uint8_t aaa = 3;
    for (;;)
    {
        bool isrStatus = false;
        if (xQueueReceive(key_select_evt_queue, &io_num, portMAX_DELAY) && !isrStatus) // io_num是否有中断
        // if (xQueueReceive(key_select_evt_queue, &io_num,10 / portTICK_PERIOD_MS10 / portTICK_PERIOD_MS 100 / portTICK_PERIOD_MS)) // io_num是否有中断
        {
            isrStatus = true;
            // xQueueSendFromISR(OLEDhandle, &aaa, NULL);

            ESP_LOGI(&"GPIO_INTR", "GPIO[%d] intr, val: %d\n", io_num, gpio_get_level(io_num));

            gpio_set_level(GPIO_NUM_2, 0);

            printf("VTaskDelay Begin\r\n");
            vTaskDelay(200 / portTICK_PERIOD_MS);
            printf("VTaskDelay End\r\n");

            uart_write_bytes(UART_NUM_0, (char *)Identify(), 12);

            printf("qurRenMa is : %d \r\n", queRenMa);
            printf("0xFF is : %d \r\n", 0xFF);
            while (queRenMa == 0xFF || queRenMa == 0x02)
            {
                static uint8_t fscount = 0;
                if (fscount >= 1)
                {
                    fscount = 0;
                    break;
                }
                fscount++;
                // os_delay_us(10000);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
            printf("qurRenMa is : %d \r\n", queRenMa);
            if (queRenMa == 0x00)
            // if (queRenMa == 0x00)
            {
                aaa = 1;
                xQueueSendFromISR(OLEDhandle, &aaa, NULL);
                aaa = 8;
                xQueueSendFromISR(OLEDhandle, &aaa, NULL);
                aaa = 3;
                xQueueSendFromISR(OLEDhandle, &aaa, NULL);
                OpenDoor();
                gpio_set_level(GPIO_NUM_2, 1);
                queRenMa = 0xFF;
            }
            else
            {
                aaa = 2;
                xQueueSendFromISR(OLEDhandle, &aaa, NULL);
                aaa = 8;
                xQueueSendFromISR(OLEDhandle, &aaa, NULL);
                aaa = 4;
                xQueueSendFromISR(OLEDhandle, &aaa, NULL);
                gpio_set_level(GPIO_NUM_2, 1);
                queRenMa = 0xFF;
            }

            // 清除中断队列，防止按键抖动导致的多次执行中断
            while (xQueueIsQueueEmptyFromISR(key_select_evt_queue) == pdFALSE)
            {
                printf("ISRQueue Clearing...\r\n");
                xQueueReceiveFromISR(key_select_evt_queue, &io_num, 100 / portTICK_PERIOD_MS);
            }
            printf("ISRQueue Clear OK\r\n");
            isrStatus = false;
        }
    }
}

/*
*
* ******gpio初始化函数******
*
*/
void GPIO_init()
{
    gpio_config_t io_cfg;

    // KEY_SELECT GPIO15 中断上升沿 输入
    io_cfg.intr_type = GPIO_INTR_NEGEDGE;
    io_cfg.mode = GPIO_MODE_INPUT;
    io_cfg.pin_bit_mask = GPIO_Pin_15;
    io_cfg.pull_down_en = 0;
    io_cfg.pull_up_en = 0;
    gpio_config(&io_cfg);

    // FS_Power GPIO02 FS模块电源控制端，低有效 输出
    io_cfg.intr_type = GPIO_INTR_DISABLE;
    io_cfg.mode = GPIO_MODE_OUTPUT_OD;
    io_cfg.pin_bit_mask = GPIO_Pin_2;
    io_cfg.pull_down_en = 0;
    io_cfg.pull_up_en = 0;
    gpio_config(&io_cfg);

    // GPIO04,05 电机驱动 A，B 输出
    io_cfg.intr_type = GPIO_INTR_DISABLE;
    io_cfg.mode = GPIO_MODE_OUTPUT_OD;
    io_cfg.pin_bit_mask = GPIO_Pin_4;
    io_cfg.pull_down_en = 0;
    io_cfg.pull_up_en = 0;
    gpio_config(&io_cfg);
    io_cfg.intr_type = GPIO_INTR_DISABLE;
    io_cfg.mode = GPIO_MODE_OUTPUT_OD;
    io_cfg.pin_bit_mask = GPIO_Pin_5;
    io_cfg.pull_down_en = 0;
    io_cfg.pull_up_en = 0;
    gpio_config(&io_cfg);

    // FS_WAK GPIO14 中断上升沿 输入
    io_cfg.intr_type = GPIO_INTR_POSEDGE;
    io_cfg.mode = GPIO_MODE_INPUT;
    io_cfg.pin_bit_mask = GPIO_Pin_14;
    io_cfg.pull_down_en = 0;
    io_cfg.pull_up_en = 1;
    gpio_config(&io_cfg);

    // AUTO_WAK GPIO16 自动复位唤醒低有效 输出
    io_cfg.intr_type = GPIO_INTR_DISABLE;
    io_cfg.mode = GPIO_MODE_OUTPUT;
    io_cfg.pin_bit_mask = GPIO_Pin_16;
    io_cfg.pull_down_en = 0;
    io_cfg.pull_up_en = 0;
    gpio_config(&io_cfg);

    // IIC SCL GPIO12 输出
    io_cfg.intr_type = GPIO_INTR_DISABLE;
    io_cfg.mode = GPIO_MODE_OUTPUT;
    io_cfg.pin_bit_mask = GPIO_Pin_12;
    io_cfg.pull_down_en = 0;
    io_cfg.pull_up_en = 0;
    gpio_config(&io_cfg);
    // IIC SDA GPIO13 输出
    io_cfg.intr_type = GPIO_INTR_DISABLE;
    io_cfg.mode = GPIO_MODE_OUTPUT;
    io_cfg.pin_bit_mask = GPIO_Pin_13;
    io_cfg.pull_down_en = 0;
    io_cfg.pull_up_en = 0;
    gpio_config(&io_cfg);

    //create a queue to handle gpio event from isr
    key_select_evt_queue = xQueueCreate(10, sizeof(uint32_t));

    //start gpio task
    xTaskCreate(gpio_task_interupt, "gpio_task_interupt", 2048, NULL, 10, NULL);

    //安装 isr 服务
    gpio_install_isr_service(0);

    // 将之前创建好的 gpio_isr 句柄添加进 isr 服务
    gpio_isr_handler_add(GPIO_NUM_15, gpio_isr_handler, (void *)GPIO_NUM_15);
    ESP_LOGI(&"GPIO_INIT", "GPIO_INIT_OK\n");

    os_timer_disarm(&timer);
    os_timer_setfn(&timer, TimerCallback, NULL);
    ESP_LOGI(&"Timer_INIT", "Timer_INIT_OK\n");
}
