#ifndef PROJECT_PYPP_JACK_CALLBACKS_H
#define PROJECT_PYPP_JACK_CALLBACKS_H

#include <jack/types.h>
#include <vector>
#include <jack/jack.h>
#include <cstring>
#include "effects_list.h"

namespace pypp {

struct JackCallbackParams {
    jack_port_t** jackOutputPorts;
    jack_port_t** jackInputPorts;
    EffectsList* effectsList;
    void (*clientCallback)(jack_default_audio_sample_t*[2]);
};

enum Channel {
    Right = 0,
    Left = 1
};

int processCallback(jack_nframes_t nframes, void* params) {
    jack_default_audio_sample_t *out[2];
    jack_default_audio_sample_t *in[2];

    auto* jackCallbackParams = (JackCallbackParams*)params;

    out[0] = (jack_default_audio_sample_t*)
            jack_port_get_buffer(
                    jackCallbackParams->jackOutputPorts[Channel::Right],
                    nframes );

    out[1] = (jack_default_audio_sample_t*)
            jack_port_get_buffer(
                    jackCallbackParams->jackOutputPorts[Channel::Left],
                    nframes );

    in[0] = (jack_default_audio_sample_t*)
            jack_port_get_buffer(
                    jackCallbackParams->jackInputPorts[Channel::Right],
                    nframes );

    in[1] = (jack_default_audio_sample_t*)
            jack_port_get_buffer(
                    jackCallbackParams->jackInputPorts[Channel::Left],
                    nframes );

    memcpy(
            out[Channel::Right],
            in[Channel::Right],
            sizeof (jack_default_audio_sample_t) * nframes );

    memcpy(
            out[Channel::Left],
            in[Channel::Left],
            sizeof (jack_default_audio_sample_t) * nframes );

    jack_default_audio_sample_t *callbackBuffer[2];
    callbackBuffer[0] = new jack_default_audio_sample_t[nframes];
    callbackBuffer[1] = new jack_default_audio_sample_t[nframes];

    memcpy(
            callbackBuffer[Channel::Right],
            out[Channel::Right],
            sizeof (jack_default_audio_sample_t) * nframes );

    memcpy(
            callbackBuffer[Channel::Left],
            out[Channel::Left],
            sizeof (jack_default_audio_sample_t) * nframes );

    jackCallbackParams->clientCallback(callbackBuffer);

    return 0;
}

void processShutdown(void* params) {
    delete (JackCallbackParams*)params;
}

}

#endif //PROJECT_PYPP_JACK_CALLBACKS_H
