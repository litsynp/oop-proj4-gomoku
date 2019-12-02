#include "game.h"
#include "symbols.h"
#include "keys.h"
#include "console_handler.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <conio.h>
#include <Windows.h>

Game::Game(int size) {
    // �ܼ�â ����
    system("title ���� ����");              // �ܼ�â �̸� ����
    ConsoleHandler::setPredefinedConsoleSize();
    ConsoleHandler::hideCursorOnConsole();  // �ܼ� Ŀ�� ������ ����

    // Ŀ�� �̵� �Ѱ� ����
    yBoundTop = 1 + (23 - size) / 2;
    yBoundBtm = yBoundTop + size - 1;
    xBoundLft = 3 + (25 - size);
    xBoundRgt = xBoundLft + (size) * 2;

    // Ŀ�� ��ġ ���� �� ���õ� ���� ��ǥ ���� (1:1 ��Ī)
    cursorY = (yBoundTop + yBoundBtm) / 2;
    cursorX = (xBoundLft + xBoundRgt) / 2;
    selectedBoardX = (yBoundTop + size) / 2 - (25 - size) / 2 / 2;
    selectedBoardY = (xBoundLft - 2 + size) / 2 - (25 - size) / 2;

    // ���� ����
    this->size = size;
    board = new Symbols * [size + 2]; // size�� 15x15�� ���� �ְ� 19x19�� ���� ����

    // �Ű������� ���� size�� �̿��� ���� ũ�� ����
    for (int i = 0; i < size + 2; i++) {
        board[i] = new Symbols[size + 2];
        memset(board[i], EMPTY, sizeof(int) * (size + 2)); // EMPTY�� �ʱ�ȭ
    }

    // ���� WALL �� ����
    for (int i = 0; i < size + 2; i++) {
        board[0][i] = WALL;
        board[size + 1][i] = WALL;
    }
    for (int i = 0; i < size + 2; i++) {
        board[i][0] = WALL;
        board[i][size + 1] = WALL;
    }

    // ���� �� ����
    turnNumber = 0;
    turn = BLACK_STONE;
    placeStone((size + 1) / 2, (size + 1) / 2); // ù ������ �߽ɿ� �浹 ����

    // ���� ����ȭ�� display
    printGameScreen();
}

