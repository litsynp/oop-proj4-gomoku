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
        MessageBox(NULL, "Another stone already exists there.", "The stone cannot be placed.", MB_OK);
        return false;
    }
    return true;
}