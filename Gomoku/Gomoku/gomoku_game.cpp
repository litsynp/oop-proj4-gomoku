#include "gomoku_game.h"
#include <Windows.h>

GomokuGame::GomokuGame(int size) : Game(size) {
    // 콘솔창 이름 설정
    if (size == 15) {
        system("title OMOK GAME - Omok Rule (15 ×15)");
    }
    else {
        system("title OMOK GAME - Omok Rule (19 ×19)");
    }
}

bool GomokuGame::isPlaceable(int x, int y) {
    if (isExist(x, y)) {
        // Already exists
        MessageBox(NULL, "해당 위치에는 이미 다른 돌이 존재합니다.", "돌을 착수할 수 없습니다.", MB_OK);
        return false;
    }
    return true;
}
