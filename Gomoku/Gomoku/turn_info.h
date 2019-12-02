#ifndef _TURN_INFO_
#define _TURN_INFO_

#include "symbols.h"

// placeStone() 함수로 돌을 착수하면 Vector에 저장되는 착수된 내용을 담은 클래스
class TurnInfo {
private:
    int x;               // 오목판에서의 착수 위치
    int y;
    int turnNumber;      // 몇 번째 턴인지 저장
    Symbols whoseTurn;   // 누구의 턴인지 저장 (백/흑)
public:
    TurnInfo(int x, int y, int turnNumber, Symbols whoseTurn);
    
    // getters
    int getX();
    int getY();
    int getTurnNumber();
    Symbols getWhoseTurn();
};

#endif