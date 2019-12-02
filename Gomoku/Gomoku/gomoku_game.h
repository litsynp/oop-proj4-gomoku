#ifndef _GOMOKU_GAME_
#define _GOMOKU_GAME_

#include "game.h"
#include <Windows.h>

class GomokuGame : public Game {
private:

public:
    GomokuGame(int size) : Game(size) { }

    virtual bool isPlaceable(int x, int y) {
        if (IsExist(x, y)) {
            MessageBox(NULL, "�ش� ��ġ���� �̹� �ٸ� ���� �����մϴ�.", "���� ������ �� �����ϴ�.", MB_OK);
            //printf("Already exist");
            return false;
        }
        return true;
    }
};

#endif