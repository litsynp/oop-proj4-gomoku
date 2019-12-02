#ifndef _GOMOKU_GAME_
#define _GOMOKU_GAME_

#include "game.h"

class GomokuGame : public Game {
private:

public:
    GomokuGame(int size);
    virtual bool isPlaceable(int x, int y);
};

#endif