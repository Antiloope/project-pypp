#include <jack/types.h>
#include <string>
#include "jack_client.h"
#include "../utils/log.h"
#include <jack/jack.h>
#include <jack/control.h>
#include "../utils/exception/exception.h"
#include "jack_callbacks.h"
#include "../utils/exception/log_exception.h"

using namespace std;
using namespace pypp;

const char* CLIENT_NAME = "project-pypp";

jack_port_t* stereoOutputPorts[2];
jack_port_t* stereoInputPorts[2];

void JackClient::setup(EffectsList* effectsList) {
    createClient();

    string jackClientName = jack_get_client_name(_jackClient);

    auto* jackCallbackParams = new JackCallbackParams{stereoOutputPorts, stereoInputPorts, effectsList};
    // Set client callbacks
    jack_set_process_callback(_jackClient, processCallback, jackCallbackParams);

    jack_on_shutdown(_jackClient, processShutdown, jackCallbackParams);

    // Crete ports
    stereoOutputPorts[Channel::Left] = jack_port_register (_jackClient, "LeftOutput",
                                                          JACK_DEFAULT_AUDIO_TYPE,
                                                          JackPortIsOutput, 0);

    stereoOutputPorts[Channel::Right] = jack_port_register (_jackClient, "RightOutput",
                                                           JACK_DEFAULT_AUDIO_TYPE,
                                                           JackPortIsOutput, 0);
    if (stereoOutputPorts[Channel::Left] == nullptr || stereoOutputPorts[Channel::Right] == nullptr)
        throw LogException("No more JACK ports available");

    stereoInputPorts[Channel::Left] = jack_port_register (_jackClient, "LeftInput",
                                                           JACK_DEFAULT_AUDIO_TYPE,
                                                           JackPortIsInput, 0);

    stereoInputPorts[Channel::Right] = jack_port_register (_jackClient, "RightInput",
                                                            JACK_DEFAULT_AUDIO_TYPE,
                                                           JackPortIsInput, 0);

    if (stereoInputPorts[Channel::Left] == nullptr || stereoInputPorts[Channel::Right] == nullptr)
        throw LogException("No more JACK ports available");

    // Activate client
    if (jack_activate(_jackClient))
        throw LogException("Cannot activate client");

    // Connect ports to outputPort strucure used to load buffers
    const char ** ports = jack_get_ports (
            _jackClient,
            nullptr,
            nullptr,
            JackPortIsPhysical|JackPortIsInput
    );

    if (ports == nullptr)
        throw LogException("No physical playback ports");

    if (jack_connect (_jackClient, jack_port_name (stereoOutputPorts[Channel::Right]), ports[Channel::Right]) ||
        jack_connect (_jackClient, jack_port_name (stereoOutputPorts[Channel::Left]), ports[Channel::Left]))
        throw LogException("Cannot connect output ports");

    free (ports);

    ports = jack_get_ports (
            _jackClient,
            nullptr,
            nullptr,
            JackPortIsPhysical|JackPortIsOutput
    );

    if (ports == nullptr)
        throw LogException("No physical record ports");

    if (jack_connect (_jackClient, ports[Channel::Right], jack_port_name (stereoInputPorts[Channel::Right])) ||
        jack_connect (_jackClient, ports[Channel::Left], jack_port_name (stereoInputPorts[Channel::Left])))
        throw LogException("Cannot connect input ports");

    free (ports);

    Log::write("Jack client connected.",Log::info_t);
}

void JackClient::start() {

}

long JackClient::getSampleRate() const {
    return _sampleRate;
}

void JackClient::createClient() {
    jack_options_t options = JackNullOption;
    jack_status_t status;

    _jackClient = jack_client_open(
            CLIENT_NAME,
            options,
            &status
    );

    if( _jackClient == nullptr ) {
        string log = "Error creating jack client. ";
        if( status & JackServerFailed )
            log.append("Status: JackServerFailed");
        Log::write(log, Log::error_t);
        throw Exception(log);
    }

    if( status & JackServerStarted )
        Log::write( "JACK server started. ", Log::info_t );

    if( status & JackNameNotUnique )
        Log::write( "Unique name asigned. ", Log::info_t );
}

JackClient::JackClient() {

}

JackClient::~JackClient() {
    delete _jackClient;
}
