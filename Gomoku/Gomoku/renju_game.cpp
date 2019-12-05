#include "renju_game.h"
#include <Windows.h>

RenjuGame::RenjuGame(int size) : Game(size) {
    // 콘솔창 이름 설정
    if (size == 15) {
        system("title OMOK GAME - Renju Rule (15 ×15)");
    }
    else {
        system("title OMOK GAME - Renju Rule (19 ×19)");
    }
}

bool RenjuGame::isPlaceable(int x, int y) {
    if (isExist(x, y)) {
        // Already exists
        MessageBox(NULL, "Another stone already exists there.", "The stone cannot be placed.", MB_OK);
        return false;
    }
    if (this->getTurn() == BLACK_STONE) {
        if (isDoubleFour(x, y)) {
            // 4-4 금수 by renju rule
            MessageBox(NULL, "The stone cannot be placed there - by double fours (4-4).", "The stone cannot be placed.", MB_OK);
            return false;
        }
        else if (isDoubleThree(x, y)) {
            // 3-3 금수 by Renju rule
            MessageBox(NULL, "The stone cannot be placed there - by double threes (3-3).", "The stone cannot be placed.", MB_OK);
            return false;
        }
        else if (isSix(x, y)) {
            // 6목 이상 금수 by Renju rule
            MessageBox(NULL, "The stone cannot be placed there - by overline. (rows of 6 or more - 6 MOK)", "The stone cannot be placed.", MB_OK);
            return false;
        }
    }
    return true;
}

Symbols RenjuGame::getWinner() {
    Symbols curTurn = getTurn();
    int boardX = getSelectedBoardX();
    int boardY = getSelectedBoardY();

    // 흑백 상관없이 5가 완성되거나, 백돌일 경우 장목을 허용
    if (isFive(boardX, boardY) 
        || (curTurn == WHITE_STONE && isSix(boardX, boardY))) {
        // 승자가 결정된 경우
        return curTurn;
    }
    else {
        // 승패가 결정되지 않은 경우
        return Symbols::EMPTY;
    }
}