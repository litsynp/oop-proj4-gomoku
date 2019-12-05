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
        MessageBox(NULL, "Another stone already exists there.", "The stone cannot be placed.", MB_OK);
        return false;
    }
    if (isDoubleThree(x, y)) {
        // 3-3 금수 by normal rule
        MessageBox(NULL, "The stone cannot be placed there - by double threes (3-3).", "The stone cannot be placed.", MB_OK);
        return false;
    }
    return true;
}