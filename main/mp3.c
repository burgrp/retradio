#include "main.h"

unsigned char buffer[1024 * 20];
int head = 0;
int tail = 0; // = next free position
bool full = false;

static EventGroupHandle_t mp3_event_group;
const int CHECK_BUFFER_BIT = BIT0;

void log_buffer(char* condition) {
    LOG_INFO("MP3 buffer %s: %d-%d %s", condition, head, tail, full? " full": "");
}

void mp3_push_data(unsigned char* data, int len) {
    log_buffer("push enter");
    for (int c = 0; c < len; c++) {
        if (!full) {
            buffer[tail] = data[c];
            tail++;
            if (tail == sizeof(buffer)) {
                tail = 0;
            }
            if (tail == head) {
                full = true;
            }
        }
        if (full) {
            break;
        }
    }
    log_buffer("push exit");
    xEventGroupSetBits(mp3_event_group, CHECK_BUFFER_BIT);
}

void mp3_decoder_task(void *param)
{
    while (true) {
        xEventGroupWaitBits(mp3_event_group, CHECK_BUFFER_BIT, false, true, portMAX_DELAY);
        xEventGroupClearBits(mp3_event_group, CHECK_BUFFER_BIT);
        log_buffer("decode wake up");
    }
}

void mp3_init() {
    mp3_event_group = xEventGroupCreate();
    xTaskCreate(mp3_decoder_task, "mp3_decoder_task", DEFAULT_STACK_SIZE, NULL, 0, NULL);
}
