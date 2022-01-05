#include <stdio.h>    // ǥ�� ����� �������
#include <conio.h>    // �ܼ� ����, _kbhit, _getch���� ����ϱ� ���� �������
#include <Windows.h>    // gotoxy �Լ��� ����� ����ϱ� ���� �ʿ��� �������
#include "Check.h"    // ���� üũ���� ���� �Լ��� ����ִ� �������
#include "Constant.h"    // ����� ��Ƴ��� �������
#include "DrawBoard.h"    // �������� �׸��� �Լ��� ����ִ� �������
#include "Move.h"    // gotoxy �Լ��� Ŀ���� �����̴� �Լ� ���� ����ִ� �������

// ���������� �������� ������ ������
extern int boardInfo[15][30];

// �������� ��ǥ�� ���������� ����
int x = 14, y = 7;

// Ŀ���� �����̱� ���� �Լ�
void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// Ű�� �Է¹޾� Ŀ���� �����̴� �Լ�
void Move_Key()
{
	unsigned char i = 0;    // �������� �� �ֵ� 225���̱� ������ �ִ밪�� 255�� ������ �����
	char key;    // �Է¹��� ���� �����ϴ� ����
	while (1)
	{
		// Ŀ�� ��ǥ �̵�
		gotoxy(x, y);
		 
		// �Է��� �ִ��� �˻�
 		if (_kbhit())
		{
			key = _getch();
			// Ű����� ��ǥ �̵�, ������ ���� �ݴ��� ������ ���ư�
			// x�� 2�� y�� 1�� �̵�
			switch (key)
			{
			case -32:
				key = _getch();
				switch (key)
				{
				case LEFT:
					x -= 2;
					if (x < 0)
						x = 28;
					break;
				case RIGHT:
					x += 2;
					if (x > 28)
						x = 0;
					break;
				case UP:
					y--;
					if (y < 0)
						y = 14;
					break;
				case DOWN:
					y++;
					if (y > 14)
						y = 0;
					break;
				default:
					break;
				}    // Move cursor
				break;
			case SPACE:     // �����̽��� �Է¹����� �� ����
				if ((boardInfo[y][x] != WHITESTONE && boardInfo[y][x] != BLACKSTONE) && printRuleOrWinner(checkRule(&i)) == WIN)
					return;    // ���ڸ� ���� Ȯ�� �� ���� üũ �� �¸��ڰ� ������ ����
				
				
				switch (i % 2)
				{
				case 0:    // �鵹���ʴ� �浹 �ݼ��� ������ �ʿ䰡 ����
					drawBanedStone(boardInfo);
					break;
				case 1:    // �浹���ʴ� �浹 �ݼ��� ���������
					clearBanedStone(boardInfo);
					break;
				}
				break;
			}
		}
	}

	return;
}