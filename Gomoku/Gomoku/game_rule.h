#ifndef _STATE_H_
#define _STATE_H_

// Main 함수의 while문에서 메뉴의 어떤 것을 골랐느냐에 따라
// 게임의 상태 (State)가 달라짐
enum GameRule {
    QP,            // Quick Play 가칭 빠른대전 (3-3 금수 룰)
    UNLIMITED,     // 무제한 (고모쿠룰)
    RENJU,         // 렌주 룰
    YAMAGUICHI     // 야마구치 룰 (국제 룰)
                   // ... (필요에 따라 추가)
};

#endif