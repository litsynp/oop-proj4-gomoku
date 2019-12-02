#include "renju_game.h"
#include <Windows.h>

RenjuGame::RenjuGame(int size) : Game(size) { }

bool RenjuGame::isPlaceable(int x, int y) {
    if (IsExist(x, y)) {
        MessageBox(NULL, "해당 위치에는 이미 다른 돌이 존재합니다.", "돌을 착수할 수 없습니다.", MB_OK);
        return false;
    }
    if (this->getTurn() == BLACK_STONE) {
        if (IsDoubleFour(x, y)) {
            MessageBox(NULL, "4-4 금수이므로 착수할 수 없습니다.", "돌을 착수할 수 없습니다.", MB_OK);
            //printf("4-4 금수 by renju rule");
            return false;
        }
        else if (IsDoubleThree(x, y)) {
            MessageBox(NULL, "3-3 금수이므로 착수할 수 없습니다.", "돌을 착수할 수 없습니다.", MB_OK);
            //printf("3-3 금수 by renju rule");
            return false;
        }
        else if (IsSix(x, y)) {
            MessageBox(NULL, "6목 이상은 금수이므로 착수할 수 없습니다.", "돌을 착수할 수 없습니다.", MB_OK);
            //printf("6목이상 금수 by renju rule");
            return false;
        }
    }
    return true;
}