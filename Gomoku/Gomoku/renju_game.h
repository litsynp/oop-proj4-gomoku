#ifndef _RENJU_GAME_
#define _RENJU_GAME_

#include "game.h"

class RenjuGame : public Game {
private:

public:
    RenjuGame(int size);
    virtual bool isPlaceable(int x, int y);
    virtual Symbols getWinner();
};

#endif