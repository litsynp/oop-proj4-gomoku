#include <iostream>
#include <cstdlib>
#include <Windows.h>

#include "game_rule.h"
#include "game.h"

using namespace std;

int main(int argc, char** argv) {
    int boardSize;  // 오목판 크기
    Game* game;     // 게임 핸들러

    game = new Game(19);
    game->printBoard();
    //while (true) {
    //    game->getKeyInput();
    //}

    //while (true) {
    //    // g.printMenuScreen();
    //    // g.getKeyboardInput();
    //    // g.update();
    //    // if (isSpacePressed && selected == RENJU_RULE) {
    //    boardSize = 19;
    //    game = new Game(boardSize);

    //    // game->update();
    //    while (true) {
    //        game->printBoard();
    //        // game->getKeyboardInput();
    //        // game->update();
    //        // game->checkWinner(); // 승자 발견시 게임 종료
    //    }
    //    delete game;
    //    // } // 게임 끝, 메뉴로 돌아감
    //}
}