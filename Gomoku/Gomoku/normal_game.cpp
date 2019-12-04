#include "normal_game.h"
#include <Windows.h>

NormalGame::NormalGame(int size) : Game(size) { }

bool NormalGame::isPlaceable(int x, int y) {
    if (isExist(x, y)) {
        // Already exists
        MessageBox(NULL, "�ش� ��ġ���� �̹� �ٸ� ���� �����մϴ�.", "���� ������ �� �����ϴ�.", MB_OK);
        return false;
    }
    if (isDoubleThree(x, y)) {
        // 3-3 �ݼ� by normal rule
        MessageBox(NULL, "3-3 �ݼ��̹Ƿ� ������ �� �����ϴ�.", "���� ������ �� �����ϴ�.", MB_OK);
        return false;
    }
    return true;
}