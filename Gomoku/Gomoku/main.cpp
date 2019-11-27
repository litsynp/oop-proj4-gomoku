#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <ctime>

#include "game.h"
#include "game_rule.h"
#include "console_handler.h"

using namespace std;

int main(int argc, char** argv) {
    Game* game;                     // ���� �ڵ鷯
    bool exitGame = false;

    while (exitGame == false)
    {
        // �޴����� �������� ����
        // 1. �� ���� ����
        ConsoleHandler::showRuleMenu();
        int selectedRuleInMenu = ConsoleHandler::getRuleMenuInput();
        // 2. ���� ������ ����
        ConsoleHandler::showBoardSizeMenu();
        int selectedBoardSizeInMenu = ConsoleHandler::getBoardSizeMenuInput();

        int boardSize;             // ������ ũ��

        // ���õ� ���� ���ַ��� ���
        switch (selectedRuleInMenu) {
        case GameRule::NORMAL:
        case GameRule::GOMOKU:
        case GameRule::RENJU:
            if (selectedBoardSizeInMenu == 1) {
                boardSize = 15;
            }
            else {
                boardSize = 19;
            }

            game = new Game(boardSize);

            // ���� ����
            while (true) {
                game->update();
                game->render();
            }
            delete game;
            break; // ���� ��, �޴��� ���ư�
        }
    }
}