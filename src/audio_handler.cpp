#include "audio_handler.h"

AudioHandler::AudioHandler() : initialized(false) {}

bool AudioHandler::init() {
    setupI2S();
    initialized = true;
    return true;
}

void AudioHandler::setupI2S() {
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = I2S_SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false,
        .tx_desc_auto_clear = true,
        .fixed_mclk = 0
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_SCK,
        .ws_io_num = I2S_WS,
        .data_out_num = I2S_SD,
        .data_in_num = I2S_PIN_NO_CHANGE
    };

    i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_PORT, &pin_config);
    i2s_zero_dma_buffer(I2S_PORT);
}

bool AudioHandler::startRecording() {
    if (!initialized) return false;
    i2s_start(I2S_PORT);
    return true;
}

bool AudioHandler::stopRecording() {
    if (!initialized) return false;
    i2s_stop(I2S_PORT);
    return true;
}

size_t AudioHandler::readAudio(uint8_t* buffer, size_t length) {
    if (!initialized) return 0;
    size_t bytesRead = 0;
    i2s_read(I2S_PORT, buffer, length, &bytesRead, portMAX_DELAY);
    return bytesRead;
}

bool AudioHandler::playTone(int frequency, int duration) {
    if (!initialized) return false;
    
    const int sampleRate = I2S_SAMPLE_RATE;
    const int samples = (sampleRate * duration) / 1000;
    int16_t* sampleBuffer = new int16_t[samples];
    
    for (int i = 0; i < samples; i++) {
        float angle = 2.0 * PI * frequency * i / sampleRate;
        sampleBuffer[i] = (int16_t)(sin(angle) * 10000);
    }
    
    size_t bytesWritten;
    i2s_write(I2S_PORT, sampleBuffer, samples * sizeof(int16_t), &bytesWritten, portMAX_DELAY);
    
    delete[] sampleBuffer;
    return true;
}

void AudioHandler::playNotification() {
    playTone(1000, 100);
    delay(50);
    playTone(1500, 100);
}

void AudioHandler::playConfirmation() {
    playTone(800, 100);
    delay(50);
    playTone(1200, 100);
    delay(50);
    playTone(1600, 100);
}

void AudioHandler::playError() {
    playTone(400, 200);
    delay(100);
    playTone(400, 200);
}
