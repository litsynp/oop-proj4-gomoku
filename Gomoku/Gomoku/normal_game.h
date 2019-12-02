#ifndef _NORMAL_GAME_
#define _NORMAL_GAME_

#include "game.h"
#include <Windows.h>

class NormalGame : public Game {
private:

public:
    NormalGame(int size) : Game(size) { }

    virtual bool isPlaceable(int x, int y) {
        if (IsExist(x, y)) {
            MessageBox(NULL, "�ش� ��ġ���� �̹� �ٸ� ���� �����մϴ�.", "���� ������ �� �����ϴ�.", MB_OK);
            //printf("Already exist");
            return false;
        }
        if (IsDoubleThree(x, y)) {
            MessageBox(NULL, "3-3 �ݼ��̹Ƿ� ������ �� �����ϴ�.", "���� ������ �� �����ϴ�.", MB_OK);
            //printf("3-3 �ݼ� by normal rule");
            return false;
        }
        return true;
    }
};

#endif