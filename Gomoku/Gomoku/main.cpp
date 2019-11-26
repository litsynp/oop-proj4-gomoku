#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <ctime>

#include "game_rule.h"
#include "game.h"


using namespace std;

int main(int argc, char** argv) {
    int boardSize = 19;  // ������ ũ��
    Game* game;     // ���� �ڵ鷯
    clock_t curTime, oldTime;

    game = new Game(boardSize);
    game->printBoard();

    while (true) {
        oldTime = clock();
        game->update();
        game->render();

        // ȭ�� ������Ʈ �ð� ����
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
    //        // game->checkWinner(); // ���� �߽߰� ���� ����
    //    }
    //    delete game;
    //    // } // ���� ��, �޴��� ���ư�
    //}
}