#ifndef _GAME_H_
#define _GAME_H_

#define TIME_LIMIT 30000    // �ϴ� �ð�����

#include "console_handler.h"
#include "turn_info.h"
#include <vector>

// ���� �������� �κ��� ����ϴ� �߻�Ŭ����
class Game {
private:
    // ���� �Ҵ��� ���� ������ �ʱ�ȭ
    Symbols** board;   // 15x15�� ���� �ְ� 19x19�� ���� ����
    int size;          // �������� ������

    // ���� ���� ������ ���� (������ �浹)
    Symbols turn;

    // ������ �������� ���θ� ���� (ESC�� ���� ��� true, �ƴϸ� false)
    bool exitGame;

    // Undo�� Redo ��� ������ ���� �� ������ �����ϴ� �迭
    std::vector<TurnInfo> turns;

    // ���� �� ��° �������� ����
    int turnNumber;

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

    // getter for turn member variable
    Symbols getTurn();

    /*************************************
     *              ���� ����
     *************************************/
     // ������� turn�� ���� ���� �����ǿ� �浹/�鵹 ��ġ �� �� ����
    void placeStone(int x, int y);

    // �� ���� ���� whichStone�� ���� ���� �����ǿ� �浹/�鵹 ��ġ
    void setStone(int x, int y, Symbols whichStone);

    // board�� x, y�� �� ���� �� �� �ִ��� Ȯ���Ѵ�
    // �꿡 ���� �޶����Ƿ� ��� �Լ����� �����ؾ� ��
    virtual bool isPlaceable(int x, int y) = 0;

    // ����ڰ� U�� ������ �� ����Ǵ� Undo ��� (0: ����, 1: ����)
    int undoStone();

    // ����ڰ� R�� ������ �� ����Ǵ� Redo ��� (0: ����, 1: ����)
    int redoStone();

    /*************************************
     *     Keyboard Input Handling ����
     *************************************/
     // Ű���� �Է��� ����
    int getKeyInput();

    // exitGame ������ ��ȯ (���� �Լ����� �ֱ������� Ȯ���ؼ� true�Ͻ� ���� ����, false�Ͻ� ���� ����)
    bool isGameFinished();

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
    bool isExist(int x, int y);                         // ���� �������� �Ѽ� �ִ��� �켱 �Ǻ�
    void getDirTable(int& x, int& y, int nDir);         // ���� ���� ��ġ�� �������� 8������ ǥ��
    int getStoneCount(int x, int y, int nDir);          // ������ �������� �ִ� ���� ���� ī��Ʈ
    bool isEmpty(int& x, int& y, int nDir);             // ���� ������ ����ִ��� Ȯ��

    bool isFiveForFour(int x, int y, int nDir);         // �־��� �������� ���� 5���� �Ǵ��� Ȯ�� 
    bool isFive(int x, int y);                          // �¸����� �Ǻ�
    bool isSix(int x, int y);                           // ����� 6���̻��� ���

    bool isFour(int x, int y, int nDir);                // ���� ������ 4�� ���
    int isOpenFour(int x, int y, int nDir);             // �������� ���� 4�� ���
    bool isDoubleFour(int x, int y);                    // �ݼ��� 4-4�� Ȯ��

    bool isOpenThree(int x, int y, int nDir);           // �������� ���� 3�� ���
    bool isDoubleThree(int x, int y);                   // �ݼ��� 3-3�� Ȯ��
    bool isForbidden(int x, int y) { return false; };   // ��� �ݼ� ������ �˻�
};

#endif