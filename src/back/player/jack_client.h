#ifndef PROJECT_PYPP_JACK_CLIENT_H
#define PROJECT_PYPP_JACK_CLIENT_H

#include "effects_list.h"
#include "jack/types.h"

namespace pypp {

class JackClient {
public:
    JackClient();
    ~JackClient();

    void setup(EffectsList*);
    void start();

    long getSampleRate() const;
private:
    void createClient();
    static void clientCallbackQueue(jack_default_audio_sample_t *[2]);

    long _sampleRate{};
    jack_client_t* _jackClient{};
};

}

#endif //PROJECT_PYPP_JACK_CLIENT_H
