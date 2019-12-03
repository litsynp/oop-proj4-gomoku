#ifndef _KEYS_H_
#define _KEYS_H_

// getch()로 입력받은 키값 정의
enum Keys {
    ESC = 27,
    UP = 72,
    LEFT = 75,
    RIGHT = 77,
    DOWN = 80,
    SPACE = 32,
    DEL = 83,

    // alphabets
    KEY_R = 82, // 32씩 더하면 lowercase
    KEY_U = 85
};

#endif