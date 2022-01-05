#include <stdio.h>    // 표준 입출력 헤더파일
#include <conio.h>    // 콘솔 관련, _kbhit, _getch등을 사용하기 위한 헤더파일
#include <Windows.h>    // gotoxy 함수를 만들고 사용하기 위해 필요한 헤더파일
#include "Check.h"    // 룰을 체크아히 위한 함수가 들어있는 헤더파일
#include "Constant.h"    // 상수를 모아놓은 헤더파일
#include "DrawBoard.h"    // 보드판을 그리는 함수가 들어있는 헤더파일
#include "Move.h"    // gotoxy 함수와 커서를 움직이는 함수 등이 들어있는 헤더파일

// 전역변수인 보드판의 정보를 가져옴
extern int boardInfo[15][30];

// 보드판의 좌표를 전역변수로 만듦
int x = 14, y = 7;

// 커서를 움직이기 휘한 함수
void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 키를 입력받아 커서를 움직이는 함수
void Move_Key()
{
	unsigned char i = 0;    // 오목판은 다 둬도 225개이기 때문에 최대값이 255인 변수를 사용함
	char key;    // 입력받을 값을 저장하는 변수
	while (1)
	{
		// 커서 좌표 이동
		gotoxy(x, y);
		 
		// 입력이 있는지 검사
 		if (_kbhit())
		{
			key = _getch();
			// 키보드로 좌표 이동, 끝으로 가면 반대쪽 끝으로 돌아감
			// x는 2씩 y는 1씩 이동
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
			case SPACE:     // 스페이스바 입력받으면 돌 착수
				if ((boardInfo[y][x] != WHITESTONE && boardInfo[y][x] != BLACKSTONE) && printRuleOrWinner(checkRule(&i)) == WIN)
					return;    // 빈자리 인지 확인 후 룰을 체크 후 승리자가 있으면 종료
				
				
				switch (i % 2)
				{
				case 0:    // 백돌차례는 흑돌 금수를 보여줄 필요가 없음
					drawBanedStone(boardInfo);
					break;
				case 1:    // 흑돌차례는 흑돌 금수를 보여줘야함
					clearBanedStone(boardInfo);
					break;
				}
				break;
			}
		}
	}

	return;
}