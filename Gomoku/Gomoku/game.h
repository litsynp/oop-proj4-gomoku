#ifndef _GAME_H_
#define _GAME_H_

#define TIME_LIMIT 30000    // 턴당 시간제한

#include "console_handler.h"
#include "turn_info.h"
#include <vector>

// 게임 포괄적인 부분을 담당하는 추상클래스
class Game {
private:
    // 동적 할당을 통한 오목판 초기화
    Symbols** board;   // 15x15일 수도 있고 19x19일 수도 있음
    int size;          // 오목판의 사이즈

    // 현재 누구 턴인지 저장 (시작은 흑돌)
    Symbols turn;

    // 게임을 종료할지 여부를 저장 (ESC를 누를 경우 true, 아니면 false)
    bool exitGame;

    // Undo와 Redo 기능 구현을 위한 턴 정보를 저장하는 배열
    std::vector<TurnInfo> turns;

    // 현재 몇 번째 턴인지를 저장
    int turnNumber;

    // 현재 커서의 위치
    int cursorX;
    int cursorY;

    // 커서의 속도
    const int vx = 2;   // 커서는 x축 방향으로 2칸씩 움직임
    const int vy = 1;   // 커서는 y축 방향으로 1칸씩 움직임

    // 커서의 한계 범위 (보드 내에서만 움직일 수 있어야 함)
    int yBoundTop;      // 위쪽 한계
    int yBoundBtm;      // 아래쪽 한계
    int xBoundLft;      // 왼쪽 한계
    int xBoundRgt;      // 오른쪽 한계

    // 커서와 1:1 대응하는 board 위의 커서의 위치
    int selectedBoardX;
    int selectedBoardY;

    // 턴을 스킵했는지 저장 (두 명이 차례대로 턴을 스킵했다면 무승부)
    bool whiteSkipped = false;
    bool blackSkipped = false;

public:
    // 게임 기본 세팅
    Game(int size);

    // 동적 할당된 오목판 메모리 해제
    ~Game();

    // 게임 정보 갱신 
    void update();

    // 화면 업데이트
    void render();

    // getter for turn member variable
    Symbols getTurn();

    // getters for selectedBoardX and Y
    int getSelectedBoardX();
    int getSelectedBoardY();

    /*************************************
     *              착수 관련
     *************************************/
     // 멤버변수 turn의 값에 따라 오목판에 흑돌/백돌 배치 후 턴 변경
    void placeStone(int x, int y);

    // 턴 변경 없이 whichStone의 값에 따라 오목판에 흑돌/백돌 배치
    void setStone(int x, int y, Symbols whichStone);

    // board의 x, y에 그 수를 둘 수 있는지 확인한다
    // 룰에 따라 달라지므로 상속 함수에서 정의해야 함
    virtual bool isPlaceable(int x, int y) = 0;

    // 사용자가 U를 눌렀을 때 실행되는 Undo 기능 (0: 성공, 1: 실패)
    int undoStone();

    // 사용자가 R을 눌렀을 때 실행되는 Redo 기능 (0: 성공, 1: 실패)
    int redoStone();

    // 현재 턴에서 둔 수로 이겼는지 체크
    virtual Symbols getWinner();

    /*************************************
     *     Keyboard Input Handling 관련
     *************************************/
     // 키보드 입력을 받음
    int getKeyInput();

    // exitGame 변수를 반환 (메인 함수에서 주기적으로 확인해서 true일시 게임 종료, false일시 게임 진행)
    bool isGameFinished();

    /*************************************
     *         Console Graphics 관련
     *************************************/
     // 첫 게임 화면 표시
    void printGameScreen();

    // 오목판 출력
    void printBoard();

    /*************************************
     *            게임 룰 관련
     *************************************/
    bool isExist(int x, int y);                         // 돌을 놓기전에 둘수 있는지 우선 판별
    void getDirTable(int& x, int& y, int nDir);         // 돌을 놓은 위치를 기준으로 8방향을 표기
    int getStoneCount(int x, int y, int nDir);          // 정해진 방향으로 있는 돌의 갯수 카운트
    bool isEmpty(int& x, int& y, int nDir);             // 착수 지점이 비어있는지 확인

    bool isFiveForFour(int x, int y, int nDir);         // 주어진 방향으로 돌이 5개가 되는지 확인 
    bool isFive(int x, int y);                          // 승리조건 판별
    bool isSix(int x, int y);                           // 장목인 6개이상인 경우

    bool isFour(int x, int y, int nDir);                // 돌의 갯수가 4인 경우
    int isOpenFour(int x, int y, int nDir);             // 양쪽으로 열린 4의 경우
    bool isDoubleFour(int x, int y);                    // 금수인 4-4를 확인

    bool isOpenThree(int x, int y, int nDir);           // 양쪽으로 열린 3의 경우
    bool isDoubleThree(int x, int y);                   // 금수인 3-3을 확인
};

#endif