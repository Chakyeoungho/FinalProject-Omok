#ifndef __DRAWBOARD_H__    // ���� �̸��� ��� ������ ���� �� �־� ������ �����ϱ� ���� ����Ѵ�
#define __DRAWBOARD_H__

void drawBoard();                                // �������� �׸��� �Լ�
void cursor_view(int boolean);                   // Ŀ�� ����� ���ϴ� �Լ�
void ColorSet(int backColor, int textColor);    // �ܼ���� ������ ���� �����ϴ� �Լ�
int printRuleOrWinner(int winner_rule);          // ȭ�鿡 ���ڳ� ��Ģ, �ݼ��� ����Ѵ�
void drawBanedStone();                           // �����ǿ� �ݼ��� ����ϱ� ���� �Լ�
void clearBanedStone();                          // �ݼ� ǥ�ø� ���ִ� �Լ�

#endif // !__DRAWBOARD_H__