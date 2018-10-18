#include "main.h"
#include "mad.h"

unsigned char buffer[1024 * 20];
int head = 0;
int tail = 0; // = next free position
bool full = false;

static EventGroupHandle_t mp3_event_group;
const int CHECK_BUFFER_BIT = BIT0;

void log_buffer(char *condition)
{
    LOG_INFO("MP3 buffer %s: %d-%d %s", condition, head, tail, full ? " full" : "");
}

void mp3_push_data(unsigned char *data, int len)
{
    log_buffer("push enter");
    for (int c = 0; c < len; c++)
    {
        if (!full)
        {
            buffer[tail] = data[c];
            tail++;
            if (tail == sizeof(buffer))
            {
                tail = 0;
            }
            if (tail == head)
            {
                full = true;
            }
        }
        if (full)
        {
            break;
        }
    }
    log_buffer("push exit");
    xEventGroupSetBits(mp3_event_group, CHECK_BUFFER_BIT);
}

unsigned char out_buffer[sizeof(buffer)];

static enum mad_flow mp3_decoder_input(void *data, struct mad_stream *stream)
{
    LOG_INFO("MP3 input");
    xEventGroupWaitBits(mp3_event_group, CHECK_BUFFER_BIT, false, true, portMAX_DELAY);
    xEventGroupClearBits(mp3_event_group, CHECK_BUFFER_BIT);
    
    log_buffer("MP3 input - pull enter");

    int c = 0;
    while(head != tail || full) {
        out_buffer[c] = buffer[head];
        c++;
        head++;
        if (head == sizeof(buffer)) {
            head = 0;
        }
    }

    log_buffer("MP3 input - pull exit");

    mad_stream_buffer(stream, out_buffer, c);

    return MAD_FLOW_CONTINUE;
}

static enum mad_flow mp3_decoder_output(void *data,
                            struct mad_header const *header,
                            struct mad_pcm *pcm)
{

    // unsigned int samplerate;		/* sampling frequency (Hz) */
    // unsigned short channels;		/* number of channels */
    // unsigned short length;		/* number of samples per channel */

    LOG_INFO("MP3 output: samplerate %d, channels %hu, length %hu", pcm->samplerate, pcm->channels, pcm->length);

    //   for (int s = 0; s < pcm->length; s++) {
    //     for (int c = 0; c < pcm->channels; c++) {
    //       LOG(LL_INFO, ("%d %d", c, pcm->samples[c][s]));
    //     }
    //   }

    return MAD_FLOW_CONTINUE;
}

static enum mad_flow mp3_decoder_error(void *data, struct mad_stream *stream, struct mad_frame *frame)
{
    LOG_ERROR("MP3 decoder error 0x%x", stream->error);
    return MAD_FLOW_CONTINUE;
}

struct mad_decoder decoder;

void mp3_decoder_task(void *param)
{
    while (true)
    {
        int result = mad_decoder_run(&decoder, MAD_DECODER_MODE_SYNC);
        LOG_INFO("MP3 decoder exit code %d", result);
    }
}

void mp3_init()
{
    mp3_event_group = xEventGroupCreate();

    mad_decoder_init(
        &decoder,
        NULL, // data
        mp3_decoder_input,
        NULL, // header
        NULL, // filter
        mp3_decoder_output,
        mp3_decoder_error,
        NULL // message
    );

    xTaskCreate(mp3_decoder_task, "mp3_decoder_task", DEFAULT_STACK_SIZE, NULL, 0, NULL);
}
