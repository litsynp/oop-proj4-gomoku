#ifndef _GAME_H_
#define _GAME_H_

// �迭 �� �ɺ��� ����
#define EMPTY		0 // ��ĭ
#define BLACK_STONE 1 // �浹
#define WHITE_STONE 2 // �鵹
#define WALL		3 // ��

// Ű�� ����
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
    // ���� �Ҵ��� ���� ������ �ʱ�ȭ
    int** board;        // 15x15�� ���� �ְ� 19x19�� ���� ����
    int size;           // �������� ������

public:
    // ���� �⺻ ����
    Game(int size);

    // ���� �Ҵ�� ������ �޸� ����
    ~Game();

    // whichStone�� ���� ���� �����ǿ� �浹/�鵹 ��ġ
    void placeStone(int x, int y, int whichStone);

    // �ӽ��Լ�: ������ ���
    void printBoard();

    // x, y�� �ش��ϴ� ������ ��ȣ �� ĭ ���
    void printSymbol(int x, int y);

    // Ű���� �Է��� ����
    int getKeyInput();

    // �ش� ���� �� �� �ִ��� üũ (����ϴ� Ŭ�������� ����)
    //virtual boolean isPlaceable() = 0;

    // ȭ�� ������Ʈ �� ���� ���� 
    void update();

    // �Ƹ� �����̰� ���� �Լ� - �޴� ȭ��
    void printMenuScreen();

    // �Ƹ� �����̰� ���� �Լ� - ���� ȭ��
    void printGameScreen();

    // �ܼ� �� Ŀ�� ��ġ �̵�
    void gotoxy(int, int);
};

#endif