#include "main.h"
#include "mad.h"


#define BUFFER_SIZE (20 * 1024)

unsigned char buffer[2][BUFFER_SIZE];
int size[2];
int inBuffer = 0; 

#define outBuffer (~inBuffer & 1)

static EventGroupHandle_t mp3_event_group;
const int CHECK_BUFFER_BIT = BIT0;

void log_buffer(char *condition)
{
    LOG_INFO("MP3 buffer %s: IN(%d):%d OUT(%d):%d", condition, inBuffer, size[inBuffer], outBuffer, size[outBuffer]);
}

void mp3_push_data(unsigned char *data, int len)
{
    log_buffer("push enter");

    for (int c = 0; c < len && size[inBuffer] < BUFFER_SIZE; c++)
    {
        buffer[inBuffer][size[inBuffer]++] = data[c];
    }
    log_buffer("push exit");
    if (size[inBuffer] > 2000) {
        xEventGroupSetBits(mp3_event_group, CHECK_BUFFER_BIT);
    }
}

unsigned char out_buffer[sizeof(buffer)];

static enum mad_flow mp3_decoder_input(void *data, struct mad_stream *stream)
{
    LOG_INFO("MP3 input");
    xEventGroupWaitBits(mp3_event_group, CHECK_BUFFER_BIT, false, true, portMAX_DELAY);
    xEventGroupClearBits(mp3_event_group, CHECK_BUFFER_BIT);
    
    log_buffer("MP3 input - pull enter");

    inBuffer = outBuffer;
    size[inBuffer] = 0;
    mad_stream_buffer(stream, buffer[outBuffer], size[outBuffer]);

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
