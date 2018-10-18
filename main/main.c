#include "main.h"

void app_main()
{
    LOG_INFO("Retradio start");

    nvs_init();
    mp3_init();
    wifi_init();
    http_init();
}