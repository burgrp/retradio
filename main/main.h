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
#include "driver/i2s.h"

extern const char* retradio_log_tag;

#define LOG_DEBUG(format, ...) ESP_LOGD(retradio_log_tag, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) ESP_LOGI(retradio_log_tag, format, ##__VA_ARGS__)
#define LOG_WARN(format, ...) ESP_LOGW(retradio_log_tag, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) ESP_LOGE(retradio_log_tag, format, ##__VA_ARGS__)
#define DEFAULT_STACK_SIZE 8192

void nvs_init();

void wifi_init();
void wifi_wait_connected();

void http_init();

void mp3_init();
void mp3_push_data(unsigned char* data, int len);

void pcm_init();
void pcm_push_data(int channels, int hz, short* data, int len);

#endif