#include "gomoku_game.h"
#include <Windows.h>

GomokuGame::GomokuGame(int size) : Game(size) { }

bool GomokuGame::isPlaceable(int x, int y) {
    if (isExist(x, y)) {
        // Already exists
        MessageBox(NULL, "�ش� ��ġ���� �̹� �ٸ� ���� �����մϴ�.", "���� ������ �� �����ϴ�.", MB_OK);
        return false;
    }
    return true;
}
