#ifndef PROJECT_PYPP_AUDIO_MESSAGE_QUEUE_H
#define PROJECT_PYPP_AUDIO_MESSAGE_QUEUE_H

#include <queue>

namespace pypp {

class AudioMessageQueue {
public:
    static AudioMessageQueue* getInstance();

    void push(float**);
    float** peek();
    float** pop();
private:
    AudioMessageQueue() = default;

    std::queue<float**> _queue;
};

}

#endif //PROJECT_PYPP_AUDIO_MESSAGE_QUEUE_H
