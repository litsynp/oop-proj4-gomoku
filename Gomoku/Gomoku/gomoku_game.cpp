#include "gomoku_game.h"
#include <Windows.h>

GomokuGame::GomokuGame(int size) : Game(size) { }

bool GomokuGame::isPlaceable(int x, int y) {
    if (IsExist(x, y)) {
        MessageBox(NULL, "�ش� ��ġ���� �̹� �ٸ� ���� �����մϴ�.", "���� ������ �� �����ϴ�.", MB_OK);
        //printf("Already exist");
        return false;
    }
    return true;
}
