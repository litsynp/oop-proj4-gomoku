#ifndef _RENJU_GAME_
#define _RENJU_GAME_

#include "game.h"

class RenjuGame : public Game {
private:

public:
    RenjuGame(int size) : Game(size) { }

    virtual bool isPlaceable(int x, int y) {
        if (IsExist(x, y)) {
            printf("Already exist");
            return false;
        }
        if (this->getTurn() == BLACK_STONE) {
            if (IsDoubleFour(x, y)) {
                printf("4-4 금수 by renju rule");
                return false;
            }
            else if (IsDoubleThree(x, y)) {
                printf("3-3 금수 by renju rule");
                return false;
            }
            else if (IsSix(x, y)) {
                printf("6목이상 금수 by renju rule");
                return false;
            }
        }
        return true;
    }
};

#endif