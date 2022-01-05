#include <stdio.h>    // ǥ�� ����� �������
#include <string.h>    // memset�� ����ϱ� ���� �������
#include <Windows.h>    // Colorset, Sleep, system ���� ����ϱ� ���� �������
#include "Check.h"    // ����, ���, �ݼ��� Ȯ���ϱ� ���� �Լ��� �ִ� �������
#include "Constant.h"    // ���ǵ� ����� �̿��ϱ� ���� �������
#include "DrawBoard.h"    // �������� �׸��� ���� �Լ��� �ִ� �������
#include "Move.h"    // gotoxy�� ����ϱ� ���� �������

// �ٸ� ������Ʈ�� �ִ� ���� ������ �����´�
extern int x, y;
extern int boardInfo[15][30];

// �ܼ���� ������ ���� �����ϴ� �Լ�
void ColorSet(int backColor, int textColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, (backColor << 4) + textColor);
	// SetConsoleTextAttribute(����ڵ�, ����);
}

// Ŀ�� ����� ���ϴ� �Լ�
void cursor_view(int boolean)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = boolean;
	ConsoleCursor.dwSize = 50;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

// �������� �׸��� �Լ�
void drawBoard()
{
	ColorSet(orange, black);    // ����� ��Ȳ��, ���ڸ� ���������� ����
	cursor_view(TRUE);              // Ŀ���� ũ�� ����
	system("cls");              // ȭ�� �ʱ�ȭ
	printf("���������������������������������������������������������� \n");
	for (int i = 0; i < 13; i++)
		printf("���������������������������������������������������������� \n");
	printf("���������������������������������������������������������� \n");
}

// ȭ�鿡 ���ڳ� ��Ģ, �ݼ��� ����Ѵ�
int printRuleOrWinner(int winner_rule)
{
	switch (winner_rule)
	{
	case WHITESTONE:    // �鵹�� �̰��� ���
		memset(boardInfo, 0, sizeof(int) * 15 * 30);  // ������ ���� �ʱ�ȭ
		ColorSet(orange, white);
		printf("��");    // ������� �� ���
		ColorSet(orange, black);
		gotoxy(41, 5);
		ColorSet(orange, white);
		printf("��");    // �鵹�� �̰�ٰ� ���
		ColorSet(orange, black);
		printf(" Win");
		gotoxy(x, y);
		return WIN;    // �����ϱ� ���� �¸��� ��ȯ
	case BLACKSTONE:
		memset(boardInfo, 0, sizeof(int) * 15 * 30);  // ������ ���� �ʱ�ȭ
		printf("��");    // �浹 ���
		gotoxy(41, 5);
		printf("�� Win");    // �浹�� �̰�ٰ� ���
		gotoxy(x, y);
		return WIN;    // �����ϱ� ���� �¸��� ��ȯ
	case DRAW:    // �ǿ� ���̻� �� �ڸ��� ���� ���� ��Ȳ
		memset(boardInfo, 0, sizeof(int) * 15 * 30);
		gotoxy(41, 5);
		printf("DRAW");
		gotoxy(x, y);
		return WIN;    // ������� �����ϱ� ���� WIN�� ��ȯ
	case LONGSTONE:    // ����� ���
		gotoxy(39, 5);    // ��� ���
		printf("*LongStone*");
		Sleep(1000);    // 1�� ����
		gotoxy(39, 5);
		printf("           ");    // ���� �����
		gotoxy(x, y);
		return NO;
	case FOURANDFOUR:
		gotoxy(41, 5);    // 4x4 ���
		printf("*4x4*");
		Sleep(1000);    // 1�� ����
		gotoxy(41, 5);
		printf("            ");    // ���� �����
		gotoxy(x, y);
		return NO;
	case THREEANDTHREE:
		gotoxy(41, 5);    // 3x3 ���
		printf("*3x3*");
		Sleep(1000);    // 1�� ����
		gotoxy(41, 5);
		printf("            ");    // ���� �����
		gotoxy(x, y);
		return NO;
	default:    // �� ��Ȳ�� �ƴϸ�
		return OK;    // OK ��ȯ
	}
}

// �����ǿ� �ݼ��� ����ϱ� ���� �Լ�
void drawBanedStone()
{
	// ���� ������ �˻�
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 30; j += 2)
		{
			// 0���ڸ�, ���ڸ��� �˻�
			if (boardInfo[i][j] == 0)
			{
				// ��� �ڸ��� WW�� ���
				boardInfo[i][j] = WHITESTONE;
				if (checkWinner(j, i) == WHITESTONE)
				{
					gotoxy(j, i);
					printf("WW");
					boardInfo[i][j] = 0;
					continue;
				}
				
				boardInfo[i][j] = BLACKSTONE;
				// ��� �ڸ��� BW ���
				if (checkWinner(j, i) == BLACKSTONE)
				{
					gotoxy(j, i);
					printf("BW");
				}
				// �ݼ��� ������ �󵵰� ���� ������ �˻��� 
				// 3x3�ڸ��� 33��� 
				else if (threeThree(j, i))
				{
					gotoxy(j, i);
					printf("33");
				}
				// ����ڸ��� LS ���
				else if (checkWinner(j, i) == LONGSTONE)
				{
					gotoxy(j, i);
					printf("LS");
				}
				// 4x4�ڸ��� 44���
				else if (fourFour(j, i))
				{
					gotoxy(j, i);
					printf("44");
				}
				
				// Ȯ���� ������ 0���� �ʱ�ȭ
				boardInfo[i][j] = 0;
			}
		}
	}
	// ���� �������� ���
	gotoxy(34, 2);
	printf("�� Turn");
}

// �ݼ� ǥ�ø� ���ִ� �Լ�
void clearBanedStone()
{
	// ȭ�� �ʱ�ȭ
	system("cls");
	drawBoard();
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 30; j += 2)
		{
			// 0�ΰ�, ���ڸ��� �˻�
			if (boardInfo[i][j] == 0)
			{
				// Ⱥ ���� ���� ������� �˻�
				boardInfo[i][j] = WHITESTONE;
				if (checkWinner(j, i) == WHITESTONE)
				{
					// WW ���
					gotoxy(j, i);
					printf("WW");
					boardInfo[i][j] = 0;
					continue;
				}
				// ������ ���� ������� �˻�
				boardInfo[i][j] = BLACKSTONE;
				if (checkWinner(j, i) == BLACKSTONE)
				{
					// BW ���
					gotoxy(j, i);
					printf("BW");
					boardInfo[i][j] = 0;
				}
				// 0���� �ʱ�ȭ
				boardInfo[i][j] = 0;
			}

			// ȭ���� �ʱ�ȭ �����Ƿ� ���� �ٽ� ���
			switch (boardInfo[i][j])
			{
			case 0:  // ���ڸ��� �Ѿ��
				break;
			case WHITESTONE:
				gotoxy(j, i);
				ColorSet(orange, white);
				printf("��");
				ColorSet(orange, black);
				break;
			case BLACKSTONE:
				gotoxy(j, i);
				printf("��");
				break;
			}
		}
	}
	// ���� �������� ���
	gotoxy(34, 2);
	ColorSet(orange, white);
	printf("��");
	ColorSet(orange, black);
	printf(" Turn");
}