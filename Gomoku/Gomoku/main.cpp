#include <iostream>
#include <cstdlib>
#include <Windows.h>

#include "game_rule.h"
#include "game.h"

using namespace std;

int main(int argc, char** argv) {
    int boardSize;  // ������ ũ��
    Game* game;     // ���� �ڵ鷯

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
    //        // game->checkWinner(); // ���� �߽߰� ���� ����
    //    }
    //    delete game;
    //    // } // ���� ��, �޴��� ���ư�
    //}
}