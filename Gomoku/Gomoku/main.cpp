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
    Game* game;                     // 게임 핸들러
    bool exitProgram = false;       // 프로그램 종료 플래그

    while (exitProgram == false) {
        int boardSize;             // 오목판 크기
        int selectedRuleInMenu;    // 선택한 룰

        // 메뉴에서 선택지를 받음
        // 1. 룰 종류 선택
        while (true) {
            ConsoleHandler::showRuleMenu();
            selectedRuleInMenu = ConsoleHandler::getRuleMenuInput();
            if (selectedRuleInMenu == Keys::ESC) {
                // ESC 또는 나가기를 선택했을 경우
                // TODO 종료 메시지 출력
                exitProgram = true;
                break;
            }

            // 2. 보드 사이즈 선택
            ConsoleHandler::showBoardSizeMenu();
            int selectedBoardSizeInMenu = ConsoleHandler::getBoardSizeMenuInput();

            // 키보드 입력으로 선택된 오목판 크기 설정
            if (selectedBoardSizeInMenu == 1) {
                boardSize = 15;
                break;
            }
            else if (selectedBoardSizeInMenu == 2) {
                boardSize = 19;
                break;
            }
            else {
                // ESC 또는 메뉴로 돌아가기를 선택했을 경우
                continue;
            }
        }

        // 룰 설정 화면에서 ESC 또는 나가기를 선택했을 경우 프로그램을 바로 종료
        if (exitProgram == true) {
            break;
        }

        switch (selectedRuleInMenu) {
        case GameRule::NORMAL:
            game = new NormalGame(boardSize);
            break;
        case GameRule::GOMOKU:
            // 선택된 룰이 오목룰일 경우
            game = new GomokuGame(boardSize);
            break;
        default:
            // 선택된 룰이 렌주룰일 경우
            game = new RenjuGame(boardSize);
        }

        bool exitGame = false;     // 게임 종료 플래그

        // 게임 진행
        while (exitGame == false) {
            game->update();
            game->render();

            // 게임이 종료됐는지 확인
            exitGame = game->isGameFinished();
        }
        delete game;
    }
}
