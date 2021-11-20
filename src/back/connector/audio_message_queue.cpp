#include "audio_message_queue.h"

using namespace pypp;

AudioMessageQueue* AudioMessageQueue::getInstance() {
    static AudioMessageQueue _instance;
    return &_instance;
}

void AudioMessageQueue::push(float **) {

}

float **AudioMessageQueue::peek() {
    return nullptr;
}

float **AudioMessageQueue::pop() {
    return nullptr;
}
