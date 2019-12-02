#include "normal_game.h"
#include <Windows.h>

NormalGame::NormalGame(int size) : Game(size) { }

bool NormalGame::isPlaceable(int x, int y) {
    if (IsExist(x, y)) {
        MessageBox(NULL, "�ش� ��ġ���� �̹� �ٸ� ���� �����մϴ�.", "���� ������ �� �����ϴ�.", MB_OK);
        //printf("Already exist");
        return false;
    }
    if (IsDoubleThree(x, y)) {
        MessageBox(NULL, "3-3 �ݼ��̹Ƿ� ������ �� �����ϴ�.", "���� ������ �� �����ϴ�.", MB_OK);
        //printf("3-3 �ݼ� by normal rule");
        return false;
    }
    return true;
}