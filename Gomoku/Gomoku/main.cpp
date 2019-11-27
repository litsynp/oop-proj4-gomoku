#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <ctime>

#include "game.h"
#include "game_rule.h"
#include "console_handler.h"

using namespace std;

int main(int argc, char** argv) {
    Game* game;                     // 게임 핸들러
    bool exitGame = false;

    while (exitGame == false)
    {
        // 메뉴에서 선택지를 받음
        // 1. 룰 종류 선택
        ConsoleHandler::showRuleMenu();
        int selectedRuleInMenu = ConsoleHandler::getRuleMenuInput();
        // 2. 보드 사이즈 선택
        ConsoleHandler::showBoardSizeMenu();
        int selectedBoardSizeInMenu = ConsoleHandler::getBoardSizeMenuInput();

        int boardSize;             // 오목판 크기

        // 선택된 룰이 렌주룰일 경우
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

            // 게임 진행
            while (true) {
                game->update();
                game->render();
            }
            delete game;
            break; // 게임 끝, 메뉴로 돌아감
        }
    }
}