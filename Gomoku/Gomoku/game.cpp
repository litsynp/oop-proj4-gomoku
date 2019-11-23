#include "game.h"
#include "game_rule.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <conio.h>
#include <Windows.h>


Game::Game(int size) {
    // �ܼ�â ����
    system("title ���� ����");// �ܼ�â �̸� ����
    system("mode con: cols=100 lines=40"); // �ܼ� ũ�� ����

    // ���� ����
    this->size = size;
    board = new int* [size + 2]; // size�� 15x15�� ���� �ְ� 19x19�� ���� ����

    // e.g. size = 15 or 19
    for (int i = 0; i < size + 2; i++) {
        board[i] = new int[size + 2];
        memset(board[i], EMPTY, sizeof(int) * (size + 2)); // EMPTY�� �ʱ�ȭ
    }

    // ���� WALL �� ����
    for (int i = 0; i < size + 2; i++) {
        board[0][i] = WALL;
        board[size + 1][i] = WALL;
    }
    for (int i = 0; i < size + 2; i++) {
        board[i][0] = WALL;
        board[i][size + 1] = WALL;
    }

    placeStone((size + 1) / 2, (size + 1) / 2, BLACK_STONE);
}

Game::~Game() {
    for (int i = 0; i < size + 2; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

void Game::update() {
    int keyInput = getKeyInput();

}

void Game::placeStone(int x, int y, int whichStone) {
    if (whichStone == BLACK_STONE) {
        board[y][x] = BLACK_STONE;
    }
    else {
        board[y][x] = WHITE_STONE;
    }
}

// �ӽ��Լ�: ������ ��� (���߿� �ٵ� �� ��)
void Game::printBoard() {
    for (int y = 0; y < size + 2; y++) {
        // ��ǥ ���� ǥ�� (y��)
        if (y != 0 && y != size + 1) {
            printf("%2d", size + 1 - y);
        }
        else {
            printf("  ");
        }

        // �ٵ��� ��ȣ ǥ��
        for (int x = 0; x < size + 2; x++) {
            printSymbol(x, y);
        }
        std::cout << std::endl;
    }

    // ��ǥ ���ĺ� ǥ�� (x��)
    printf("    ");
    for (int x = 0; x < size; x++) {
        printf("%2c", alphabets[x]);
    }
}

void Game::printSymbol(int x, int y) {
    // TODO Symbol���� Background/Foreground ��ĥ
    // TODO https://m.blog.naver.com/PostView.nhn?blogId=einsbon&logNo=221134136276&proxyReferer=https%3A%2F%2Fwww.google.com%2F

    if (board[y][x] == EMPTY) {
        // Corners
        if (y == 1 && x == 1)               std::cout << "�� ";
        else if (y == 1 && x == size)       std::cout << "�� ";
        else if (y == size && x == 1)       std::cout << "�� ";
        else if (y == size && x == size)    std::cout << "�� ";

        // Edges
        else if (y == 1)                    std::cout << "�� ";
        else if (x == 1)                    std::cout << "�� ";
        else if (x == size)                 std::cout << "�� ";
        else if (y == size)                 std::cout << "�� ";

        // Inside
        else                                std::cout << "�� ";
    }
    else if (board[y][x] == BLACK_STONE) {
        std::cout << "��";
    }
    else if (board[y][x] == WHITE_STONE) {
        std::cout << "��";
    }
    else { // Wall
        std::cout << "��";
    }
}


int Game::getKeyInput() {
    int keyInput = _getch();

    // Ư��Ű �Է�
    if (keyInput == LEFT || keyInput == RIGHT || keyInput == UP || keyInput == DOWN) {
        std::cout << "Ư������ �ƽ�Ű�ڵ�: " << keyInput << std::endl;
    }

    return keyInput;
}

// �ܼ� �� Ŀ�� ��ġ �̵�
void Game::gotoxy(int x, int y) {
    COORD pos = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}