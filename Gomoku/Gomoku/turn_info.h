#ifndef _TURN_INFO_
#define _TURN_INFO_

#include "symbols.h"

// placeStone() �Լ��� ���� �����ϸ� Vector�� ����Ǵ� ������ ������ ���� Ŭ����
class TurnInfo {
private:
    int x;               // �����ǿ����� ���� ��ġ
    int y;
    int turnNumber;      // �� ��° ������ ����
    Symbols whoseTurn;   // ������ ������ ���� (��/��)
public:
    TurnInfo(int x, int y, int turnNumber, Symbols whoseTurn);
    
    // getters
    int getX();
    int getY();
    int getTurnNumber();
    Symbols getWhoseTurn();
};

#endif