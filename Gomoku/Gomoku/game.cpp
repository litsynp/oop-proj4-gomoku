#include "game.h"
#include "game_rule.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <conio.h>
#include <Windows.h>


Game::Game(int size) {
    // 콘솔창 설정
    system("title 오목 게임");// 콘솔창 이름 설정
    system("mode con: cols=100 lines=40"); // 콘솔 크기 설정

    // 콘솔 커서 숨기기
    CONSOLE_CURSOR_INFO cursorInfo = { 1, false };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // 커서 이동 한계 설정
    yBoundTop = 1;
    yBoundBtm = yBoundTop + size - 1;
    xBoundLft = 3;
    xBoundRgt = xBoundLft + (size) * 2;

    // 커서 위치 설정 및 선택된 보드 좌표 설정 (1:1 매칭)
    cursorY = (yBoundTop + yBoundBtm) / 2;
    cursorX = (xBoundLft + xBoundRgt) / 2;
    selectedBoardX = (yBoundTop + size) / 2;
    selectedBoardY = (xBoundLft - 2 + size) / 2;

    // 보드 생성
    this->size = size;
    board = new int* [size + 2]; // size는 15x15일 수도 있고 19x19일 수도 있음

    // e.g. size = 15 or 19
    for (int i = 0; i < size + 2; i++) {
        board[i] = new int[size + 2];
        memset(board[i], EMPTY, sizeof(int) * (size + 2)); // EMPTY로 초기화
    }

    // 벽에 WALL 값 대입
    for (int i = 0; i < size + 2; i++) {
        board[0][i] = WALL;
        board[size + 1][i] = WALL;
    }
    for (int i = 0; i < size + 2; i++) {
        board[i][0] = WALL;
        board[i][size + 1] = WALL;
    }

    // 현재 턴 설정
    turn = BLACK_STONE;
    placeStone((size + 1) / 2, (size + 1) / 2);

}

Game::~Game() {
    for (int i = 0; i < size + 2; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

void Game::update() {
    handleKeyInput();

}

void Game::render() {
    gotoxy(0, 0);
    printBoard();

    gotoxy(cursorX, cursorY);
    std::cout << "◎";
}

void Game::placeStone(int x, int y) {
    board[y][x] = turn;

    if (turn == BLACK_STONE) {
        turn = WHITE_STONE;
    }
    else {
        turn = BLACK_STONE;
    }
}

void Game::placeStone(int x, int y, int whichStone) {
    if (whichStone == BLACK_STONE) {
        board[y][x] = BLACK_STONE;
    }
    else {
        board[y][x] = WHITE_STONE;
    }
}

// 임시함수: 오목판 출력 (나중에 다듬어서 쓸 것)
void Game::printBoard() {
    for (int y = 0; y < size + 2; y++) {
        // 좌표 숫자 표시 (y축)
        if (y != 0 && y != size + 1) {
            printf("%2d", size + 1 - y);
        }
        else {
            printf("  ");
        }

        // 바둑판 기호 표시
        for (int x = 0; x < size + 2; x++) {
            printSymbol(x, y);
        }
        std::cout << std::endl;
    }

    // 좌표 알파벳 표시 (x축)
    printf("    ");
    for (int x = 0; x < size; x++) {
        printf("%2c", alphabets[x]);
    }
}

void Game::printSymbol(int x, int y) {
    // TODO Symbol마다 Background/Foreground 색칠
    // TODO https://m.blog.naver.com/PostView.nhn?blogId=einsbon&logNo=221134136276&proxyReferer=https%3A%2F%2Fwww.google.com%2F

    if (board[y][x] == EMPTY) {
        // Corners
        if (y == 1 && x == 1)               std::cout << "┌ ";
        else if (y == 1 && x == size)       std::cout << "┐ ";
        else if (y == size && x == 1)       std::cout << "└ ";
        else if (y == size && x == size)    std::cout << "┘ ";

        // Edges
        else if (y == 1)                    std::cout << "┬ ";
        else if (x == 1)                    std::cout << "├ ";
        else if (x == size)                 std::cout << "┤ ";
        else if (y == size)                 std::cout << "┴ ";

        // Inside
        else                                std::cout << "┼ ";
    }
    else if (board[y][x] == BLACK_STONE) {
        std::cout << "●";
    }
    else if (board[y][x] == WHITE_STONE) {
        std::cout << "○";
    }
    else { // Wall
        std::cout << "※";
    }
}

void Game::handleKeyInput() {

    int keyInput = getKeyInput();
    int vx = 2;
    int vy = 1;

    // 키 입력을 받았을 경우
    // 커서의 위치와 보드 위 선택된 좌표를 업데이트한다
    // 커서가 움직이면 선택된 보드 좌표도 움직여야 함
    if (keyInput == UP) {
        if (cursorY - vy >= yBoundTop) {
            selectedBoardY -= 1;
            cursorY -= vy;
            gotoxy(cursorX, cursorY);
            std::cout << "◎";
        }
    }
    else if (keyInput == DOWN) {
        if (cursorY + vy <= yBoundBtm) {
            selectedBoardY += 1;
            cursorY += vy;
            gotoxy(cursorX, cursorY);
            std::cout << "◎";
        }
    }
    else if (keyInput == LEFT) {
        if (cursorX - vx >= xBoundLft) {
            selectedBoardX -= 1;
            cursorX -= vx;
            gotoxy(cursorX, cursorY);
            std::cout << "◎";
        }
    }
    else if (keyInput == RIGHT) {
        if (cursorX + vx <= xBoundRgt) {
            selectedBoardX += 1;
            cursorX += vx;
            gotoxy(cursorX, cursorY);
            std::cout << "◎";
        }
    }
    else if (keyInput == SPACE) {
        placeStone(selectedBoardX, selectedBoardY);
    }
}

int Game::getKeyInput() {
    int keyInput = _getch();

    // 특수키 입력
    if (keyInput == LEFT || keyInput == RIGHT || keyInput == UP || keyInput == DOWN) {
        return keyInput;
    }

    return keyInput;
}

// 콘솔 내 커서 위치 이동
void Game::gotoxy(int x, int y) {
    COORD pos = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}