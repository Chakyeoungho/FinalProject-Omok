#include <stdio.h>        // ǥ�� ����� �������
#include <conio.h>        // �ܼ����� ����°� ���õ� �������
#include <Windows.h>      // �ܼ�â�� ũ�⸦ �����ϰ� ���α׷��� ��� ���� Sleep�� ����ϱ� ���� �������
#include "DrawBoard.h"    // ����� �׸��� ���� �Լ��� ��Ƴ��� �������
#include "Move.h"         // Ŀ���� �����ϰ� ���� �����ϱ� ���� �Լ��� ���ϳ��� �������
#include "PrintInfo.h"    // ������ �� ������ ������ ����ϱ� ���� �������

// �����Լ�
int main(int argc, char *argv[])
{
	char start;    // ������ �� �Է��� �޴� ���� ����
	char retry;    // �ٽ� �������� Ȯ���ϱ� ���� �Է��� �޴� ���� ����
	system("mode con cols=60 lines=17");    // �ܼ�â�� ũ�⸦ ���� 60, �÷� 17ĭ���� ����
	printInfo();    // ������ ������ ���
	
	while (1)
	{
		if (_kbhit())    // �Է��� ������ ����
		{
			start = _getch();    // start ������ ���� �Է�
			switch (start)
			{
			case 'y': case 'Y':    // y�Ǵ� Y�� �Էµ¸� ����
				system("cls");     // ȭ�� �ʱ�ȭ
				goto RETRY;        // goto�� ���� �ݺ��� ���� ���������� ����
			default:    // �ٸ� �Է��� ������ �ٽ� �ݺ�
				break;
			}
		}
	}

RETRY:    // �ٽ� �����ϱ� ���� �ʿ��� ���̺�
	drawBoard();    // �������� �׸���
	Move_Key();     // Ŀ���� �����ϰ� �����ϱ� ���� �Լ�
	
	gotoxy(35, 7);    // 35, 7�� �̵�
	printf("Try again? [ Y / N ]");    // �ٽ� �������� ���θ� �����
	while (1)
	{
		if (_kbhit())    // �Է��� ������ ����
		{
			retry = _getch();    // retry ������ �Է¹޴´�
			switch (retry)
			{
			case 'y': case 'Y':    // y�� Y�� �Է¹����� RETRY ���̺�� �̵��Ͽ� ������ �ٽ� �����Ѵ�
				system("cls");     // ȭ�� �ʱ�ȭ
				goto RETRY;
			case 'n': case 'N':    // n�̳� N�� �Է¹����� �����Ѵ�
				system("cls");
				gotoxy(25, 7);    // 25, 7�� �̵�
				printf("Quit...");  // ���
				Sleep(1000); // ���α׷� 1�ʵ��� ����
				return 0;    // ����
			default:    // �ٸ� �Է��� ������ ��� �ݺ�
				break;
			}
		}
	}

	return 0;   
}