Game::~Game() {
    // Turn ������ ���� ���� ����
    turns.clear();

    // Board ���� ����
    for (int i = 0; i < size + 2; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

void Game::update() {
    bool timeLimitExceeded = false;
    clock_t time = clock();

    // 30�ʰ� ������ �ð���
    while (timeLimitExceeded == false) {
        // ���� �ð� ǥ��
        if (turn == BLACK_STONE) {
            ConsoleHandler::gotoxy((30 - size), size + (27 - size) / 2 + 1);
            ConsoleHandler::displayRemainingTime(time);
            ConsoleHandler::gotoxy(size * 2 + (24 - size), size + (27 - size) / 2 + 1);
            printf("  ");
        }
        else {
            ConsoleHandler::gotoxy(size * 2 + (24 - size), size + (27 - size) / 2 + 1);
            ConsoleHandler::displayRemainingTime(time);
            ConsoleHandler::gotoxy((30 - size), size + (27 - size) / 2 + 1);
            printf("  ");
        }

        if (clock() - time > 30000) {
            // ���� ���� 30�� �ð������� ����
            timeLimitExceeded = true;

            // TODO �ð��� �߰��ϱ�
            // ...
        }

        // Ű �Է��� �޾��� ���
        // Ŀ���� ��ġ�� ���� �� ���õ� ��ǥ�� ������Ʈ�Ѵ�
        if (_kbhit()) {
            // Ű���� �Է¹޴´�
            int keyInput = getKeyInput();

            /****************************************
             * Ű �Է¿� ���� Ŀ�� �̵� �� ���� ó��
             ****************************************/
             // ���� �ڸ��� ���� ���� �ɺ� ǥ��
            ConsoleHandler::setConsoleColor(BLACK, BROWN);
            ConsoleHandler::gotoxy(cursorX, cursorY);
            ConsoleHandler::printSymbol(board[selectedBoardY][selectedBoardX], size, selectedBoardX, selectedBoardY);

            // Ŀ���� ���� ����
            ConsoleHandler::setConsoleColor(WHITE, BROWN);

            // Ŀ���� �����̸� ���õ� ���� ��ǥ (selectedBoardX, Y) �� �������� ��
            if (keyInput == UP) {
                if (cursorY - vy >= yBoundTop) {
                    selectedBoardY -= 1;
                    cursorY -= vy;
                    ConsoleHandler::gotoxy(cursorX, cursorY);
                    printf("��");
                }
            }
            else if (keyInput == DOWN) {
                if (cursorY + vy <= yBoundBtm) {
                    selectedBoardY += 1;
                    cursorY += vy;
                    ConsoleHandler::gotoxy(cursorX, cursorY);
                    printf("��");
                }
            }
            else if (keyInput == LEFT) {
                if (cursorX - vx >= xBoundLft) {
                    selectedBoardX -= 1;
                    cursorX -= vx;
                    ConsoleHandler::gotoxy(cursorX, cursorY);
                    printf("��");
                }
            }
            else if (keyInput == RIGHT) {
                if (cursorX + vx <= xBoundRgt) {
                    selectedBoardX += 1;
                    cursorX += vx;
                    ConsoleHandler::gotoxy(cursorX, cursorY);
                    printf("��");
                }
            }
            else if (keyInput == SPACE) {
                // ���� ���� ���� Ȯ�� ��, ���õ� ��ǥ�� �Ͽ� ���� ��/�鵹 ����
                if (isPlaceable(selectedBoardX, selectedBoardY)) {
                    placeStone(selectedBoardX, selectedBoardY);

                    // ������ �ߴٸ� while�� Ż���ϰ� ���� ���� �ð��� ǥ���� �غ� �Ѵ�
                    break;
                }
            }
            else if (keyInput == KEY_U || keyInput == KEY_U + 32) {
                // U: Undo ����
                if (undoStone() == 0) {
                    break;
                }
            }
            else if (keyInput == KEY_R || keyInput == KEY_R + 32) {
                // R: Redo ����
                if (redoStone() == 0) {
                    break;
                }
            }

            // TODO ESC, DELETE �� ó��
            // ...
        }
    }
}

void Game::render() {
    printBoard();
    ConsoleHandler::gotoxy(cursorX, cursorY);
    ConsoleHandler::setConsoleColor(WHITE, BROWN);
    std::cout << "��";
}

Symbols Game::getTurn() {
    return this->turn;
}

void Game::placeStone(int x, int y) {
    board[y][x] = turn;

    // ���� �� ������ turns�� ����
    TurnInfo newTurn(x, y, turnNumber, turn);
    turns.push_back(newTurn);

    // ���� ������ ���� (�浹->�鵹, �鵹->�浹)
    turn = (turn == Symbols::BLACK_STONE ? Symbols::WHITE_STONE : Symbols::BLACK_STONE);
    turnNumber++;
}

void Game::setStone(int x, int y, Symbols whichStone) {
    board[y][x] = whichStone;
}

int Game::undoStone() {
    if (turns.empty()) {
        // �ǵ��� ���� ���ٸ� �ƹ� �ϵ� �������� �ʰ� ��ȯ
        return 1;
    }

    // ������ ���� ������ ������ ����
    TurnInfo lastTurn = turns.back();
    Symbols whoIsLastTurn = lastTurn.getWhoseTurn();    // ���� ������ ���� �鵹���� �浹���� ������
    int lastTurnX = lastTurn.getX();
    int lastTurnY = lastTurn.getY();

    // ���� ������ ���� ������ ����
    turns.pop_back();

    // ���� ���� ������Ʈ
    turnNumber--;                                       // ������ 1�� �ǵ���
    board[lastTurnY][lastTurnX] = EMPTY;                // ������ ���� ������ �ǵ���
    turn = (whoIsLastTurn == Symbols::BLACK_STONE ? Symbols::WHITE_STONE : Symbols::BLACK_STONE);
    return 0; // ���������� ���� �ǵ���
}

int Game::redoStone() {
    return 0; // ���������� ���� ������
}


int Game::getKeyInput() {
    int keyInput = _getch();

    // Ư��Ű �Է�
    if (keyInput == LEFT || keyInput == RIGHT || keyInput == UP || keyInput == DOWN) {
        return keyInput;
    }

    return keyInput;
}


void Game::printGameScreen() {
    printBoard();

    ConsoleHandler::gotoxy((25 - size), size + (27 - size) / 2 + 1);
    printf("��");

    ConsoleHandler::gotoxy(size * 2 + (29 - size), size + (27 - size) / 2 + 1);
    printf("��");

    ConsoleHandler::displayShortcuts(size);
}

// �ӽ��Լ�: ������ ��� (���߿� �ٵ� �� ��)
void Game::printBoard() {
    // ���� ��� ��ġ�� �̵�
    ConsoleHandler::gotoxy(25 - size, (23 - size) / 2);
    // �ܼ� ���� ����
    ConsoleHandler::setConsoleColor(BLACK, BROWN);

    for (int y = 0; y < size + 2; y++) {
        // ��ǥ ���� ǥ�� (y��)
        if (y != 0 && y != size + 1) {
            printf("%2d", size + 1 - y);
        }
        else {
            printf("  ");
        }

        // �ٵ��� ��ȣ ǥ��
        for (int x = 0; x < size + 2; x++) {
            ConsoleHandler::printSymbol(board[y][x], size, x, y);
        }
        //std::cout << std::endl;
        ConsoleHandler::gotoxy(25 - size, (23 - size) / 2 + y + 1);
    }

    // ��ǥ ���ĺ� ǥ�� (x��)
    printf("    ");
    for (int x = 0; x < size; x++) {
        printf("%2c", alphabets[x]);
    }
    printf("  ");

    ConsoleHandler::setConsoleColor(WHITE, BLACK);

    // �ش� ���� ���� ������ �޼����� ���
    if (turn == BLACK_STONE) {
        ConsoleHandler::gotoxy((25 - size), size + (27 - size) / 2 + 2);
        ConsoleHandler::showMsg(0);
        ConsoleHandler::gotoxy(size * 2 + (21 - size), size + (27 - size) / 2 + 2);
        ConsoleHandler::showMsg(2);
    }
    if (turn == WHITE_STONE) {
        ConsoleHandler::gotoxy(size * 2 + (21 - size), size + (27 - size) / 2 + 2);
        ConsoleHandler::showMsg(1);
        ConsoleHandler::gotoxy((25 - size), size + (27 - size) / 2 + 2);
        ConsoleHandler::showMsg(2);
    }
}



/***********************************************
 *
 *                  ��Ģ ����
 *
 ***********************************************/
 // �������� ��ǥ (x, y)�� ���� �ִ��� Ȯ��
bool Game::IsExist(int x, int y) {
    if (board[y][x] != EMPTY) return true;
    else return false;
}

// ������ ��ġ�� �������� 8���� ����
// dx dy�� ��������� ���� ������
void Game::GetDirTable(int& x, int& y, int nDir) {
    int dx[] = { -1, 1,  0, 0, -1, 1, -1, 1 };
    int dy[] = { 0, 0, -1, 1, -1, 1, 1, -1 };
    x = dx[nDir];
    y = dy[nDir];
}

// �־��� ������ ���������� �ڸ��� ����ִ��� Ȯ���ϰ�
// �� ��ġ�� ��ǥ�� �̵�
bool Game::IsEmpty(int& x, int& y, int nDir) {
    int dx, dy;
    GetDirTable(dx, dy, nDir);
    // �����Ǵ� ����ġ�� ã�Ƽ� �ݺ����� ����
    // ���ӵǴ� ������ üũ�Ҷ� ���̴� ����� �߰��� ����
    for (; board[y][x] == turn; x += dx, y += dy);
    if (board[y][x] == EMPTY) return true;
    else return false;
}

//�־��� ��ǥ�� ���� �ξ����� �־��� �������� ���ӵ� ���� ���� ī��Ʈ
int Game::GetStoneCount(int x, int y, int nDir) {
    int dx, dy;
    int tx = x;
    int ty = y;
    int count = 0;

    if (board[y][x] != EMPTY) return 0;
    setStone(x, y, turn);
    GetDirTable(dx, dy, nDir);
    for (; board[y][x] == turn; x += dx, y += dy) count++;

    GetDirTable(dx, dy, nDir % 2 ? nDir - 1 : nDir + 1);
    x = tx + dx;
    y = ty + dy;
    for (; board[y][x] == turn; x += dx, y += dy) count++;
    setStone(tx, ty, EMPTY);
    return count;
}
// Four�� OpenFour �� �Ǵ��� �Ǻ��ϱ� ����
// ����� ���� �ϳ��� �θ鼭 ������ �Ǵ��� �˻�
bool Game::IsFiveForFour(int x, int y, int nDir) {
    if (GetStoneCount(x, y, nDir) == 5) return true;
    return false;
}

// ���� �������� ���� ������ 5������ �Ǻ�
bool Game::IsFive(int x, int y) {
    for (int i = 0; i < 8; i += 2) {
        if (GetStoneCount(x, y, i) == 5) return true;
    }
    return false;
}

// ����� �Ǵ��� �˻�
bool Game::IsSix(int x, int y) {
    for (int i = 0; i < 8; i += 2) {
        if (GetStoneCount(x, y, i) >= 6) return true;
    }
    return false;
}


// ���� ������ �� 4������ �˻�
bool Game::IsFour(int x, int y, int nDir) {
    int tx, ty;
    nDir % 2 ? nDir -= 1 : nDir;
    setStone(x, y, turn);
    for (int i = 0; i < 2; i++) {
        tx = x;
        ty = y;
        if (IsEmpty(tx, ty, nDir + i)) {
            if (IsFiveForFour(tx, ty, nDir + i)) {
                setStone(x, y, EMPTY);
                return true;
            }
        }
    }
    setStone(x, y, EMPTY);
    return false;
}

// ���� �������� 4���̰� ���� ���� �������� ������ �Ǹ� ���� 4�̴�
int Game::IsOpenFour(int x, int y, int nDir) {
    int tx, ty;
    int sum = 0;
    nDir % 2 ? nDir -= 1 : nDir;
    setStone(x, y, turn);
    for (int i = 0; i < 2; i++) {
        tx = x;
        ty = y;
        if (IsEmpty(tx, ty, nDir + i))
            if (IsFiveForFour(tx, ty, nDir + i)) sum++;
    }
    setStone(x, y, EMPTY);
    // Ư�� ���̽��� ���� 4�϶� ���ٿ��� 44�� �����Ҷ��� ���� ó��
    if (sum == 2) {
        if (GetStoneCount(x, y, nDir) == 4) sum = 1;
    }
    else sum = 0;
    return sum;
}

// �ݼ��� 4-4�� ���ؼ� �˻�
bool Game::IsDoubleFour(int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; i += 2) {
        if (IsOpenFour(x, y, i) == 2) return true;
        else if (IsFour(x, y, i)) count++;
        if (count >= 2) return true;
    }
    return false;
}

// ���� 3�� ���Ͽ� �˻�
// ���� 3�� ���� �ϳ� �� �������� ���� 4�� �ݵ�� �Ǿ�� �Ѵ�.
bool Game::IsOpenThree(int x, int y, int nDir) {
    int tx, ty;
    setStone(x, y, turn);
    for (int i = 0; i < 2; i++) {
        tx = x;
        ty = y;
        if (IsEmpty(tx, ty, nDir += i)) {
            if ((IsOpenFour(tx, ty, nDir) == 1) && isPlaceable(tx, ty)) {
                setStone(x, y, EMPTY);
                return true;
            }
        }
    }
    setStone(x, y, EMPTY);
    return false;
}

// �ݼ��� 3-3�� �˻�
bool Game::IsDoubleThree(int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; i += 2) {
        if (IsOpenThree(x, y, i)) count++;
        if (count >= 2) return true;
    }
    return false;
}