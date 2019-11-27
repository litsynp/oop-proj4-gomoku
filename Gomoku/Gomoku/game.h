#ifndef _GAME_H_
#define _GAME_H_

#define TIME_LIMIT 30000    // �ϴ� �ð�����
#include "console_handler.h"

// ���� �������� �κ��� ����ϴ� �߻�Ŭ����
class Game {
private:
    // ���� �Ҵ��� ���� ������ �ʱ�ȭ
    Symbols** board;   // 15x15�� ���� �ְ� 19x19�� ���� ����
    int size;          // �������� ������

    // ���� ���� ������ ���� (������ �浹)
    Symbols turn;

    // TODO ��˻縦 ���� �ӽú���
    // Symbols** tBoard;

    // ���� Ŀ���� ��ġ
    int cursorX;
    int cursorY;

    // Ŀ���� �ӵ�
    const int vx = 2;   // Ŀ���� x�� �������� 2ĭ�� ������
    const int vy = 1;   // Ŀ���� y�� �������� 1ĭ�� ������

    // Ŀ���� �Ѱ� ���� (���� �������� ������ �� �־�� ��)
    int yBoundTop;      // ���� �Ѱ�
    int yBoundBtm;      // �Ʒ��� �Ѱ�
    int xBoundLft;      // ���� �Ѱ�
    int xBoundRgt;      // ������ �Ѱ�

    // Ŀ���� 1:1 �����ϴ� board ���� Ŀ���� ��ġ
    int selectedBoardX;
    int selectedBoardY;

public:
    // ���� �⺻ ����
    Game(int size);

    // ���� �Ҵ�� ������ �޸� ����
    ~Game();

    // ���� ���� ���� 
    void update();

    // ȭ�� ������Ʈ
    void render();


    /*************************************
     *              ���� ����
     *************************************/
     // ������� turn�� ���� ���� �����ǿ� �浹/�鵹 ��ġ
    void placeStone(int x, int y);

    // whichStone�� ���� ���� �����ǿ� �浹/�鵹 ��ġ
    void placeStone(int x, int y, int whichStone);

    // board�� x, y�� �� ���� �� �� �ִ��� Ȯ���Ѵ�
    // �꿡 ���� �޶����Ƿ� ��� �Լ����� �����ؾ� ��
    virtual bool isPlaceable(int x, int y) = 0;


    /*************************************
     *     Keyboard Input Handling ����
     *************************************/
     // Ű���� �Է��� ����
    int getKeyInput();


    /*************************************
     *         Console Graphics ����
     *************************************/
     // ù ���� ȭ�� ǥ��
    void printGameScreen();

    // ������ ���
    void printBoard();

    /*************************************
     *            ���� �� ����
     *************************************/
    void GetDirTable(int& x, int& y, int nDir);         // ���� ���� ��ġ�� �������� 8������ ǥ��
    int GetStoneCount(int x, int y, int nDir);          // ������ �������� �ִ� ���� ���� ī��Ʈ
    bool IsEmpty(int& x, int& y, int nDir);             // ���� ������ ����ִ��� Ȯ��

    bool IsFiveForFour(int x, int y, int nDir);         // �־��� �������� ���� 5���� �Ǵ��� Ȯ�� 
    bool IsFive(int x, int y);                          // �¸����� �Ǻ�
    bool IsSix(int x, int y);                           // ����� 6���̻��� ���

    bool IsFour(int x, int y, int nDir);                // ���� ������ 4�� ���
    int IsOpenFour(int x, int y, int nDir);             // �������� ���� 4�� ���
    bool IsDoubleFour(int x, int y);                    // �ݼ��� 4-4�� Ȯ��

    bool IsOpenThree(int x, int y, int nDir);           // �������� ���� 3�� ���
    bool IsDoubleThree(int x, int y);                   // �ݼ��� 3-3�� Ȯ��
    bool IsForbidden(int x, int y) { return false; };   // ��� �ݼ� ������ �˻�

};


#endif