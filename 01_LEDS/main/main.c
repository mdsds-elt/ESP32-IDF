/**************** MARCIA DE SA ****************/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#define LED 12
#define LED_V 14
#define LED_B 26

void LED_1()
{
    printf("LED V\n");
    gpio_set_level(LED, 1);
    vTaskDelay(2000 / portTICK_RATE_MS);
     gpio_set_level(LED, 0);
    vTaskDelay(2000 / portTICK_RATE_MS);
}

void LED_2()
{
    printf("LED on\n");
    gpio_set_level(LED_V, 1);
}

void LED_3()
{
    printf("LED VERMELHO\n");
    gpio_set_level(LED_B, 1);
    vTaskDelay(500 / portTICK_RATE_MS);
     gpio_set_level(LED_B, 0);
    vTaskDelay(500 / portTICK_RATE_MS);
}

void main_task(void *pvParameter)
{
    gpio_pad_select_gpio(LED);
    gpio_pad_select_gpio(LED_V);
    gpio_pad_select_gpio(LED_B);
    gpio_set_direction(LED, GPIO_MODE_INPUT_OUTPUT);
    gpio_set_direction(LED_V, GPIO_MODE_INPUT_OUTPUT);
    gpio_set_direction(LED_B, GPIO_MODE_INPUT_OUTPUT);

    while (1)
    {
        LED_1();
        LED_2();
        LED_3();
    }
}

void app_main()
{
    nvs_flash_init();
    xTaskCreate(&main_task, "main_task", 2048, NULL, 5, NULL);
}

