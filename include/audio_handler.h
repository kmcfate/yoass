#ifndef AUDIO_HANDLER_H
#define AUDIO_HANDLER_H

#include <Arduino.h>
#include <driver/i2s.h>
#include "config.h"

class AudioHandler {
private:
    bool initialized;
    void setupI2S();

public:
    AudioHandler();
    bool init();
    bool startRecording();
    bool stopRecording();
    size_t readAudio(uint8_t* buffer, size_t length);
    bool playTone(int frequency, int duration);
    void playNotification();
    void playConfirmation();
    void playError();
};

#endif // AUDIO_HANDLER_H
