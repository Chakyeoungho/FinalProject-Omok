#include <stdio.h>    // ǥ�� ����� �������
#include <Windows.h>    // system�� Sleep�� �̿��ϱ� ���� �������
#include <conio.h>    // _kbhit�� _getch�� ����ϱ� ���� �������
#include "Constant.h"    // ����� ��Ƴ��� �������
#include "DrawBoard.h"    // Colorset �Լ��� ����ϱ� ���� �������
#include "Move.h"    // gotoxy�� ����ϱ� ���� �������

// ���� ������ ����ϱ� ���� �Լ�
void printInfo()
{
	// ó�� ȭ�鿡���� Ŀ���� ����
	cursor_view(FALSE);
	// ������ ��� ���, ���� ���������� ���
	ColorSet(white, black);
	system("cls");    // �̰� ������� ������ ���ڸ� ����ϴ� �κи� ���� ����
	gotoxy(0, 3);    // ���� ����
	printf("     GGGGG    OOOOO   M     M   OOOOO   KK   KK  UU   UU\n");
	printf("    GG   GG  OO   OO  MM   MM  OO   OO  KK  KK   UU   UU\n");
	printf("    GG       OO   OO  M M M M  OO   OO  KKKKK    UU   UU\n");
	printf("    GG  GGG  OO   OO  M  M  M  OO   OO  KK  kK   UU   UU\n");
	printf("     GGGG G   OOOOO   M     M   OOOOO   KK   KK   UUUUU \n");
	gotoxy(27, 9);
	printf("����");
	gotoxy(22, 12);
	printf("Press any key");
	gotoxy(0, 16);
	printf("������ : DCU ��ǻ�ͼ���Ʈ�����к� 21114073 ����ȣ");
	while (1)    // ...�� ������, �ݺ������� ����ϱ� ���� �Լ�
	{
		Sleep(500);    // 0.5�� ����
		gotoxy(35, 12);    // ���� ��ǥ�� �̴��Ѵ�.
		printf(".");    // .�� ����Ѵ�
		if (_kbhit())    // �Է��� �ִ��� Ȯ�� �� ������ �����Ѵ�.
			break;

		Sleep(500);
		gotoxy(36, 12);
		printf(".");
		if (_kbhit())
			break;

		Sleep(500);
		gotoxy(37, 12);
		printf(".");
		if (_kbhit())
			break;

		Sleep(500);
		gotoxy(35, 12);
		printf("   ");
		gotoxy(35, 12);
		if (_kbhit())
			break;
	}

	_getch(); // ó���� y�� Y�� �Է��ص� ���� ȭ���� �� �� �ֵ��� �ϴ� ����

	system("cls");    // ȭ�� �ʱ�ȭ
	gotoxy(3, 1);    // ��ǥ �̵� �� ���� ���� ���
	printf("�� �� �� �� �� �� �� �� �� �� �� �� *Info*�� �� �� �� �� �� �� �� �� �� �� ����");
	gotoxy(3, 2);
	printf("��                                                    ��");
	gotoxy(3, 3);
	printf("��  *����Ű�� Ŀ���� ���� �� �� �ֽ��ϴ�.             ��");
	gotoxy(3, 4);
	printf("��  *�����̽��ٸ� ������ ���� ������ �� �ֽ��ϴ�.     ��");
	gotoxy(3, 5);
	printf("��                                                    ��");
	gotoxy(3, 6);
	printf("��  *�� ������ ���ַ��� �����ϴ�.                     ��");
	gotoxy(3, 7);
	printf("��  *���� ���� ���� �������� 5���� ���̸� �̱�ϴ�.   ��");
	gotoxy(3, 8);
	printf("��  *�浹�� 3x3, 4x4, ����� �Ұ��� �մϴ�.           ��");
	gotoxy(3, 9);
	printf("��                                                    ��");
	gotoxy(3, 10);
	printf("��                    *���ӳ� ǥ��*                   ��");
	gotoxy(3, 11);
	printf("��  *33 : ��� �ݼ� | 44 : ��� �ݼ� | LS : ���      ��");
	gotoxy(3, 12);
	printf("��  *BW : ��� �ڸ� | WW : ��� �ڸ�                  ��");
	gotoxy(3, 13);
	printf("��                                                    ��");
	gotoxy(3, 14);
	printf("�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ����");
	gotoxy(50, 15);
	printf("���� (Y)");
}