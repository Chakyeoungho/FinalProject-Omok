#include <stdio.h>    // 표준 입출력 헤더파일
#include <string.h>    // memset을 사용하기 위핸 헤더파일
#include <Windows.h>    // Colorset, Sleep, system 등을 사용하기 위한 헤더파일
#include "Check.h"    // 승자, 비김, 금수를 확인하기 위한 함수가 있는 헤더파일
#include "Constant.h"    // 정의된 상수를 이용하기 위한 헤더파일
#include "DrawBoard.h"    // 보드판을 그리기 위한 함수가 있는 헤더파일
#include "Move.h"    // gotoxy를 사용하기 위한 헤더파일

// 다른 프로젝트에 있는 전역 변수를 가져온다
extern int x, y;
extern int boardInfo[15][30];

// 콘솔장과 글자의 색을 결정하는 함수
void ColorSet(int backColor, int textColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, (backColor << 4) + textColor);
	// SetConsoleTextAttribute(출력핸들, 색값);
}

// 커서 사이즈를 정하는 함수
void cursor_view(int boolean)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = boolean;
	ConsoleCursor.dwSize = 50;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

// 보드판을 그리는 함수
void drawBoard()
{
	ColorSet(orange, black);    // 배경을 주황색, 글자를 검은색으로 지정
	cursor_view(TRUE);              // 커서의 크기 조정
	system("cls");              // 화면 초기화
	printf("┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐ \n");
	for (int i = 0; i < 13; i++)
		printf("├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤ \n");
	printf("└─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘ \n");
}

// 화면에 승자나 규칙, 금수를 출력한다
int printRuleOrWinner(int winner_rule)
{
	switch (winner_rule)
	{
	case WHITESTONE:    // 백돌이 이겼을 경우
		memset(boardInfo, 0, sizeof(int) * 15 * 30);  // 보드판 정보 초기화
		ColorSet(orange, white);
		printf("●");    // 흰색으로 돌 출력
		ColorSet(orange, black);
		gotoxy(41, 5);
		ColorSet(orange, white);
		printf("●");    // 백돌이 이겼다고 출력
		ColorSet(orange, black);
		printf(" Win");
		gotoxy(x, y);
		return WIN;    // 종료하기 위해 승리를 반환
	case BLACKSTONE:
		memset(boardInfo, 0, sizeof(int) * 15 * 30);  // 보드판 정보 초기화
		printf("●");    // 흑돌 출력
		gotoxy(41, 5);
		printf("● Win");    // 흑돌이 이겼다고 출력
		gotoxy(x, y);
		return WIN;    // 종료하기 위해 승리를 반환
	case DRAW:    // 판에 더이상 둘 자리가 없어 비기는 상황
		memset(boardInfo, 0, sizeof(int) * 15 * 30);
		gotoxy(41, 5);
		printf("DRAW");
		gotoxy(x, y);
		return WIN;    // 비겼지만 종료하기 위해 WIN을 반환
	case LONGSTONE:    // 장목일 경우
		gotoxy(39, 5);    // 장목 출력
		printf("*LongStone*");
		Sleep(1000);    // 1초 정지
		gotoxy(39, 5);
		printf("           ");    // 글자 지우기
		gotoxy(x, y);
		return NO;
	case FOURANDFOUR:
		gotoxy(41, 5);    // 4x4 출력
		printf("*4x4*");
		Sleep(1000);    // 1초 정지
		gotoxy(41, 5);
		printf("            ");    // 글자 지우기
		gotoxy(x, y);
		return NO;
	case THREEANDTHREE:
		gotoxy(41, 5);    // 3x3 출력
		printf("*3x3*");
		Sleep(1000);    // 1초 정지
		gotoxy(41, 5);
		printf("            ");    // 글자 지우기
		gotoxy(x, y);
		return NO;
	default:    // 위 상황이 아니면
		return OK;    // OK 반환
	}
}

// 보드판에 금수를 출력하기 위한 함수
void drawBanedStone()
{
	// 판의 모든곳을 검사
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 30; j += 2)
		{
			// 0인자리, 빈자리만 검사
			if (boardInfo[i][j] == 0)
			{
				// 백승 자리에 WW를 출력
				boardInfo[i][j] = WHITESTONE;
				if (checkWinner(j, i) == WHITESTONE)
				{
					gotoxy(j, i);
					printf("WW");
					boardInfo[i][j] = 0;
					continue;
				}
				
				boardInfo[i][j] = BLACKSTONE;
				// 흑승 자리에 BW 출력
				if (checkWinner(j, i) == BLACKSTONE)
				{
					gotoxy(j, i);
					printf("BW");
				}
				// 금수가 나오는 빈도가 높은 순으로 검사함 
				// 3x3자리에 33출력 
				else if (threeThree(j, i))
				{
					gotoxy(j, i);
					printf("33");
				}
				// 장목자리에 LS 출력
				else if (checkWinner(j, i) == LONGSTONE)
				{
					gotoxy(j, i);
					printf("LS");
				}
				// 4x4자리에 44출력
				else if (fourFour(j, i))
				{
					gotoxy(j, i);
					printf("44");
				}
				
				// 확인을 했으면 0으로 초기화
				boardInfo[i][j] = 0;
			}
		}
	}
	// 누구 차례인지 출력
	gotoxy(34, 2);
	printf("● Turn");
}

// 금수 표시를 없애는 함수
void clearBanedStone()
{
	// 화면 초기화
	system("cls");
	drawBoard();
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 30; j += 2)
		{
			// 0인곳, 빈자리만 검사
			if (boardInfo[i][j] == 0)
			{
				// 횐 돌을 놓고 백승인지 검사
				boardInfo[i][j] = WHITESTONE;
				if (checkWinner(j, i) == WHITESTONE)
				{
					// WW 출력
					gotoxy(j, i);
					printf("WW");
					boardInfo[i][j] = 0;
					continue;
				}
				// 검은돌 놓고 흑승인지 검사
				boardInfo[i][j] = BLACKSTONE;
				if (checkWinner(j, i) == BLACKSTONE)
				{
					// BW 출력
					gotoxy(j, i);
					printf("BW");
					boardInfo[i][j] = 0;
				}
				// 0으로 초기화
				boardInfo[i][j] = 0;
			}

			// 화면이 초기화 됬으므로 돌들 다시 출력
			switch (boardInfo[i][j])
			{
			case 0:  // 빈자리면 넘어가기
				break;
			case WHITESTONE:
				gotoxy(j, i);
				ColorSet(orange, white);
				printf("●");
				ColorSet(orange, black);
				break;
			case BLACKSTONE:
				gotoxy(j, i);
				printf("●");
				break;
			}
		}
	}
	// 누구 차례인지 출력
	gotoxy(34, 2);
	ColorSet(orange, white);
	printf("●");
	ColorSet(orange, black);
	printf(" Turn");
}