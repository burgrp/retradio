#include "main.h"

void app_main()
{
    LOG_INFO("Retradio start");

    init_nvs();
    init_wifi();
    init_http();
}