#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <ctime>

#include "game_rule.h"
#include "game.h"


using namespace std;

int main(int argc, char** argv) {
    int boardSize = 19;  // 오목판 크기
    Game* game;     // 게임 핸들러
    clock_t curTime, oldTime;

    game = new Game(boardSize);
    game->printBoard();

    while (true) {
        oldTime = clock();
        game->update();
        game->render();

        // 화면 업데이트 시간 조정
        while (true) {
            curTime = clock();
            if (curTime - oldTime > 33) {
                break;
            }
        }

    }

    delete game;
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