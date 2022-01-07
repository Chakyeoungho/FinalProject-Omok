#include <stdio.h>    // 표준 입출력 헤더파일
#include <Windows.h>    // system과 Sleep을 이용하기 위한 헤더파일
#include <conio.h>    // _kbhit와 _getch를 사용하기 위한 헤더파일
#include "Constant.h"    // 상수를 모아놓은 헤더파일
#include "DrawBoard.h"    // Colorset 함수를 사용하기 위한 헤더파일
#include "Move.h"    // gotoxy를 사용하기 위한 헤더파일

// 게임 정보를 출력하기 위한 함수
void printInfo()
{
	// 처음 화면에서는 커서를 없앰
	cursor_view(FALSE);
	// 정보는 배경 흰색, 글자 검은색으로 출력
	ColorSet(white, black);
	system("cls");    // 이걸 사용하지 않으면 글자를 출력하는 부분만 색이 변함
	gotoxy(0, 3);    // 게임 제목
	printf("     GGGGG    OOOOO   M     M   OOOOO   KK   KK  UU   UU\n");
	printf("    GG   GG  OO   OO  MM   MM  OO   OO  KK  KK   UU   UU\n");
	printf("    GG       OO   OO  M M M M  OO   OO  KKKKK    UU   UU\n");
	printf("    GG  GGG  OO   OO  M  M  M  OO   OO  KK  kK   UU   UU\n");
	printf("     GGGG G   OOOOO   M     M   OOOOO   KK   KK   UUUUU \n");
	gotoxy(27, 9);
	printf("오목");
	gotoxy(22, 12);
	printf("Press any key");
	gotoxy(0, 16);
	printf("제작자 : DCU 컴퓨터소프트웨어학부 21114073 차경호");
	while (1)    // ...을 순차적, 반복적으로 출력하기 위한 함수
	{
		Sleep(500);    // 0.5초 쉰다
		gotoxy(35, 12);    // 다음 좌표로 이당한다.
		printf(".");    // .을 출력한다
		if (_kbhit())    // 입력이 있는지 확인 후 있으면 종료한다.
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

	_getch(); // 처음에 y나 Y를 입력해도 정보 화면을 불 수 있도록 하는 역할

	system("cls");    // 화면 초기화
	gotoxy(3, 1);    // 죄표 이동 후 게임 정보 출력
	printf("┌ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ *Info*─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─┐");
	gotoxy(3, 2);
	printf("│                                                    │");
	gotoxy(3, 3);
	printf("│  *방향키로 커서를 조작 할 수 있습니다.             │");
	gotoxy(3, 4);
	printf("│  *스페이스바를 누르면 돌을 착수할 수 있습니다.     │");
	gotoxy(3, 5);
	printf("│                                                    │");
	gotoxy(3, 6);
	printf("│  *이 게임은 렌주룰을 따릅니다.                     │");
	gotoxy(3, 7);
	printf("│  *같은 색의 돌이 연속으로 5개가 놓이면 이깁니다.   │");
	gotoxy(3, 8);
	printf("│  *흑돌은 3x3, 4x4, 장목이 불가능 합니다.           │");
	gotoxy(3, 9);
	printf("│                                                    │");
	gotoxy(3, 10);
	printf("│                    *게임내 표시*                   │");
	gotoxy(3, 11);
	printf("│  *33 : 삼삼 금수 | 44 : 사사 금수 | LS : 장목      │");
	gotoxy(3, 12);
	printf("│  *BW : 흑승 자리 | WW : 백승 자리                  │");
	gotoxy(3, 13);
	printf("│                                                    │");
	gotoxy(3, 14);
	printf("└ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─┘");
	gotoxy(50, 15);
	printf("시작 (Y)");
}