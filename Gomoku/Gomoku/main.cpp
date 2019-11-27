#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <ctime>

#include "game.h"
#include "gomoku_game.h"
#include "normal_game.h"
#include "renju_game.h"

#include "console_handler.h"
#include "game_rule.h"
#include "keys.h"

using namespace std;

int main(int argc, char** argv) {
    Game* game;                     // ���� �ڵ鷯
    bool exitGame = false;

    while (exitGame == false) {
        // �޴����� �������� ����
        // 1. �� ���� ����
        ConsoleHandler::showRuleMenu();
        int selectedRuleInMenu = ConsoleHandler::getRuleMenuInput();
        if (selectedRuleInMenu == Keys::ESC) {
            // ESC �Ǵ� �����⸦ �������� ���
            // TODO ���� �޽��� ���
            break;
        }

        // 2. ���� ������ ����
        ConsoleHandler::showBoardSizeMenu();
        int selectedBoardSizeInMenu = ConsoleHandler::getBoardSizeMenuInput();

        // ���õ� ������ ũ�� ����
        int boardSize;             // ������ ũ��
        if (selectedBoardSizeInMenu == 1) {
            boardSize = 15;
        }
        else {
            boardSize = 19;
        }

        switch (selectedRuleInMenu) {
        case GameRule::NORMAL:
            game = new NormalGame(boardSize);
        case GameRule::GOMOKU:
            // ���õ� ���� ������� ���
            game = new GomokuGame(boardSize);
        default:
            // ���õ� ���� ���ַ��� ���
            game = new RenjuGame(boardSize);
        }

        // ���� ����
        while (true) {
            game->update();
            game->render();
        }
        delete game;
        break; // ���� ��, �޴��� ���ư�
    }
}