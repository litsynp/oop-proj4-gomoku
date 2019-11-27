#ifndef _GAME_RULE_H_
#define _GAME_RULE_H_

// Main 함수의 while문에서 메뉴의 어떤 것을 골랐느냐에 따라
// 게임의 상태 (State)가 달라짐
enum GameRule {
    GOMOKU = 1,        // 무제한 (고모쿠룰)
    NORMAL = 2,        // 노말
    RENJU = 3,         // 렌주 룰
    YAMAGUICHI = 4     // 야마구치 룰 (국제 룰)
                       // ... (필요에 따라 추가)
};

#endif