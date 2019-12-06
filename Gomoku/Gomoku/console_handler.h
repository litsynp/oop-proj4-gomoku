#ifndef _CONSOLE_HANDLER_H_
#define _CONSOLE_HANDLER_H_

#include "symbols.h"
#include <ctime>
#include <string>

// 콘솔 색상 정의
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

// 알파벳 문자 정의
const unsigned char alphabets[26] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};

class ConsoleHandler {
private:

public:
    // 사전에 정의된 통일한 콘솔창 크기 설정
    static void setPredefinedConsoleSize();

    // 어떤 룰을 사용할지를 고르는 메뉴 표시
    static void showRuleMenu();

    // 어떤 룰을 선택했는지 입력값을 받음
    static int getRuleMenuInput();

    // 어떤 크기의 오목판을 사용할지를 고르는 메뉴 표시
    static void showBoardSizeMenu();

    // 어떤 크기의 오목판을 선택했는지 입력값을 받음
    static int getBoardSizeMenuInput();

    // 화면에 정보 표시
    static void showMsg(int whichMsg);

    // x, y에 해당하는 오목판 기호 한 칸 출력
    static void printSymbol(Symbols symbolOnBoardXY, int size, int x, int y);

    // x, y에 커서 출력
    static void displayCursor(int cursorX, int cursorY);

    // 화면에 남은 시간 표시
    static void displayRemainingTime(clock_t time);

    // 게임 단축키 설명
    static void displayShortcuts(int size);

    // 콘솔 위 글자색과 배경색 설정
    static void setConsoleColor(int foreground, int background);

    // 콘솔 내 커서 깜빡임 제거
    static void hideCursorOnConsole();

    // 콘솔 내 커서 위치 이동
    static void gotoxy(int x, int y);
};

#endif