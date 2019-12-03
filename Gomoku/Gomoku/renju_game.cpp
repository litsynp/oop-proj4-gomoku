#include "renju_game.h"
#include <Windows.h>

RenjuGame::RenjuGame(int size) : Game(size) { }

bool RenjuGame::isPlaceable(int x, int y) {
    if (IsExist(x, y)) {
        // Already exists
        MessageBox(NULL, "�ش� ��ġ���� �̹� �ٸ� ���� �����մϴ�.", "���� ������ �� �����ϴ�.", MB_OK);
        return false;
    }
    if (this->getTurn() == BLACK_STONE) {
        if (IsDoubleFour(x, y)) {
            // 4-4 �ݼ� by renju rule
            MessageBox(NULL, "4-4 �ݼ��̹Ƿ� ������ �� �����ϴ�.", "���� ������ �� �����ϴ�.", MB_OK);
            return false;
        }
        else if (IsDoubleThree(x, y)) {
            // 3-3 �ݼ� by Renju rule
            MessageBox(NULL, "3-3 �ݼ��̹Ƿ� ������ �� �����ϴ�.", "���� ������ �� �����ϴ�.", MB_OK);
            return false;
        }
        else if (IsSix(x, y)) {
            // 6�� �̻� �ݼ� by Renju rule
            MessageBox(NULL, "6�� �̻��� �ݼ��̹Ƿ� ������ �� �����ϴ�.", "���� ������ �� �����ϴ�.", MB_OK);
            return false;
        }
    }
    return true;
}