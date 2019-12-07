#include "game.h"
#include "symbols.h"
#include "keys.h"
#include "console_handler.h"

#include <conio.h>
#include <Windows.h>

Game::Game(int size) {
    // 게임을 시작
    exitGame = false;

    // 콘솔창 설정
    ConsoleHandler::setPredefinedConsoleSize();
    ConsoleHandler::hideCursorOnConsole();  // 콘솔 커서 깜빡임 제거

    // 커서 이동 한계 설정
    yBoundTop = 1 + (23 - size) / 2;
    yBoundBtm = yBoundTop + size - 1;
    xBoundLft = 3 + (25 - size);
    xBoundRgt = xBoundLft + (size) * 2;

    // 커서 위치 설정 및 선택된 보드 좌표 설정 (1:1 매칭)
    cursorY = (yBoundTop + yBoundBtm) / 2;
    cursorX = (xBoundLft + xBoundRgt) / 2;
    selectedBoardX = (yBoundTop + size) / 2 - (25 - size) / 2 / 2;
    selectedBoardY = (xBoundLft - 2 + size) / 2 - (25 - size) / 2;

    // 보드 생성
    this->size = size;
    board = new Symbols * [size + 2]; // size는 15x15일 수도 있고 19x19일 수도 있음

    // 매개변수로 받은 size를 이용해 보드 크기 설정
    for (int i = 0; i < size + 2; i++) {
        board[i] = new Symbols[size + 2];
        memset(board[i], EMPTY, sizeof(int) * (size + 2)); // EMPTY로 초기화
    }

    // 벽에 WALL 값 대입
    for (int i = 0; i < size + 2; i++) {
        board[0][i] = WALL;
        board[size + 1][i] = WALL;
    }
    for (int i = 0; i < size + 2; i++) {
        board[i][0] = WALL;
        board[i][size + 1] = WALL;
    }

    // 현재 턴 설정
    turnNumber = 0;
    turn = BLACK_STONE;
    placeStone((size + 1) / 2, (size + 1) / 2); // 첫 턴으로 중심에 흑돌 착수

    // 최초 게임화면 display
    printGameScreen();
}

