#ifndef _GAME_RULE_H_
#define _GAME_RULE_H_

// Main �Լ��� while������ �޴��� � ���� ������Ŀ� ����
// ������ ���� (State)�� �޶���
enum GameRule {
    GOMOKU = 1,        // ������ (������)
    NORMAL = 2,        // �븻
    RENJU = 3,         // ���� ��
    YAMAGUICHI = 4     // �߸���ġ �� (���� ��)
                       // ... (�ʿ信 ���� �߰�)
};

#endif