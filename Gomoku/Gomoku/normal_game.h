#ifndef _NORMAL_GAME_
#define _NORMAL_GAME_

#include "game.h"

class NormalGame : public Game {
private:
public:
    NormalGame(int size) : Game(size) { }

    virtual bool isPlaceable(int x, int y) {
        // Some rules ...
		if (IsExist(x, y)) {
			printf("Already exist");
			return false;
		}
		if (IsDoubleThree(x, y)) {
			printf("3-3 ±Ý¼ö by normal rule");
			return false;
		}
        return true;
    }
};

#endif