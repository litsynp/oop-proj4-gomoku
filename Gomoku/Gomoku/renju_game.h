#ifndef _RENJU_GAME_
#define _RENJU_GAME_

#include "game.h"

class RenjuGame : public Game {
private:

public:
    RenjuGame(int size) : Game(size) { }

    virtual bool isPlaceable(int x, int y) {
        // Some rules ...
        return true;
    }
};

#endif