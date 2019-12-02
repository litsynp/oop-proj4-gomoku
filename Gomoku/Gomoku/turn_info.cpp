#include "turn_info.h"

TurnInfo::TurnInfo(int x, int y, int turnNumber, Symbols whoseTurn) 
    : x(x), y(y), turnNumber(turnNumber), whoseTurn(whoseTurn) { }

int TurnInfo::getX() {
    return x;
}

int TurnInfo::getY() {
    return y;
}

int TurnInfo::getTurnNumber() {
    return turnNumber;
}

Symbols TurnInfo::getWhoseTurn() {
    return whoseTurn;
}