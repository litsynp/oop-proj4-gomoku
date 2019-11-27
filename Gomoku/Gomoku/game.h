#ifndef _GAME_H_
#define _GAME_H_

#define TIME_LIMIT 30000    // 턴당 시간제한
#include "console_handler.h"

// 게임 포괄적인 부분을 담당하는 추상클래스
class Game {
private:
    // 동적 할당을 통한 오목판 초기화
    Symbols** board;   // 15x15일 수도 있고 19x19일 수도 있음
    int size;          // 오목판의 사이즈

    // 현재 누구 턴인지 저장 (시작은 흑돌)
    Symbols turn;

    // TODO 룰검사를 위한 임시보드
    // Symbols** tBoard;

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

public:
    // 게임 기본 세팅
    Game(int size);

    // 동적 할당된 오목판 메모리 해제
    ~Game();

    // 게임 정보 갱신 
    void update();

    // 화면 업데이트
    void render();


    /*************************************
     *              착수 관련
     *************************************/
     // 멤버변수 turn의 값에 따라 오목판에 흑돌/백돌 배치
    void placeStone(int x, int y);

    // whichStone의 값에 따라 오목판에 흑돌/백돌 배치
    void placeStone(int x, int y, int whichStone);

    // board의 x, y에 그 수를 둘 수 있는지 확인한다
    // 룰에 따라 달라지므로 상속 함수에서 정의해야 함
    virtual bool isPlaceable(int x, int y) = 0;


    /*************************************
     *     Keyboard Input Handling 관련
     *************************************/
     // 키보드 입력을 받음
    int getKeyInput();


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
    void GetDirTable(int& x, int& y, int nDir);         // 돌을 놓은 위치를 기준으로 8방향을 표기
    int GetStoneCount(int x, int y, int nDir);          // 정해진 방향으로 있는 돌의 갯수 카운트
    bool IsEmpty(int& x, int& y, int nDir);             // 착수 지점이 비어있는지 확인

    bool IsFiveForFour(int x, int y, int nDir);         // 주어진 방향으로 돌이 5개가 되는지 확인 
    bool IsFive(int x, int y);                          // 승리조건 판별
    bool IsSix(int x, int y);                           // 장목인 6개이상인 경우

    bool IsFour(int x, int y, int nDir);                // 돌의 갯수가 4인 경우
    int IsOpenFour(int x, int y, int nDir);             // 양쪽으로 열린 4의 경우
    bool IsDoubleFour(int x, int y);                    // 금수인 4-4를 확인

    bool IsOpenThree(int x, int y, int nDir);           // 양쪽으로 열린 3의 경우
    bool IsDoubleThree(int x, int y);                   // 금수인 3-3을 확인
    bool IsForbidden(int x, int y) { return false; };   // 모든 금수 조건을 검사

};


#endif