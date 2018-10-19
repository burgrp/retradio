#include "main.h"

#define MINIMP3_IMPLEMENTATION
#include "minimp3.h"

#define RX_BUFFER_SIZE 64 * 1024
#define DECODE_TRIGGER 8 * 1024

unsigned char buffer[RX_BUFFER_SIZE];
int size = 0;

static EventGroupHandle_t mp3_event_group;
const int DECODE_TRIGGER_BIT = BIT0;
const int BUFFER_ACCEPTING_BIT = BIT1;

static mp3dec_t mp3d;
short pcm[MINIMP3_MAX_SAMPLES_PER_FRAME];

void log_buffer(char *condition)
{
    //LOG_INFO("MP3 buffer %s: %d", condition, size);
}

void mp3_push_data(unsigned char *data, int len)
{
    xEventGroupWaitBits(mp3_event_group, BUFFER_ACCEPTING_BIT, false, true, portMAX_DELAY);

    log_buffer("before push");

    if (size + len > sizeof(buffer))
    {
        LOG_WARN("Buffer full");
    }

    for (int c = 0; c < len && size < sizeof(buffer); c++)
    {
        buffer[size++] = data[c];
    }
    log_buffer("after push");

    if (size > DECODE_TRIGGER)
    {
        xEventGroupSetBits(mp3_event_group, DECODE_TRIGGER_BIT);
    }
}

void mp3_decoder_task(void *param)
{
    while (true)
    {
        xEventGroupWaitBits(mp3_event_group, DECODE_TRIGGER_BIT, false, true, portMAX_DELAY);
        xEventGroupClearBits(mp3_event_group, DECODE_TRIGGER_BIT);

        mp3dec_frame_info_t info;
        memset(&info, 0, sizeof(info));

        log_buffer("before decode");

        int start = 0;
        do
        {
            int samples = mp3dec_decode_frame(&mp3d, &buffer[start], size - start, pcm, &info);
            LOG_INFO("MP3 decoder consumed %d from %d bytes in buffer, produced %d samples", info.frame_bytes, size, samples);
            start += info.frame_bytes;
        } while (info.frame_bytes);

        xEventGroupClearBits(mp3_event_group, BUFFER_ACCEPTING_BIT);
        for (int c = 0; c < size - start; c++)
        {
            buffer[c] = buffer[c + start];
        }
        size -= start;
        xEventGroupSetBits(mp3_event_group, BUFFER_ACCEPTING_BIT);

        log_buffer("after decode");
    }
}

void mp3_init()
{
    mp3dec_init(&mp3d);
    memset(&mp3d, 0, sizeof(mp3d));
    mp3_event_group = xEventGroupCreate();
    xEventGroupSetBits(mp3_event_group, BUFFER_ACCEPTING_BIT);
    xTaskCreate(mp3_decoder_task, "mp3_decoder_task", 30000, NULL, 0, NULL);
}
