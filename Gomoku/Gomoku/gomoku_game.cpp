#include "gomoku_game.h"
#include <Windows.h>

GomokuGame::GomokuGame(int size) : Game(size) {
    // �ܼ�â �̸� ����
    if (size == 15) {
        system("title OMOK GAME - Omok Rule (15 ��15)");
    }
    else {
        system("title OMOK GAME - Omok Rule (19 ��19)");
    }
}

bool GomokuGame::isPlaceable(int x, int y) {
    if (isExist(x, y)) {
        // Already exists
        MessageBox(NULL, "�ش� ��ġ���� �̹� �ٸ� ���� �����մϴ�.", "���� ������ �� �����ϴ�.", MB_OK);
        return false;
    }
    return true;
}
