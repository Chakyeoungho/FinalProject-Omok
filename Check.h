#ifndef __CHECK_H__    // ���� �̸��� ��� ������ ���� �� �־� ������ �����ϱ� ���� ����Ѵ�
#define __CHECK_H__

int checkRule(unsigned char *i);    // ù ���� õ���� �ΰų� ���� ������ ���� ���� �ݼ��� üũ�ϴ� �Լ�
int checkWinner(int x, int y);      // ���ڸ� Ȯ���ϴ� �Լ� ��� ���⼭ üũ�Ѵ�
int threeThree(int x, int y);       // 3x3�� üũ�ϴ� �Լ�
int fourFour(int x, int y);         // 4x4�� üũ�ϴ� �Լ�

#endif // !__CHECK_H__