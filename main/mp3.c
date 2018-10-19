#include "main.h"

#define MINIMP3_IMPLEMENTATION
#include "minimp3.h"

unsigned char buffer[1024 * 20];
int size = 0;

static EventGroupHandle_t mp3_event_group;
const int CHECK_BUFFER_BIT = BIT0;
const int BUFFER_ACCEPTING_BIT = BIT1;

static mp3dec_t mp3d;

void log_buffer(char *condition)
{
    LOG_INFO("MP3 buffer %s: %d", condition, size);
}

void mp3_push_data(unsigned char *data, int len)
{
    xEventGroupWaitBits(mp3_event_group, BUFFER_ACCEPTING_BIT, false, true, portMAX_DELAY);

    log_buffer("push enter");
    for (int c = 0; c < len && size < sizeof(buffer); c++)
    {
        buffer[size++] = data[c];
    }
    log_buffer("push exit");

    if (size > 16000)
    {
        xEventGroupSetBits(mp3_event_group, CHECK_BUFFER_BIT);
    }
}

void mp3_decoder_task(void *param)
{
    while (true)
    {
        xEventGroupWaitBits(mp3_event_group, CHECK_BUFFER_BIT, false, true, portMAX_DELAY);
        xEventGroupClearBits(mp3_event_group, CHECK_BUFFER_BIT);

        log_buffer("MP3 input - pull enter");

        mp3dec_frame_info_t info;
        short pcm[MINIMP3_MAX_SAMPLES_PER_FRAME];
        int samples = mp3dec_decode_frame(&mp3d, buffer, size, pcm, &info);
        LOG_INFO("MP3 decoder consumed %d bytes, produced %d samples", info.frame_bytes, samples);

        xEventGroupClearBits(mp3_event_group, BUFFER_ACCEPTING_BIT);
        for (int c = info.frame_bytes; c < size; c++) {
            buffer[c - info.frame_bytes] = buffer[c];
        }
        xEventGroupSetBits(mp3_event_group, BUFFER_ACCEPTING_BIT);
        log_buffer("MP3 input - pull exit");
    }
}

void mp3_init()
{
    mp3dec_init(&mp3d);
    xEventGroupSetBits(mp3_event_group, BUFFER_ACCEPTING_BIT);
    mp3_event_group = xEventGroupCreate();
    xTaskCreate(mp3_decoder_task, "mp3_decoder_task", DEFAULT_STACK_SIZE, NULL, 0, NULL);
}
