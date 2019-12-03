#include "normal_game.h"
#include <Windows.h>

NormalGame::NormalGame(int size) : Game(size) { }

bool NormalGame::isPlaceable(int x, int y) {
    if (IsExist(x, y)) {
        // Already exists
        MessageBox(NULL, "해당 위치에는 이미 다른 돌이 존재합니다.", "돌을 착수할 수 없습니다.", MB_OK);
        return false;
    }
    if (IsDoubleThree(x, y)) {
        // 3-3 금수 by normal rule
        MessageBox(NULL, "3-3 금수이므로 착수할 수 없습니다.", "돌을 착수할 수 없습니다.", MB_OK);
        return false;
    }
    return true;
}