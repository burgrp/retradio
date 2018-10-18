#ifndef INC_APPLICATION_MAIN_H
#define INC_APPLICATION_MAIN_H

#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "esp_event_loop.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_http_client.h"

extern const char* retradio_log_tag;

#define LOG_INFO(format, ...) ESP_LOGI(retradio_log_tag, format, ##__VA_ARGS__)
#define DEFAULT_STACK_SIZE 8192

void init_nvs();
void init_wifi();
void wifi_wait_connected();
void init_http();



#endif