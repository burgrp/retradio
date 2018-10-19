#include "main.h"

//#define URL "http://icecast5.play.cz/cro3-128.mp3"
#define URL "http://167.114.244.122:80"

esp_err_t handle_http_event(esp_http_client_event_t *evt)
{
    if (evt->event_id == HTTP_EVENT_ON_DATA)
    {
        mp3_push_data(evt->data, evt->data_len);
    }
    return ESP_OK;
}

void http_fetch_task(void *param)
{
    while (true)
    {
        LOG_INFO("Checking Wi-Fi connection...");
        wifi_wait_connected();
        LOG_INFO("Connected");

        esp_http_client_config_t client_config = {
            .url = URL,
            .event_handler = handle_http_event,
        };
        esp_http_client_handle_t client = esp_http_client_init(&client_config);
        esp_err_t client_perform_error = esp_http_client_perform(client);

        if (client_perform_error == ESP_OK)
        {
            LOG_INFO("HTTP Status = %d, content_length = %d",
                     esp_http_client_get_status_code(client),
                     esp_http_client_get_content_length(client));
        }
        else
        {
            LOG_ERROR("client_perform_error %d", client_perform_error);
        }
        esp_http_client_cleanup(client);
    }
}

void http_init()
{
    xTaskCreate(http_fetch_task, "http_fetch_task", DEFAULT_STACK_SIZE, NULL, 0, NULL);
}
