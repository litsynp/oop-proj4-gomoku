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
#define SPACE 32

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

    // 현재 누구 턴인지 저장 (시작은 흑돌)
    int turn;

    // 현재 커서의 위치
    int cursorX;
    int cursorY;

    // 커서의 한계 범위 (보드 내에서만 움직일 수 있어야 함)
    int yBoundTop; // 위쪽 한계
    int yBoundBtm; // 아래쪽 한계
    int xBoundLft; // 왼쪽 한계
    int xBoundRgt; // 오른쪽 한계
    
    // 커서와 1:1 대응하는 board 위의 커서의 위치
    int selectedBoardX;
    int selectedBoardY;

public:
    // 게임 기본 세팅
    Game(int size);

    // 동적 할당된 오목판 메모리 해제
    ~Game();

    // 멤버변수 turn의 값에 따라 오목판에 흑돌/백돌 배치
    void placeStone(int x, int y);

    // whichStone의 값에 따라 오목판에 흑돌/백돌 배치
    void placeStone(int x, int y, int whichStone);

    // 임시함수: 오목판 출력
    void printBoard();

    // x, y에 해당하는 오목판 기호 한 칸 출력
    void printSymbol(int x, int y);

    // 키보드 입력을 처리함 (UP, DOWN, LEFT, RIGHT, ...)
    void handleKeyInput();

    // 키보드 입력을 받음
    int getKeyInput();

    // 해당 수를 둘 수 있는지 체크 (상속하는 클래스에서 정의)
    //virtual boolean isPlaceable() = 0;

    // 게임 정보 갱신 
    void update();

    // 화면 업데이트
    void render();

    // 아마 성민이가 만들 함수 - 메뉴 화면
    void printMenuScreen();

    // 아마 성민이가 만들 함수 - 게임 화면
    void printGameScreen();

    // 콘솔 내 커서 위치 이동
    void gotoxy(int, int);
};

#endif