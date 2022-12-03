#include <Arduino.h>
#include "driver/i2s.h"
#include <math.h>

#include "SampleSource.h"
#include "DACOutput.h"

// number of frames to try and send at once (a frame is a left and right sample)
#define NUM_FRAMES_TO_SEND 128

void i2sWriterTask(void *param)
{
    DACOutput *output = (DACOutput *)param;
    int availableBytes = 0;
    int buffer_position = 0;
    int read_frames = 0;
    Frame_t frames[128];
    while (true)
    {
        // pause output task if no audio source
        if (!output->m_sample_generator)
        {
            ESP_ERROR_CHECK(i2s_zero_dma_buffer(I2S_NUM_0));
            vTaskSuspend(NULL);
        }

        // wait for some data to be requested
        i2s_event_t evt;
        if (xQueueReceive(output->m_i2sQueue, &evt, portMAX_DELAY) == pdPASS)
        {
            if (evt.type == I2S_EVENT_TX_DONE)
            {
                size_t bytesWritten = 0;
                do
                {
                    if (availableBytes == 0)
                    {
                        // get some frames from the wave file - a frame consists of a 16 bit left and right sample
                        read_frames = output->m_sample_generator->getFrames(frames, NUM_FRAMES_TO_SEND);
                        // end playing if no more data
                        if (read_frames == 0)
                        {
                            delete output->m_sample_generator;
                            output->m_sample_generator = nullptr;
                            break;
                        }
                        // how many bytes do we now have to send
                        availableBytes = read_frames * sizeof(uint64_t);
                        // reset the buffer position back to the start
                        buffer_position = 0;
                    }
                    // do we have something to write?
                    if (availableBytes > 0)
                    {
                        // write data to the i2s peripheral
                        ESP_ERROR_CHECK(i2s_write(I2S_NUM_0, (uint8_t *)frames + buffer_position,
                                                  availableBytes, &bytesWritten, portMAX_DELAY));
                        availableBytes -= bytesWritten;
                        buffer_position += bytesWritten;
                    }
                    taskYIELD();
                } while (bytesWritten > 0);
            }
        }
        taskYIELD();
    }
}

void DACOutput::init(int pin_out)
{
    // i2s config for writing both channels of I2S
    i2s_config_t i2sConfig = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = 44100,   // we'll set this later
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_STAND_PCM_SHORT),
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 4,
        .dma_buf_len = 64,
        .use_apll = 0,
        .fixed_mclk = -1};

    i2s_pin_config_t pinConfig = {
        .mck_io_num = -1,
        .bck_io_num = -1,
        .ws_io_num = -1,
        .data_out_num = pin_out,
        .data_in_num = -1};

    // install and start i2s driver
    ESP_ERROR_CHECK(i2s_driver_install(I2S_NUM_0, &i2sConfig, 4, &m_i2sQueue));
    // set i2s pins
    ESP_ERROR_CHECK(i2s_set_pin(I2S_NUM_0, &pinConfig));
    // clear the DMA buffers
    ESP_ERROR_CHECK(i2s_zero_dma_buffer(I2S_NUM_0));
    // start a task to write samples to the i2s peripheral
    m_sample_generator = nullptr;
    xTaskCreatePinnedToCore(i2sWriterTask, "i2s Writer Task", 4096, this, 2, &m_i2sWriterTaskHandle, 0);
}

void DACOutput::start(SampleSource *sample_generator)
{
    if (sample_generator->valid())
    {
        m_sample_generator = sample_generator;
        ESP_ERROR_CHECK(i2s_set_sample_rates(I2S_NUM_0, m_sample_generator->sampleRate()));
        vTaskResume(m_i2sWriterTaskHandle);
    }
}

void DACOutput::pause()
{
    ESP_ERROR_CHECK(i2s_zero_dma_buffer(I2S_NUM_0));
    vTaskSuspend(m_i2sWriterTaskHandle);
}

void DACOutput::resume()
{
    vTaskResume(m_i2sWriterTaskHandle);
}

void DACOutput::stop()
{
    delete m_sample_generator;
    m_sample_generator = nullptr;
    vTaskSuspend(m_i2sWriterTaskHandle);
}