Game::~Game() {
    // Turn 정보를 담은 벡터 삭제
    turns.clear();

    // Board 정보 삭제
    for (int i = 0; i < size + 2; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

void Game::update() {
    bool timeLimitExceeded = false; // 시간 제한이 지났는지 플래그
    clock_t time = clock();

    // 30초가 지나면 시간패
    while (timeLimitExceeded == false) {
        // 남은 시간 표시
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

        // 착수 없이 30초 시간제한이 끝나면 시간패
        if (clock() - time > 30000) {
            timeLimitExceeded = true;

            // 메세지박스 출력
            if (turn == BLACK_STONE) {
                MessageBox(NULL, "Time Over - White stone wins.", "WHITE STONE WINS!", MB_OK);
            }
            else {
                MessageBox(NULL, "Time Over - Black stone wins.", "BLACK STONE WINS!", MB_OK);
            }
            // 게임 종료
            exitGame = true;
            break;
        }

        // 키 입력을 받았을 경우
        // 커서의 위치와 보드 위 선택된 좌표를 업데이트한다
        if (_kbhit()) {
            // 키값을 입력받는다
            int keyInput = getKeyInput();

            /****************************************
             * 키 입력에 따른 커서 이동 및 착수 처리
             ****************************************/
             // 원래 자리에 원래 보드 심볼 표시
            ConsoleHandler::setConsoleColor(BLACK, BROWN);
            ConsoleHandler::gotoxy(cursorX, cursorY);
            ConsoleHandler::printSymbol(board[selectedBoardY][selectedBoardX], size, selectedBoardX, selectedBoardY);

            // 커서가 움직이면 선택된 보드 좌표 (selectedBoardX, Y) 도 움직여야 함
            if (keyInput == Keys::UP) {
                if (cursorY - vy >= yBoundTop) {
                    selectedBoardY -= 1;
                    cursorY -= vy;
                    ConsoleHandler::displayCursor(cursorX, cursorY);
                }
            }
            else if (keyInput == Keys::DOWN) {
                if (cursorY + vy <= yBoundBtm) {
                    selectedBoardY += 1;
                    cursorY += vy;
                    ConsoleHandler::displayCursor(cursorX, cursorY);
                }
            }
            else if (keyInput == Keys::LEFT) {
                if (cursorX - vx >= xBoundLft) {
                    selectedBoardX -= 1;
                    cursorX -= vx;
                    ConsoleHandler::displayCursor(cursorX, cursorY);
                }
            }
            else if (keyInput == Keys::RIGHT) {
                if (cursorX + vx <= xBoundRgt) {
                    selectedBoardX += 1;
                    cursorX += vx;
                    ConsoleHandler::displayCursor(cursorX, cursorY);
                }
            }
            else if (keyInput == Keys::SPACE) {
                // 승자가 누구인지 결정되면 사용하기 위해 현재 턴이 누군지 저장
                Symbols winner = EMPTY;

                // 착수 가능 여부 확인 후, 선택된 좌표에 턴에 따라 흑/백돌 착수
                if (isPlaceable(selectedBoardX, selectedBoardY)) {
                    // 지금 둘 수로 게임에서 이겼는지 확인
                    winner = getWinner();

                    // 착수
                    placeStone(selectedBoardX, selectedBoardY);

                    // 승자가 존재한다면 마지막 오목판 상태 출력, 메세지박스 출력 및 게임 종료
                    if (winner == BLACK_STONE) {
                        printBoard();
                        MessageBox(NULL, "OMOK! - Black stone wins!", "BLACK STONE WINS!", MB_OK);
                        exitGame = true;
                    }
                    else if (winner == WHITE_STONE) {
                        printBoard();
                        MessageBox(NULL, "OMOK! - White stone wins!", "WHITE STONE WINS!", MB_OK);
                        exitGame = true;
                    }

                    // 착수를 했다면 while문 탈출하고 다음 턴의 시간을 표시할 준비를 한다
                    break;
                }
            }
            else if (keyInput == Keys::KEY_U || keyInput == Keys::KEY_U + 32) {
                // U를 눌렀을 경우 undo 실행
                if (undoStone() == 0) {
                    break;
                }
            }
            else if (keyInput == Keys::KEY_R || keyInput == Keys::KEY_R + 32) {
                // R을 눌렀을 경우 redo 실행
                if (redoStone() == 0) {
                    break;
                }
            }
            else if (keyInput == Keys::ESC) {
                // ESC를 눌렀을 경우 게임을 종료
                exitGame = true;
                break;
            }
            else if (keyInput == Keys::DEL) {
                // DELETE를 눌렀을 경우 착수하지 않고 현재 턴을 종료
                if (turn == Symbols::BLACK_STONE) {
                    blackSkipped = true;
                }
                else {
                    whiteSkipped = true;
                }
                // 둘 다 스킵했으면 무승부
                if (blackSkipped && whiteSkipped) {
                    MessageBox(NULL, "DRAW - Both players skipped their turns.", "DRAW!", MB_OK);
                    exitGame = true;
                }

                turn = (turn == Symbols::BLACK_STONE ? Symbols::WHITE_STONE : Symbols::BLACK_STONE);
                break;
            }
        }
    }
}

void Game::render() {
    // 화면 출력
    printBoard();
}

Symbols Game::getTurn() {
    return this->turn;
}

int Game::getSelectedBoardX() {
    return this->selectedBoardX;
}
int Game::getSelectedBoardY() {
    return this->selectedBoardY;
}

void Game::placeStone(int x, int y) {
    board[y][x] = turn;
    if (turn == Symbols::BLACK_STONE) {
        blackSkipped = false;
    }
    else {
        whiteSkipped = false;
    }

    // 현재 턴 넘버와 같거나 큰 넘버를 가진, 다른 분기의 수를 전부 삭제
    if (!turns.empty() && (turns.size() >= turnNumber)) {
        std::vector<TurnInfo>::iterator curIter = turns.begin() + turnNumber - 1; // 현재 턴부터의 iterator
        turns.erase(curIter, curIter + (turns.size() - turnNumber) + 1);
    }

    // 현재 턴 정보를 turns에 저장
    TurnInfo newTurn(x, y, turnNumber, turn);
    turns.push_back(newTurn);

    // 다음 턴으로 변경 (흑돌->백돌, 백돌->흑돌)
    turn = (turn == Symbols::BLACK_STONE ? Symbols::WHITE_STONE : Symbols::BLACK_STONE);
    turnNumber++;
}

void Game::setStone(int x, int y, Symbols whichStone) {
    board[y][x] = whichStone;
}

int Game::undoStone() {
    if (turns.empty() || turnNumber == 1) {
        // 첫번째 턴에서 undo를 하려고 하거나 되돌릴 턴이 없다면 아무 일도 수행하지 않고 반환
        return 1;
    }

    // 이전 턴의 정보를 불러옴
    TurnInfo lastTurn = turns.at(turnNumber - 2);
    Symbols whoIsLastTurn = lastTurn.getWhoseTurn();    // 가장 마지막 턴이 백돌인지 흑돌인지 판단
    int lastTurnX = lastTurn.getX();
    int lastTurnY = lastTurn.getY();

    // 게임 정보 업데이트
    turnNumber--;                                       // 게임을 1턴 되돌림
    board[lastTurnY][lastTurnX] = EMPTY;                // 마지막 턴의 정보를 되돌림
    turn = whoIsLastTurn;
    return 0; // 성공적으로 턴을 되돌림
}

int Game::redoStone() {
    if (turns.size() < turnNumber) {
        // 다시 가져올 턴이 없음
        return 1;
    }

    // 현재 턴과 같은 턴 넘버를 가진 턴 정보를 가져옴
    TurnInfo redoTurn = turns.at(turnNumber - 1);
    Symbols whoIsRedoTurn = redoTurn.getWhoseTurn();    // 가장 마지막 턴이 백돌인지 흑돌인지 가져옴
    int redoTurnX = redoTurn.getX();
    int reooTurnY = redoTurn.getY();

    // 게임 정보 업데이트
    board[reooTurnY][redoTurnX] = whoIsRedoTurn;        // 마지막 턴의 정보를 되돌림

    // 다음 턴으로 넘김
    turn = (whoIsRedoTurn == Symbols::BLACK_STONE ? Symbols::WHITE_STONE : Symbols::BLACK_STONE);
    turnNumber++;

    return 0; // 성공적으로 턴을 복구함
}

Symbols Game::getWinner() {
    if (isFive(selectedBoardX, selectedBoardY)) {
        // 승자가 결정된 경우
        return turn;
    }
    else {
        return Symbols::EMPTY;
    }
}


int Game::getKeyInput() {
    int keyInput = _getch();

    // 특수키 입력
    if (keyInput == LEFT || keyInput == RIGHT || keyInput == UP || keyInput == DOWN) {
        return keyInput;
    }

    return keyInput;
}

bool Game::isGameFinished() {
    return exitGame;
}

void Game::printGameScreen() {
    printBoard();

    ConsoleHandler::setConsoleColor(WHITE, BLACK);
    ConsoleHandler::gotoxy((25 - size), size + (27 - size) / 2 + 1);
    printf("○");

    ConsoleHandler::setConsoleColor(WHITE, BLACK);
    ConsoleHandler::gotoxy(size * 2 + (29 - size), size + (27 - size) / 2 + 1);
    printf("●");

    ConsoleHandler::displayShortcuts(size);
}

void Game::printBoard() {
    // 보드 출력 위치로 이동
    ConsoleHandler::gotoxy(25 - size, (23 - size) / 2);
    // 콘솔 색상 설정
    ConsoleHandler::setConsoleColor(BLACK, BROWN);

    for (int y = 0; y < size + 2; y++) {
        // 좌표 숫자 표시 (y축)
        if (y != 0 && y != size + 1) {
            printf("%2d", size + 1 - y);
        }
        else {
            printf("  ");
        }

        // 바둑판 기호 표시
        for (int x = 0; x < size + 2; x++) {
            ConsoleHandler::printSymbol(board[y][x], size, x, y);
        }
        //std::cout << std::endl;
        ConsoleHandler::gotoxy(25 - size, (23 - size) / 2 + y + 1);
    }

    // 좌표 알파벳 표시 (x축)
    printf("    ");
    for (int x = 0; x < size; x++) {
        printf("%2c", alphabets[x]);
    }
    printf("  ");

    ConsoleHandler::setConsoleColor(WHITE, BLACK); // 콘솔 색상 설정

    // 해당 턴이 누구 턴인지 메세지를 출력
    if (turn == BLACK_STONE) {
        ConsoleHandler::gotoxy((25 - size), size + (27 - size) / 2 + 2);
        ConsoleHandler::showMsg(0);
        ConsoleHandler::gotoxy(size * 2 + (21 - size), size + (27 - size) / 2 + 2);
        ConsoleHandler::showMsg(2);
    }
    else { // if (turn == WHITE_STONE)
        ConsoleHandler::gotoxy(size * 2 + (21 - size), size + (27 - size) / 2 + 2);
        ConsoleHandler::showMsg(1);
        ConsoleHandler::gotoxy((25 - size), size + (27 - size) / 2 + 2);
        ConsoleHandler::showMsg(2);
    }
}



/***********************************************
 *
 *                  규칙 관련
 *
 ***********************************************/
 // 오목판의 좌표 (x, y)에 무언가 있는지 확인
bool Game::isExist(int x, int y) {
    if (board[y][x] != EMPTY) return true;
    else return false;
}

// 착수된 위치를 기준으로 8방향 설정
// dx dy는 멤버변수로 따로 빼낼것
void Game::getDirTable(int& x, int& y, int nDir) {
    int dx[] = { -1, 1,  0, 0, -1, 1, -1, 1 };
    int dy[] = { 0, 0, -1, 1, -1, 1, 1, -1 };
    x = dx[nDir];
    y = dy[nDir];
}

// 주어진 방향의 마지막돌의 자리가 비어있는지 확인하고
// 그 위치로 좌표를 이동
bool Game::isEmpty(int& x, int& y, int nDir) {
    int dx, dy;
    getDirTable(dx, dy, nDir);
    // 착수되는 점위치를 찾아서 반복문을 종료
    // 연속되는 갯수를 체크할때 쓰이는 기능이 추가된 상태
    for (; board[y][x] == turn; x += dx, y += dy);
    if (board[y][x] == EMPTY) return true;
    else return false;
}

//주어진 좌표에 돌을 두었을때 주어진 방향으로 연속된 돌의 갯수 카운트
int Game::getStoneCount(int x, int y, int nDir) {
    int dx, dy;
    int tx = x;
    int ty = y;
    int count = 0;

    if (board[y][x] != EMPTY) return 0;
    setStone(x, y, turn);
    getDirTable(dx, dy, nDir);
    for (; board[y][x] == turn; x += dx, y += dy) count++;

    getDirTable(dx, dy, nDir % 2 ? nDir - 1 : nDir + 1);
    x = tx + dx;
    y = ty + dy;
    for (; board[y][x] == turn; x += dx, y += dy) count++;
    setStone(tx, ty, EMPTY);
    return count;
}
// Four나 OpenFour 가 되는지 판별하기 위해
// 빈곳에 돌을 하나씩 두면서 오목이 되는지 검사
bool Game::isFiveForFour(int x, int y, int nDir) {
    if (getStoneCount(x, y, nDir) == 5) return true;
    return false;
}

// 돌을 놓았을때 돌의 갯수가 5개인지 판별
bool Game::isFive(int x, int y) {
    for (int i = 0; i < 8; i += 2) {
        if (getStoneCount(x, y, i) == 5) return true;
    }
    return false;
}

// 장목이 되는지 검사
bool Game::isSix(int x, int y) {
    for (int i = 0; i < 8; i += 2) {
        if (getStoneCount(x, y, i) >= 6) return true;
    }
    return false;
}


// 돌을 놓았을 때 4인지를 검사
bool Game::isFour(int x, int y, int nDir) {
    int tx, ty;
    nDir % 2 ? nDir -= 1 : nDir;
    setStone(x, y, turn);
    for (int i = 0; i < 2; i++) {
        tx = x;
        ty = y;
        if (isEmpty(tx, ty, nDir + i)) {
            if (isFiveForFour(tx, ty, nDir + i)) {
                setStone(x, y, EMPTY);
                return true;
            }
        }
    }
    setStone(x, y, EMPTY);
    return false;
}

// 돌이 연속으로 4개이고 끝에 돌을 놓았을때 오목이 되면 열린 4이다
int Game::isOpenFour(int x, int y, int nDir) {
    int tx, ty;
    int sum = 0;
    nDir % 2 ? nDir -= 1 : nDir;
    setStone(x, y, turn);
    for (int i = 0; i < 2; i++) {
        tx = x;
        ty = y;
        if (isEmpty(tx, ty, nDir + i))
            if (isFiveForFour(tx, ty, nDir + i)) sum++;
    }
    setStone(x, y, EMPTY);
    // 특이 케이스로 열린 4일때 한줄에서 44가 성립할때의 예외 처리
    if (sum == 2) {
        if (getStoneCount(x, y, nDir) == 4) sum = 1;
    }
    else sum = 0;
    return sum;
}

// 금수로 4-4에 대해서 검사
bool Game::isDoubleFour(int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; i += 2) {
        if (isOpenFour(x, y, i) == 2) return true;
        else if (isFour(x, y, i)) count++;
        if (count >= 2) return true;
    }
    return false;
}

// 열린 3에 대하여 검사
// 열린 3은 돌을 하나 더 놓았을때 열린 4가 반드시 되어야 한다.
bool Game::isOpenThree(int x, int y, int nDir) {
    int tx, ty;
    setStone(x, y, turn);
    for (int i = 0; i < 2; i++) {
        tx = x;
        ty = y;
        if (isEmpty(tx, ty, nDir += i)) {
            if ((isOpenFour(tx, ty, nDir) == 1)) {
                setStone(x, y, EMPTY);
                return true;
            }
        }
    }
    setStone(x, y, EMPTY);
    return false;
}

// 금수인 3-3을 검사
bool Game::isDoubleThree(int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; i += 2) {
        if (isOpenThree(x, y, i)) count++;
        if (count >= 2) return true;
    }
    return false;
}