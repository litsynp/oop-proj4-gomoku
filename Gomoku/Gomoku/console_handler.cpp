#include "console_handler.h"
#include "game.h"
#include "symbols.h"
#include "keys.h"

#include <Windows.h>
#include <cstdio>
#include <conio.h>
#include <ctime>
#include <iostream>

const std::string shortcutsMsg[] = {
    "�����̽��� : ��  ��",
    "��  ��  Ű : ��  ��",
    "    U      : Undo  ",
    "    R      : Redo  ",
    "Delete Key : Pass  "
};

const std::string turnMsg[] = {
    "BLACK TURN",
    "WHITE TURN",
    "          ",
    "BLACK  WIN",
    "WHITE  WIN",
    "   DRAW   "
};

void ConsoleHandler::setPredefinedConsoleSize() {
    system("mode con: cols=58 lines=32"); // �ܼ� ũ�� ����
}

void ConsoleHandler::showRuleMenu() {
    // �ܼ�â ����
    system("title ���� ����");// �ܼ�â �̸� ����
    setPredefinedConsoleSize();
    hideCursorOnConsole();

    const std::string ruleMenus[] = {
        "O M O K  G A M E",
        "������(GOMOKU) ��",
        "��  ��(NORMAL) ��",
        "��  ��(RENJU)  ��",
        "��   ��   ��   ��"
    };

    const std::string menuSelections[] = {
        "    ",
        "                         ",
        "  1. ",
        "                         ",
        "  2. ",
        "                         ",
        "  3. ",
        "                         ",
        "  4. "
    };

    int x = menuSelections[1].length();
    int y = sizeof(menuSelections) / sizeof(menuSelections[0]);

    x = 29 - x / 2;
    y = 12 - y / 2 - 1;

    system("cls");
    for (int i = 0; i < sizeof(menuSelections) / sizeof(menuSelections[0]); i++) {
        gotoxy(x, y + i);
        if (i & 1) std::cout << menuSelections[i];
        else       std::cout << menuSelections[i] << ruleMenus[i / 2];
    }
}

int ConsoleHandler::getRuleMenuInput() {
    int keyInput; // ���� Ű�� ���� ����
    while (true) {
        keyInput = _getch();
        if (keyInput == ESC || keyInput == '4') return ESC;
        else if (keyInput >= '1' && keyInput <= '3') break;
    }

    keyInput -= '0';
    return keyInput;
}

void ConsoleHandler::showBoardSizeMenu() {
    // �ܼ�â ����
    system("title ���� ����");// �ܼ�â �̸� ����
    setPredefinedConsoleSize();
    hideCursorOnConsole();

    int x, y;

    const std::string sizeMenus[] = {
        "  SIZE     SELECT",
        "15      *      15",
        "19      *      19",
        "��   ��   ��   ��"
    };

    const std::string menuSelections[] = {
        "    ",
        "                         ",
        "  1. ",
        "                         ",
        "  2. ",
        "                         ",
        "  3. "
    };

    x = menuSelections[1].length();
    y = sizeof(menuSelections) / sizeof(menuSelections[0]);

    x = 29 - x / 2;
    y = 12 - y / 2 - 1;

    system("cls");
    for (int i = 0; i < sizeof(menuSelections) / sizeof(menuSelections[0]); i++) {
        gotoxy(x, y + i);
        if (i & 1) std::cout << menuSelections[i];
        else       std::cout << menuSelections[i] << sizeMenus[i / 2];
    }
}

int ConsoleHandler::getBoardSizeMenuInput() {
    int keyInput; // ���� Ű�� ���� ����

    while (true) {
        keyInput = _getch();
        if (keyInput == ESC || keyInput == '3') return ESC;
        else if (keyInput >= '1' && keyInput <= '2') break;
    }

    keyInput -= '0';
    return keyInput;
}

void ConsoleHandler::printSymbol(Symbols symbolOnBoardXY, int size, int x, int y) {
    // TODO Symbol���� Background/Foreground ��ĥ
    if (symbolOnBoardXY == EMPTY) {
        // Corners
        if (y == 1 && x == 1)                  std::cout << "�� ";
        else if (y == 1 && x == size)          std::cout << "�� ";
        else if (y == size && x == 1)          std::cout << "�� ";
        else if (y == size && x == size)       std::cout << "�� ";

        // Edges
        else if (y == 1)                       std::cout << "�� ";
        else if (x == 1)                       std::cout << "�� ";
        else if (x == size)                    std::cout << "�� ";
        else if (y == size)                    std::cout << "�� ";

        // Inside
        else                                std::cout << "�� ";
    }
    else if (symbolOnBoardXY == BLACK_STONE) {
        std::cout << "��";
    }
    else if (symbolOnBoardXY == WHITE_STONE) {
        std::cout << "��";
    }
    else { // Wall
        std::cout << "��";
    }
}

void ConsoleHandler::displayShortcuts(int size) {
    for (int i = 0; i < sizeof(shortcutsMsg) / sizeof(shortcutsMsg[0]); i++) {
        gotoxy(size - 1 + (19 - size), size + (27 - size) / 2 + 3 + i);
        std::cout << shortcutsMsg[i];
    }
}

void ConsoleHandler::displayRemainingTime(clock_t time) {
    ConsoleHandler::setConsoleColor(RED, BLACK);
    int sec = ((clock() - (int)time) / 1000) % 60;
    int timeLimitInSec = TIME_LIMIT / 1000;
    printf("%02d", 30 - sec);
}

void ConsoleHandler::showMsg(int whichMsg) {
    std::cout << turnMsg[whichMsg];
}

void ConsoleHandler::setConsoleColor(int foreground, int background) {
    int color = foreground + background * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ConsoleHandler::hideCursorOnConsole() {
    CONSOLE_CURSOR_INFO cursorInfo = { 1, false };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void ConsoleHandler::gotoxy(int x, int y) {
    COORD pos = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
