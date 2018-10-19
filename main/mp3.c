#include "main.h"

#define MINIMP3_IMPLEMENTATION
#include "minimp3.h"

unsigned char buffer[1024 * 20];
int size = 0;

static EventGroupHandle_t mp3_event_group;
const int CHECK_BUFFER_BIT = BIT0;
const int BUFFER_ACCEPTING_BIT = BIT1;

static mp3dec_t mp3d;
short pcm[MINIMP3_MAX_SAMPLES_PER_FRAME];

void log_buffer(char *condition)
{
    LOG_INFO("MP3 buffer %s: %d", condition, size);
}

void mp3_push_data(unsigned char *data, int len)
{
    xEventGroupWaitBits(mp3_event_group, BUFFER_ACCEPTING_BIT, false, true, portMAX_DELAY);

    log_buffer("before push");
    for (int c = 0; c < len && size < sizeof(buffer); c++)
    {
        buffer[size++] = data[c];
    }
    log_buffer("after push");

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

        mp3dec_frame_info_t info;
        memset(&info, 0, sizeof(info));
        do
        {
            log_buffer("before decode");

            int samples = mp3dec_decode_frame(&mp3d, buffer, size, pcm, &info);
            LOG_INFO("MP3 decoder consumed %d bytes, produced %d samples", info.frame_bytes, samples);

            xEventGroupClearBits(mp3_event_group, BUFFER_ACCEPTING_BIT);
            for (int c = 0; c < info.frame_bytes; c++)
            {
                buffer[c] = buffer[c + info.frame_bytes];
            }
            size -= info.frame_bytes;
            xEventGroupSetBits(mp3_event_group, BUFFER_ACCEPTING_BIT);

            log_buffer("after decode");
        } while (info.frame_bytes);
        
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
