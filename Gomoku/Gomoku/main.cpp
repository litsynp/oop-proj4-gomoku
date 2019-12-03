#include <iostream>

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
    bool exitProgram = false;       // ���α׷� ���� �÷���

    while (exitProgram == false) {
        int boardSize;             // ������ ũ��
        int selectedRuleInMenu;    // ������ ��

        // �޴����� �������� ����
        // 1. �� ���� ����
        while (true) {
            ConsoleHandler::showRuleMenu();
            selectedRuleInMenu = ConsoleHandler::getRuleMenuInput();
            if (selectedRuleInMenu == Keys::ESC) {
                // ESC �Ǵ� �����⸦ �������� ���
                // TODO ���� �޽��� ���
                exitProgram = true;
                break;
            }

            // 2. ���� ������ ����
            ConsoleHandler::showBoardSizeMenu();
            int selectedBoardSizeInMenu = ConsoleHandler::getBoardSizeMenuInput();

            // Ű���� �Է����� ���õ� ������ ũ�� ����
            if (selectedBoardSizeInMenu == 1) {
                boardSize = 15;
                break;
            }
            else if (selectedBoardSizeInMenu == 2) {
                boardSize = 19;
                break;
            }
            else {
                // ESC �Ǵ� �޴��� ���ư��⸦ �������� ���
                continue;
            }
        }

        // �� ���� ȭ�鿡�� ESC �Ǵ� �����⸦ �������� ��� ���α׷��� �ٷ� ����
        if (exitProgram == true) {
            break;
        }

        switch (selectedRuleInMenu) {
        case GameRule::NORMAL:
            game = new NormalGame(boardSize);
            break;
        case GameRule::GOMOKU:
            // ���õ� ���� ������� ���
            game = new GomokuGame(boardSize);
            break;
        default:
            // ���õ� ���� ���ַ��� ���
            game = new RenjuGame(boardSize);
        }

        bool exitGame = false;     // ���� ���� �÷���

        // ���� ����
        while (exitGame == false) {
            game->update();
            game->render();

            // ������ ����ƴ��� Ȯ��
            exitGame = game->isGameFinished();
        }
        delete game;
    }
}
