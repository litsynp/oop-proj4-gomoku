#ifndef _GAME_H_
#define _GAME_H_

// 배열 내 심볼값 정의
#define EMPTY		0 // 빈칸
#define BLACK_STONE 1 // 흑돌
#define WHITE_STONE 2 // 백돌
#define WALL		3 // 벽

// 키값 정의
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

const unsigned char alphabets[26] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};

class Game {
private:
    // 동적 할당을 통한 오목판 초기화
    int** board;        // 15x15일 수도 있고 19x19일 수도 있음
    int size;           // 오목판의 사이즈

public:
    // 게임 기본 세팅
    Game(int size);

    // 동적 할당된 오목판 메모리 해제
    ~Game();

    // whichStone의 값에 따라 오목판에 흑돌/백돌 배치
    void placeStone(int x, int y, int whichStone);

    // 임시함수: 오목판 출력
    void printBoard();

    // x, y에 해당하는 오목판 기호 한 칸 출력
    void printSymbol(int x, int y);

    // 키보드 입력을 받음
    int getKeyInput();

    // 해당 수를 둘 수 있는지 체크 (상속하는 클래스에서 정의)
    //virtual boolean isPlaceable() = 0;

    // 화면 업데이트 및 게임 진행 
    void update();

    // 아마 성민이가 만들 함수 - 메뉴 화면
    void printMenuScreen();

    // 아마 성민이가 만들 함수 - 게임 화면
    void printGameScreen();

    // 콘솔 내 커서 위치 이동
    void gotoxy(int, int);
};

#endif