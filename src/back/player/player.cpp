#include "player.h"
#include "../utils/log.h"
#include <queue>
#include "jack_client.h"

using namespace pypp;
using namespace std;

Player* Player::getInstance() {
    static Player _instance;
    return &_instance;
}

Player::Player() = default;

unsigned long Player::getSampleRate() const {
    return _jackClient ? _jackClient->getSampleRate() : 0L;
}

Player::~Player() {
    delete _jackClient;
    delete _effectsList;
}

void Player::init() {
    Log::write("Player init", Log::info_t);

    _jackClient = new JackClient();
    _jackClient->setup(_effectsList);

    _jackClient->start();
}

const EffectsList* Player::getEffectsList() const {
    return _effectsList;
}
