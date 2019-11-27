#ifndef _CONSOLE_HANDLER_H_
#define _CONSOLE_HANDLER_H_

#include "symbols.h"
#include <ctime>

// �ܼ� ���� ����
#define BLACK           0
#define BLUE            1
#define GREEN           2
#define CYAN            3
#define RED             4
#define MAGENTA         5
#define BROWN           6
#define LIGHTGRAY       7
#define DARKGRAY        8
#define LIGHTBLUE       9
#define LIGHTGREEN      10
#define LIGHTCYAN       11
#define LIGHTRED        12
#define LIGHTMAGENTA    13
#define YELLOW          14
#define WHITE           15

// ���ĺ� ���� ����
const unsigned char alphabets[26] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};

class ConsoleHandler {
private:

public:
    // � ���� ��������� ���� �޴� ǥ��
    static void showRuleMenu();

    // � ���� �����ߴ��� �Է°��� ����
    static int getRuleMenuInput();

    // � ũ���� �������� ��������� ���� �޴� ǥ��
    static void showBoardSizeMenu();

    // � ũ���� �������� �����ߴ��� �Է°��� ����
    static int getBoardSizeMenuInput();

    // ȭ�鿡 ���� ǥ��
    static void showMsg(int whichMsg);

    // x, y�� �ش��ϴ� ������ ��ȣ �� ĭ ���
    static void printSymbol(Symbols symbolOnBoardXY, int size, int x, int y);

    // ȭ�鿡 ���� �ð� ǥ��
    static void displayRemainingTime(clock_t time);

    // ���� ����Ű ����
    static void displayShortcuts(int size);

    // �ܼ� �� ���ڻ��� ���� ����
    static void setConsoleColor(int foreground, int background);

    // �ܼ� �� Ŀ�� ������ ����
    static void hideCursorOnConsole();

    // �ܼ� �� Ŀ�� ��ġ �̵�
    static void gotoxy(int x, int y);
};

#endif