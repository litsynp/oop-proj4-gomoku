#ifndef _STATE_H_
#define _STATE_H_

// Main �Լ��� while������ �޴��� � ���� ������Ŀ� ����
// ������ ���� (State)�� �޶���
enum GameRule {
    QP,            // Quick Play ��Ī �������� (3-3 �ݼ� ��)
    UNLIMITED,     // ������ (������)
    RENJU,         // ���� ��
    YAMAGUICHI     // �߸���ġ �� (���� ��)
                   // ... (�ʿ信 ���� �߰�)
};

#endif