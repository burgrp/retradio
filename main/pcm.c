#include "main.h"

static const int i2s_num = 0;

static const i2s_config_t i2s_config = {
     .mode = I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN,
     .sample_rate = 44100,
     .bits_per_sample = 16, /* the DAC module will only take the 8bits from MSB */
     .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
     .communication_format = I2S_COMM_FORMAT_I2S_MSB,
     .intr_alloc_flags = 0, // default interrupt priority
     .dma_buf_count = 8,
     .dma_buf_len = 64,
     .use_apll = false
};

void pcm_init()
{
    i2s_driver_install(i2s_num, &i2s_config, 0, NULL);
    i2s_set_pin(i2s_num, NULL); //for internal DAC, this will enable both of the internal channels
    i2s_set_dac_mode(I2S_DAC_CHANNEL_BOTH_EN);
    
    i2s_set_sample_rates(i2s_num, 44100); 
}

void pcm_push_data(int channels, int hz, short* data, int len)
{
    size_t written = 0;
    //LOG_INFO("I2S write %d", len);
    for (int c = 0; c < len; c++) {
        data[c] = data[c] + 0x8000;
    }
    i2s_write(i2s_num, data, len, &written, portMAX_DELAY);    
    //LOG_INFO("I2S written %d", written);
}