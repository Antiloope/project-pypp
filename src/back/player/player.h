#ifndef PROJECT_PYPP_PLAYER_H
#define PROJECT_PYPP_PLAYER_H

#include "effects_list.h"

namespace pypp {

class JackClient;

class Player {
public:
    static Player* getInstance();
    ~Player();

    void init();

    unsigned long getSampleRate() const;

    const EffectsList* getEffectsList() const;
private:
    Player();

    JackClient* _jackClient = nullptr;
    EffectsList* _effectsList = new EffectsList();
};

}

#endif //PROJECT_PYPP_PLAYER_H