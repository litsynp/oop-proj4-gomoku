#ifndef _GOMOKU_GAME_
#define _GOMOKU_GAME_

#include "game.h"

class GomokuGame : public Game {
private:

public:
    GomokuGame(int size) : Game(size) { }

    virtual bool isPlaceable(int x, int y) {
        if (IsExist(x, y)) {
            printf("Already exist");
            return false;
        }
        return true;
    }
};

#endif