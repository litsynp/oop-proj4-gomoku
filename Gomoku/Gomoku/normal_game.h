#ifndef _NORMAL_GAME_
#define _NORMAL_GAME_

#include "game.h"

class NormalGame : public Game {
private:

public:
    NormalGame(int size);
    virtual bool isPlaceable(int x, int y);
};

#endif