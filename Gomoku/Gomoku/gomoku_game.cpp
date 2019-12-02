#include "gomoku_game.h"
#include <Windows.h>

GomokuGame::GomokuGame(int size) : Game(size) { }

bool GomokuGame::isPlaceable(int x, int y) {
    if (IsExist(x, y)) {
        MessageBox(NULL, "해당 위치에는 이미 다른 돌이 존재합니다.", "돌을 착수할 수 없습니다.", MB_OK);
        //printf("Already exist");
        return false;
    }
    return true;
}
