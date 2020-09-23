
#include "app_main.h"

#define FW "v1.0"

// extern unsigned char bilibili[];

uint8_t OLED_Status = 0;
extern bool doorStatus;

/* OLEDTask任务 */
QueueHandle_t OLEDhandle;
void OLEDTask(uint8_t parmToPass)
{
    OLED_Init();
    OLED_ColorTurn(0);   //0正常显示，1 反色显示
    OLED_DisplayTurn(0); //0正常显示 1 屏幕翻转显示
    OLED_Showxiaodianshi1();
    OLED_Refresh();

    vTaskDelay(2000 / portTICK_PERIOD_MS);

    for (;;)
    {
        static uint8_t count = 0;
        /* 先显示文字，显示后refresh，再显示图片 */
        vTaskDelay(50 / portTICK_PERIOD_MS);

        if (doorStatus)
            OLED_Status = 1;
        else
            OLED_Status = 2;

        xQueueReceiveFromISR(OLEDhandle, &OLED_Status, NULL);

        switch (OLED_Status)
        {
        case 1:
            OLED_ClearRectangularArea(0, 0, 128, 15);
            OLED_ShowString(0, 0, (uint8_t *)(&"LOCK OPEN"), 16);
            OLED_Status = 0;
            break;
        case 2:
            OLED_ClearRectangularArea(0, 0, 128, 15);
            OLED_ShowString(0, 0, (uint8_t *)(&"LOCK CLOSE"), 16);
            OLED_Status = 0;
            break;
        case 3:
            OLED_Refresh();
            OLED_ClearRectangularArea(0, 16, 127, 63);
            OLED_Showblack();
            OLED_Showok1();
            OLED_Status = 0;
            break;
        case 4:
            OLED_Refresh();
            OLED_ClearRectangularArea(0, 16, 127, 63);
            OLED_Showblack();
            OLED_Showno1();
            OLED_Status = 0;
            break;
        case 5:
            OLED_Refresh();
            OLED_ClearRectangularArea(0, 16, 127, 63);
            OLED_Showblack();
            OLED_Showxiaodianshi1();
            OLED_Status = 0;
            break;
        case 9:
            OLED_DisPlay_Off();
            OLED_Status = 0;
            break;
        case 10:
            OLED_DisPlay_On();
            OLED_Status = 0;
            break;
        default:
            break;
        }
    }
}
/* 创建OLEDTask任务 */
void CreateOLEDTask()
{
    OLEDhandle = xQueueCreate(10, sizeof(uint8_t));

    static uint8_t parmToPass;
    static TaskHandle_t oledTaskHandle = NULL;
    xTaskCreate(OLEDTask, &"oledTask", 2048, parmToPass, (UBaseType_t)7, oledTaskHandle);
}

/*
*
*  ******主函数******
*
*/
void app_main()
{
    GPIO_init();
    usr_uart_init();
    printf("UART Init OK\r\n");
    usr_uart_start();
    printf("UART Start OK\r\n");
    wifi_init_sta();
    printf("WIFI Init OK\r\n");
    CreateOLEDTask();
    printf("OLED Create OK\r\n");
    gpio_set_level(GPIO_NUM_2, 1);
    gpio_set_level(GPIO_NUM_4, 0);
    gpio_set_level(GPIO_NUM_5, 0);
    printf("GPIO Set OK\r\n");
    printf("********************* FW is %s ********************\r\n", FW);

    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
