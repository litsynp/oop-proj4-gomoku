#include "normal_game.h"
#include <Windows.h>

NormalGame::NormalGame(int size) : Game(size) {
    // 콘솔창 이름 설정
    if (size == 15) {
        system("title OMOK GAME - Normal Rule (15 ×15)");
    }
    else {
        system("title OMOK GAME - Normal Rule (19 ×19)");
    }
}

bool NormalGame::isPlaceable(int x, int y) {
    if (isExist(x, y)) {
        // Already exists
        MessageBox(NULL, "해당 위치에는 이미 다른 돌이 존재합니다.", "돌을 착수할 수 없습니다.", MB_OK);
        return false;
    }
    if (isDoubleThree(x, y)) {
        // 3-3 금수 by normal rule
        MessageBox(NULL, "3-3 금수이므로 착수할 수 없습니다.", "돌을 착수할 수 없습니다.", MB_OK);
        return false;
    }
    return true;
}