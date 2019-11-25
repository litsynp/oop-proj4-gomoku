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

    // �ܼ� Ŀ�� �����
    CONSOLE_CURSOR_INFO cursorInfo = { 1, false };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // Ŀ�� �̵� �Ѱ� ����
    yBoundTop = 1;
    yBoundBtm = yBoundTop + size - 1;
    xBoundLft = 3;
    xBoundRgt = xBoundLft + (size) * 2;

    // Ŀ�� ��ġ ���� �� ���õ� ���� ��ǥ ���� (1:1 ��Ī)
    cursorY = (yBoundTop + yBoundBtm) / 2;
    cursorX = (xBoundLft + xBoundRgt) / 2;
    selectedBoardX = (yBoundTop + size) / 2;
    selectedBoardY = (xBoundLft - 2 + size) / 2;

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

    // ���� �� ����
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
    std::cout << "��";
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

void Game::handleKeyInput() {

    int keyInput = getKeyInput();
    int vx = 2;
    int vy = 1;

    // Ű �Է��� �޾��� ���
    // Ŀ���� ��ġ�� ���� �� ���õ� ��ǥ�� ������Ʈ�Ѵ�
    // Ŀ���� �����̸� ���õ� ���� ��ǥ�� �������� ��
    if (keyInput == UP) {
        if (cursorY - vy >= yBoundTop) {
            selectedBoardY -= 1;
            cursorY -= vy;
            gotoxy(cursorX, cursorY);
            std::cout << "��";
        }
    }
    else if (keyInput == DOWN) {
        if (cursorY + vy <= yBoundBtm) {
            selectedBoardY += 1;
            cursorY += vy;
            gotoxy(cursorX, cursorY);
            std::cout << "��";
        }
    }
    else if (keyInput == LEFT) {
        if (cursorX - vx >= xBoundLft) {
            selectedBoardX -= 1;
            cursorX -= vx;
            gotoxy(cursorX, cursorY);
            std::cout << "��";
        }
    }
    else if (keyInput == RIGHT) {
        if (cursorX + vx <= xBoundRgt) {
            selectedBoardX += 1;
            cursorX += vx;
            gotoxy(cursorX, cursorY);
            std::cout << "��";
        }
    }
    else if (keyInput == SPACE) {
        placeStone(selectedBoardX, selectedBoardY);
    }
}

int Game::getKeyInput() {
    int keyInput = _getch();

    // Ư��Ű �Է�
    if (keyInput == LEFT || keyInput == RIGHT || keyInput == UP || keyInput == DOWN) {
        return keyInput;
    }

    return keyInput;
}

// �ܼ� �� Ŀ�� ��ġ �̵�
void Game::gotoxy(int x, int y) {
    COORD pos = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}