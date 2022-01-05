#include <stdio.h>    // 표준 입출력 헤더파일
#include <stdbool.h>    // 참 거짓을 사용하기 위한 헤더파일
#include "Check.h"    // 룰을 체크하는 함수가 들어있는 헤더파일
#include "Constant.h"    // 상수를 모아놓은 헤도파일
#include "DrawBoard.h"    // Colorset을 사용하기 위한 함수
#include "Move.h"    // gotoxy 함수를 사용하기 위한 함수

// 전역변수인 보드판의 정보와 x, y좌표를 가져옴
extern int boardInfo[15][30];
extern int x, y;

// Renju rule
int checkRule(unsigned char *i)
{
	int winnerCheck;
	int bwChange = !((*i) & 1);

	if (*i == 0)
	{
		boardInfo[7][14] = BLACKSTONE;
		gotoxy(14, 7);
		printf("●");
		if (x != 14 || y != 7)
			boardInfo[y][x] = 0;
		gotoxy(x, y);
		(*i)++;
		return NO;
	}
	else
	{
		switch (bwChange)
		{
		case 0:    // when i is odd
			boardInfo[y][x] = WHITESTONE;
			break;
		case 1:    // when i is even
			boardInfo[y][x] = BLACKSTONE;
			break;
		}
		(*i)++;
	}

	// 승자 여부 체크
	winnerCheck = checkWinner(x, y);
	if (winnerCheck)
	{
		if (winnerCheck == LONGSTONE)
		{
			(*i)--;
			boardInfo[y][x] = 0;
		}
		return winnerCheck;
	}
	// 흑돌 금수 체크
	else if (boardInfo[y][x] == BLACKSTONE)
	{
		if (x > 0 && x < 28 && y > 0 && y < 14) // 가장자리 태두리에는 3x3 금수가 나올 수 없다.
		{
			if (threeThree(x, y))    // 3x3
			{
				(*i)--;
				boardInfo[y][x] = 0;
				return THREEANDTHREE;
			}
		}
		if (fourFour(x, y))    // 4x4
		{
			(*i)--;
			boardInfo[y][x] = 0;
			return FOURANDFOUR;
		}
	}

	switch (bwChange)
	{
	case 0:    // 백돌일때 백돌 출력
		ColorSet(orange, white);
		printf("●");
		gotoxy(x, y);
		ColorSet(orange, black);
		break;
	case 1:    // 흑돌일때 흑돌 출력
		printf("●");
		gotoxy(x, y);
		break;
	}

	if ((*i) == 225)
		return DRAW;

	return NO;
}

// Check winner
int checkWinner(int x, int y)
{
	int count[4];    // 연속된 돌의 개수
	bool end1, end2;

	// Row ( | )
	count[0] = 1;
	end1 = false, end2 = false;
	for (int i = 1; i <= 4; i++)
	{
		// 세로 아래쪽
		if (boardInfo[y + i][x] != boardInfo[y][x])
			end1 = true;    // 중간에 같은 색의 돌이 아닌 부분이 나오면 그만세기
		if (boardInfo[y + i][x] == boardInfo[y][x] && y + i < 15 && !end1)
			count[0]++;    // 연속된 같은 색의 돌 개수 세기

		// 세로 위쪽
		if (boardInfo[y - i][x] != boardInfo[y][x])
			end2 = true;    // 중간에 같은 색의 돌이 아닌 부분이 나오면 그만세기
		if (boardInfo[y - i][x] == boardInfo[y][x] && y - i >= 0 && !end2)
			count[0]++;    // 연속된 같은 색의 돌 개수 세기
	}

	// Col ( ㅡ )
	count[1] = 1;
	end1 = false, end2 = false;
	for (int i = 1; i <= 4; i++)
	{
		// 가로 오른쪽
		if (boardInfo[y][x + (i * 2)] != boardInfo[y][x])
			end1 = true;    // 중간에 같은 색의 돌이 아닌 부분이 나오면 그만세기
		if (boardInfo[y][x + (i * 2)] == boardInfo[y][x] && x + (i * 2) < 30 && !end1)
			count[1]++;    // 연속된 같은 색의 돌 개수 세기

		// 가로 왼쪽
		if (boardInfo[y][x - (i * 2)] != boardInfo[y][x])
			end2 = true;    // 중간에 같은 색의 돌이 아닌 부분이 나오면 그만세기
		if (boardInfo[y][x - (i * 2)] == boardInfo[y][x] && x - (i * 2) >= 0 && !end2)
			count[1]++;    // 연속된 같은 색의 돌 개수 세기
	}

	// Diagonal ( / )
	count[2] = 1;
	end1 = false, end2 = false;
	for (int i = 1; i <= 4; i++)
	{
		// 대각선 오른쪽 위
		if (boardInfo[y - i][x + (i * 2)] != boardInfo[y][x])
			end1 = true;    // 중간에 같은 색의 돌이 아닌 부분이 나오면 그만세기
		if (boardInfo[y - i][x + (i * 2)] == boardInfo[y][x] && x + (i * 2) < 30 && y - i >= 0 && !end1)
			count[2]++;    // 연속된 같은 색의 돌 개수 세기

		// 대각선 왼쪽 아래
		if (boardInfo[y + i][x - (i * 2)] != boardInfo[y][x])
			end2 = true;    // 중간에 같은 색의 돌이 아닌 부분이 나오면 그만세기
		if (boardInfo[y + i][x - (i * 2)] == boardInfo[y][x] && x - (i * 2) >= 0 && y + i < 15 && !end2)
			count[2]++;    // 연속된 같은 색의 돌 개수 세기
	}

	// Diagonal ( \ )
	count[3] = 1;
	end1 = false, end2 = false;
	for (int i = 1; i <= 4; i++)
	{
		// 대각선 오른쪽 아래
		if (boardInfo[y + i][x + (i * 2)] != boardInfo[y][x])
			end1 = true;    // 중간에 같은 색의 돌이 아닌 부분이 나오면 그만세기
		if (boardInfo[y + i][x + (i * 2)] == boardInfo[y][x] && x + (i * 2) < 30 && y + i < 15 && !end1)
			count[3]++;    // 연속된 같은 색의 돌 개수 세기

		// 대각선 왼쪽 위
		if (boardInfo[y - i][x - (i * 2)] != boardInfo[y][x])
			end2 = true;    // 중간에 같은 색의 돌이 아닌 부분이 나오면 그만세기
		if (boardInfo[y - i][x - (i * 2)] == boardInfo[y][x] && x - (i * 2) >= 0 && y - i >= 0 && !end2)
			count[3]++;    // 연속된 같은 색의 돌 개수 세기
	}

	// 승자가 있으면 승자의 색 반환
	for (int i = 0; i < 4; i++)
	{
		if (count[i] == 5 && boardInfo[y][x] == BLACKSTONE)
			return BLACKSTONE;    // 중간에 같은 색의 돌이 아닌 부분이 나오면 그만세기
		else if (count[i] >= 5 && boardInfo[y][x] == WHITESTONE)
			return WHITESTONE;    // 백돌은 장목을 둬도 괜찮음
	}

	// 승자를 검사하고 장목을 검사해야 룰에 맞음
	for (int i = 0; i < 4; i++)
	{
		if (count[i] > 5 && boardInfo[y][x] == BLACKSTONE)
			return LONGSTONE;
	}

	return NO;
}

// Check 4x4
int fourFour(int x, int y)
{
	int blackCount[4];    // 흑돌의 개수
	int fourCount = 0;    // 열린 4와 반열린 4의 개수
	int emptyCount[2];    // 빈자리의 개수
	bool whiteStone1, whiteStone2;    // 흰돌이 있는지 검사할 변수
	int xu, xd, yu, yd;    // 가장 끝에 있는 흑돌의 좌표를 기억할 변수

	// Row ( | )
	blackCount[0] = 1;    // 흑돌의 개수, 현재 자리를 제외하고 계산하므로 1이라 설정
	xu = x; xd = x; yu = y; yd = y;    // 우선은 현재 돌을 놓은 좌표를 저장
	emptyCount[0] = 0; emptyCount[1] = 0;    // 빈자리의 개수
	whiteStone1 = false, whiteStone2 = false;    // 흰돌 여부
	for (int i = 1; i <= 4; i++)
	{
		// 세로 아래쪽
		if (boardInfo[y + i][x] == WHITESTONE)
			whiteStone1 = true;  // 흰돌이 있으면 거기까지 세기
		if (!whiteStone1 && boardInfo[y + i][x] == 0)
			emptyCount[0]++;    // 흰돌 전까지 빈자리 세기
		if (boardInfo[y + i][x] == boardInfo[y][x] && y + i < 15 && !whiteStone1 && emptyCount[0] <= 1)
		{    // 빈자리가 1개 초과거나 흰돌이 있으면 멈춤
			blackCount[0]++;
			yu = y + i;
		}

		// 세로 위쪽
		if (boardInfo[y - i][x] == WHITESTONE)
			whiteStone2 = true;  // 흰돌이 있으면 거기까지 세기
		if (!whiteStone2 && boardInfo[y - i][x] == 0)
			emptyCount[1]++;    // 흰돌 전까지 빈자리 세기
		if (boardInfo[y - i][x] == boardInfo[y][x] && y - i >= 0 && !whiteStone2 && emptyCount[1] <= 1)
		{    // 빈자리가 1개 초과거나 흰돌이 있으면 멈춤
			blackCount[0]++;
			yd = y - i;
		}
	}
	if (emptyCount[0] == 0 && emptyCount[1] == 0 && boardInfo[yu + 1][x] == WHITESTONE && boardInfo[yd - 1][x] == WHITESTONE)
		blackCount[0] = 0;    // 닫힌 4인지 검사
	for (int i = y - 4; i <= y - 3; i++)    // ●● ●● ●● 이어도 4x4이므로 검사
		if (boardInfo[i][x]     == BLACKSTONE && boardInfo[i + 1][x] == BLACKSTONE &&
			boardInfo[i + 2][x] == 0          &&
			boardInfo[i + 3][x] == BLACKSTONE && boardInfo[i + 4][x] == BLACKSTONE &&
			boardInfo[i + 5][x] == 0          &&
			boardInfo[i + 6][x] == BLACKSTONE && boardInfo[i + 7][x] == BLACKSTONE &&
			y >= 3 && y <= 11)
			return OK;
	for (int i = y - 4; i <= y - 2; i++)    // ● ●●● ● 이어도 4x4이므로 검사
		if (boardInfo[i][x]     == BLACKSTONE && boardInfo[i + 1][x] == 0          &&
			boardInfo[i + 2][x] == BLACKSTONE && boardInfo[i + 3][x] == BLACKSTONE && boardInfo[i + 4][x] == BLACKSTONE &&
			boardInfo[i + 5][x] == 0          && boardInfo[i + 6][x] == BLACKSTONE &&
			y >= 2 && y <= 12)
			return OK;

	// Col ( ㅡ )
	blackCount[1] = 1;
	xu = x; xd = x; yu = y; yd = y;
	emptyCount[0] = 0; emptyCount[1] = 0;
	whiteStone1 = false, whiteStone2 = false;
	for (int i = 1; i <= 4; i++)
	{
		// 가로 오른쪽
		if (boardInfo[y][x + (i * 2)] == WHITESTONE)
			whiteStone1 = true;  // 흰돌이 있으면 거기까지 세기
		if (!whiteStone1 && boardInfo[y][x + (i * 2)] == 0)
			emptyCount[0]++;    // 흰돌 전까지 빈자리 세기
		if (boardInfo[y][x + (i * 2)] == boardInfo[y][x] && x + (i * 2) < 30 && !whiteStone1 && emptyCount[0] <= 1)
		{    // 빈자리가 1개 초과거나 흰돌이 있으면 멈춤
			blackCount[1]++;
			xu = x + (i * 2);
		}

		// 가로 왼쪽
		if (boardInfo[y][x - (i * 2)] == WHITESTONE)
			whiteStone2 = true;  // 흰돌이 있으면 거기까지 세기
		if (!whiteStone2 && boardInfo[y][x - (i * 2)] == 0)
			emptyCount[1]++;    // 흰돌 전까지 빈자리 세기
		if (boardInfo[y][x - (i * 2)] == boardInfo[y][x] && x - (i * 2) >= 0 && !whiteStone2 && emptyCount[1] <= 1)
		{    // 빈자리가 1개 초과거나 흰돌이 있으면 멈춤
			blackCount[1]++;
			xd = x - (i * 2);
		}
	}
	if (emptyCount[0] == 0 && emptyCount[1] == 0 && boardInfo[y][xu + 2] == WHITESTONE && boardInfo[y][xd - 2] == WHITESTONE)
		blackCount[1] = 0;    // 닫힌 4인지 검사
	for (int i = x - 8; i <= x - 6; i++)    // ●● ●● ●● 이어도 4x4이므로 검사
		if (boardInfo[y][i]      == BLACKSTONE && boardInfo[y][i + 2]  == BLACKSTONE &&
			boardInfo[y][i + 4]  == 0          &&
			boardInfo[y][i + 6]  == BLACKSTONE && boardInfo[y][i + 8]  == BLACKSTONE &&
			boardInfo[y][i + 10] == 0          &&
			boardInfo[y][i + 12] == BLACKSTONE && boardInfo[y][i + 14] == BLACKSTONE &&
			x >= 6 && x <= 22)
			return OK;
	for (int i = x - 8; i <= x - 4; i++)    // ● ●●● ● 이어도 4x4이므로 검사
		if (boardInfo[y][i]      == BLACKSTONE && boardInfo[y][i + 2]  == 0          &&
			boardInfo[y][i + 4]  == BLACKSTONE && boardInfo[y][i + 6]  == BLACKSTONE && boardInfo[y][i + 8] == BLACKSTONE &&
			boardInfo[y][i + 10] == 0          && boardInfo[y][i + 12] == BLACKSTONE &&
			x >= 4 && x <= 26)
			return OK;

	// Diagonal ( / )
	blackCount[2] = 1;
	xu = x; xd = x; yu = y; yd = y;
	emptyCount[0] = 0; emptyCount[1] = 0;
	whiteStone1 = false, whiteStone2 = false;
	for (int i = 1; i <= 4; i++)
	{
		// 대각선 오른쪽 위
		if (boardInfo[y - i][x + (i * 2)] == WHITESTONE)
			whiteStone1 = true;  // 흰돌이 있으면 거기까지 세기
		if (!whiteStone1 && boardInfo[y - i][x + (i * 2)] == 0)
			emptyCount[0]++;    // 흰돌 전까지 빈자리 세기
		if (boardInfo[y - i][x + (i * 2)] == boardInfo[y][x] && x + (i * 2) < 30 && y - i >= 0 && !whiteStone1 && emptyCount[0] <= 1)
		{    // 빈자리가 1개 초과거나 흰돌이 있으면 멈춤
			blackCount[2]++;
			yd = y - i;
			xu = x + (i * 2);
		}

		// 대각선 왼쪽 아래
		if (boardInfo[y + i][x - (i * 2)] == WHITESTONE)
			whiteStone2 = true;  // 흰돌이 있으면 거기까지 세기
		if (!whiteStone2 && boardInfo[y + i][x - (i * 2)] == 0)
			emptyCount[1]++;    // 흰돌 전까지 빈자리 세기
		if (boardInfo[y + i][x - (i * 2)] == boardInfo[y][x] && x - (i * 2) >= 0 && y + i < 15 && !whiteStone2 && emptyCount[1] <= 1)
		{    // 빈자리가 1개 초과거나 흰돌이 있으면 멈춤
			blackCount[2]++;
			yu = y + i;
			xd = x - (i * 2);
		}
	}
	if (emptyCount[0] == 0 && emptyCount[1] == 0 && boardInfo[yu + 1][xd - 2] == WHITESTONE && boardInfo[yd - 1][xu + 2] == WHITESTONE)
		blackCount[2] = 0;    // 닫힌 4인지 검사
	for (int i = 0; i <= 1; i++)    // ●● ●● ●● 이어도 4x4이므로 검사
		if (boardInfo[y - i + 4][x + (i * 2) - 8] == BLACKSTONE && boardInfo[y - i + 3][x + (i * 2) - 6] == BLACKSTONE &&
			boardInfo[y - i + 2][x + (i * 2) - 4] == 0 &&
			boardInfo[y - i + 1][x + (i * 2) - 2] == BLACKSTONE && boardInfo[y - i][x + (i * 2)]         == BLACKSTONE &&
			boardInfo[y - i - 1][x + (i * 2) + 2] == 0 &&
			boardInfo[y - i - 2][x + (i * 2) + 4] == BLACKSTONE && boardInfo[y - i - 3][x + (i * 2) + 6] == BLACKSTONE &&
			x >= 6 && x <= 22)
			return OK;
	for (int i = 0; i <= 2; i++)    // ● ●●● ● 이어도 4x4이므로 검사
		if (boardInfo[y - i + 4][x + (i * 2) - 8] == BLACKSTONE && boardInfo[y - i + 3][x + (i * 2) - 6] == 0          &&
			boardInfo[y - i + 2][x + (i * 2) - 4] == BLACKSTONE && boardInfo[y - i + 1][x + (i * 2) - 2] == BLACKSTONE && boardInfo[y - i][x + (i * 2)] == BLACKSTONE &&
			boardInfo[y - i - 1][x + (i * 2) + 2] == 0          && boardInfo[y - i - 2][x + (i * 2) + 4] == BLACKSTONE &&
			x >= 4 && x <= 26)
			return OK;

	// Diagonal ( \ )
	blackCount[3] = 1;
	xu = x; xd = x; yu = y; yd = y;
	emptyCount[0] = 0; emptyCount[1] = 0;
	whiteStone1 = false, whiteStone2 = false;
	for (int i = 1; i <= 4; i++)
	{
		// 대각선 오른쪽 아래
		if (boardInfo[y + i][x + (i * 2)] == WHITESTONE)
			whiteStone1 = true;  // 흰돌이 있으면 거기까지 세기
		if (!whiteStone1 && boardInfo[y + i][x + (i * 2)] == 0)
			emptyCount[0]++;    // 흰돌 전까지 빈자리 세기
		if (boardInfo[y + i][x + (i * 2)] == boardInfo[y][x] && x + (i * 2) < 30 && y + i < 15 && !whiteStone1 && emptyCount[0] <= 1)
		{    // 빈자리가 1개 초과거나 흰돌이 있으면 멈춤
			blackCount[3]++;
			yu = y + i;
			xu = x + (i * 2);
		}

		// 대각선 왼쪽 위
		if (boardInfo[y - i][x - (i * 2)] == WHITESTONE)
			whiteStone2 = true;  // 흰돌이 있으면 거기까지 세기
		if (!whiteStone2 && boardInfo[y - i][x - (i * 2)] == 0)
			emptyCount[1]++;    // 흰돌 전까지 빈자리 세기
		if (boardInfo[y - i][x - (i * 2)] == boardInfo[y][x] && x - (i * 2) >= 0 && y - i >= 0 && !whiteStone2 && emptyCount[1] <= 1)
		{    // 빈자리가 1개 초과거나 흰돌이 있으면 멈춤
			blackCount[3]++;
			yd = y - i;
			xd = x - (i * 2);
		}
	}
	if (emptyCount[0] == 0 && emptyCount[1] == 0 && boardInfo[yu + 1][xu + 2] == WHITESTONE && boardInfo[yd - 1][xd - 2] == WHITESTONE)
		blackCount[3] = 0;    // 닫힌 4인지 검사
	for (int i = 0; i <= 1; i++)    // ●● ●● ●● 이어도 4x4이므로 검사
		if (boardInfo[y + i - 4][x + (i * 2) - 8] == BLACKSTONE && boardInfo[y + i - 3][x + (i * 2) - 6] == BLACKSTONE &&
			boardInfo[y + i - 2][x + (i * 2) - 4] == 0 &&
			boardInfo[y + i - 1][x + (i * 2) - 2] == BLACKSTONE && boardInfo[y + i][x + (i * 2)]         == BLACKSTONE &&
			boardInfo[y + i + 1][x + (i * 2) + 2] == 0 &&
			boardInfo[y + i + 2][x + (i * 2) + 4] == BLACKSTONE && boardInfo[y + i + 3][x + (i * 2) + 6] == BLACKSTONE &&
			x >= 6 && x <= 22)
			return OK;
	for (int i = 0; i <= 2; i++)    // ● ●●● ● 이어도 4x4이므로 검사
		if (boardInfo[y + i - 4][x + (i * 2) - 8] == BLACKSTONE && boardInfo[y + i - 3][x + (i * 2) - 6] == 0          &&
			boardInfo[y + i - 2][x + (i * 2) - 4] == BLACKSTONE && boardInfo[y + i - 1][x + (i * 2) - 2] == BLACKSTONE && boardInfo[y + i][x + (i * 2)] == BLACKSTONE &&
			boardInfo[y + i + 1][x + (i * 2) + 2] == 0          && boardInfo[y + i + 2][x + (i * 2) + 4] == BLACKSTONE &&
			x >= 4 && x <= 26)
			return OK;

	// 열린 4 개수 세기
	for (int i = 0; i < 4; i++)
		if (blackCount[i] == 4)
			fourCount++;

	// 열린 4가 2개 이상이면 맞다 반환
	if (fourCount >= 2)
		return OK;

	return NO;
}

// Check 3x3
int threeThree(int x, int y)
{
	int blackCount[4] = { 1, 1, 1, 1 };    // 흑돌의 개수, 자기자신은 세지 않으므로 1로 초기화
	int threeCount = 0;    // 열린 3의 개수
	int emptyCount[2];    // 빈자리의 개수
	int xu, xd, yu, yd;    // 세면서 움직인 x, y의 좌표
	bool end1, end2;    // 끝인지 여부를 검사

	/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- Row ( | ) +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-*/
	end1 = false, end2 = false;    // 우선 끝이 아니라고 해둠
	emptyCount[0] = 0; emptyCount[1] = 0;    // 0으로 초기화
	xu = x; xd = x; yu = y; yd = y;    // 현재 좌표를 지정
	for (int i = 1; i <= 4; i++)
	{
		if (boardInfo[y + i][x] == WHITESTONE)
			end1 = true;    // 흰돌이 있으면 끝
		if (!end1 && boardInfo[y + i][x] == 0)
			emptyCount[0]++;    // 빈자리 개수 세기
		if (y + i < 15 && !end1 && boardInfo[y + i][x] == boardInfo[y][x] && emptyCount[0] <= 1)
		{    // 흑돌 개수 세기
			blackCount[0]++;
			yu = y + i;    // 좌표 이동
		}

		if (boardInfo[y - i][x] == WHITESTONE)
			end2 = true;
		if (!end2 && boardInfo[y - i][x] == 0)
			emptyCount[1]++;
		if (y - i >= 0 && !end2 && boardInfo[y - i][x] == boardInfo[y][x] && emptyCount[1] <= 1)
		{
			blackCount[0]++;
			yd = y - i;
		}
	}
	if (boardInfo[yu + 1][x] == WHITESTONE || boardInfo[yd - 1][x] == WHITESTONE ||
		(blackCount[0] == 3 && (boardInfo[yu + 1][x] == BLACKSTONE || boardInfo[yd - 1][x] == BLACKSTONE)))
		blackCount[0] = 0;    // 열린 3인지 검사, 4인지 검사
	else if (((boardInfo[yu + 2][x] == WHITESTONE || yu + 2 > 14) && (boardInfo[yd - 2][x] == WHITESTONE || yd - 2 < 0)) ||
			 ((boardInfo[yu + 3][x] == BLACKSTONE || yu + 3 > 14) && (boardInfo[yd - 3][x] == BLACKSTONE || yd - 3 < 0)) ||
			 ((boardInfo[yu + 2][x] == WHITESTONE || yu + 2 > 14) && (boardInfo[yd - 3][x] == BLACKSTONE || yd - 3 < 0)) ||
			 ((boardInfo[yu + 3][x] == BLACKSTONE || yu + 3 > 14) && (boardInfo[yd - 2][x] == WHITESTONE || yd - 2 < 0)) ||
			   yd == 0 || yu == 14)
		blackCount[0] = 0;    // 금수 조사
	else if (boardInfo[y - 1][x] == 0 && boardInfo[y - 2][x] == BLACKSTONE && boardInfo[y + 1][x] == 0 && boardInfo[y + 2][x] == BLACKSTONE)
		blackCount[0] = 0;    // 착수한 곳 양쪽이 빈자리면 안됨

	/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- Col ( ㅡ ) +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-*/
	end1 = false, end2 = false;
	emptyCount[0] = 0; emptyCount[1] = 0;
	xu = x; xd = x; yu = y; yd = y;
	for (int i = 1; i <= 4; i++)
	{
		if (boardInfo[y][x + (i * 2)] == WHITESTONE)
			end1 = true;
		if (!end1 && boardInfo[y][x + (i * 2)] == 0)
			emptyCount[0]++;
		if (x + (i * 2) < 30 && !end1 && boardInfo[y][x + (i * 2)] == boardInfo[y][x] && emptyCount[0] <= 1)
		{
			blackCount[1]++;
			xu = x + (i * 2);
		}

		if (boardInfo[y][x - (i * 2)] == WHITESTONE)
			end2 = true;
		if (!end2 && boardInfo[y][x - (i * 2)] == 0)
			emptyCount[1]++;
		if (x - (i * 2) >= 0 && !end2 && boardInfo[y][x - (i * 2)] == boardInfo[y][x] && emptyCount[1] <= 1)
		{
			blackCount[1]++;
			xd = x - (i * 2);
		}
	}
	if (boardInfo[y][xu + 2] == WHITESTONE || boardInfo[y][xd - 2] == WHITESTONE ||
		(blackCount[1] == 3 && (boardInfo[y][xu + 2] == BLACKSTONE || boardInfo[y][xd - 2] == BLACKSTONE)))
		blackCount[1] = 0;
	else if (((boardInfo[y][xu + 4] == WHITESTONE || xu + 4 > 28) && (boardInfo[y][xd - 4] == WHITESTONE || xd - 4 < 0)) ||
		((boardInfo[y][xu + 6] == BLACKSTONE || xu + 6 > 28) && (boardInfo[y][xd - 6] == BLACKSTONE || xd - 6 < 0)) ||
		((boardInfo[y][xu + 4] == WHITESTONE || xu + 4 > 28) && (boardInfo[y][xd - 6] == BLACKSTONE || xd - 6 < 0)) ||
		((boardInfo[y][xu + 6] == BLACKSTONE || xu + 6 > 28) && (boardInfo[y][xd - 4] == WHITESTONE || xd - 4 < 0)) ||
		xd == 0 || xu == 28)
		blackCount[1] = 0;
	else if (boardInfo[y][x - 2] == 0 && boardInfo[y][x - 4] == BLACKSTONE && boardInfo[y][x + 2] == 0 && boardInfo[y][x + 4] == BLACKSTONE)
		blackCount[1] = 0;

	/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- Diagonal ( / ) +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-*/
	end1 = false, end2 = false;
	emptyCount[0] = 0; emptyCount[1] = 0;
	xu = x; xd = x; yu = y; yd = y;
	for (int i = 1; i <= 4; i++)
	{

		if (boardInfo[y - i][x + (i * 2)] == WHITESTONE)
			end1 = true;
		if (!end1 && boardInfo[y - i][x + (i * 2)] == 0)
			emptyCount[0]++;
		if (x + (i * 2) < 30 && y - i >= 0 && !end1 && boardInfo[y - i][x + (i * 2)] == boardInfo[y][x] && emptyCount[0] <= 1)
		{
			blackCount[2]++;
			xu = x + (i * 2);
			yd = y - i;
		}


		if (boardInfo[y + i][x - (i * 2)] == WHITESTONE)
			end2 = true;
		if (!end2 && boardInfo[y + i][x - (i * 2)] == 0)
			emptyCount[1]++;
		if (x - (i * 2) >= 0 && y + i < 15 && !end2 && boardInfo[y + i][x - (i * 2)] == boardInfo[y][x] && emptyCount[1] <= 1)
		{
			blackCount[2]++;
			xd = x - (i * 2);
			yu = y + i;
		}
	}
	if (boardInfo[yd - 1][xu + 2] == WHITESTONE || boardInfo[yu + 1][xd - 2] == WHITESTONE ||
		(blackCount[2] == 3 && (boardInfo[yd - 1][xu + 2] == BLACKSTONE || boardInfo[yu + 1][xd - 2] == BLACKSTONE)))
		blackCount[2] = 0;
	else if ((boardInfo[yd - 2][xu + 4] == WHITESTONE || (yd - 2 < 0 || xu + 4 > 28)) && (boardInfo[yu + 2][xd - 4] == WHITESTONE || (yu + 2 > 14 || xd - 4 < 0)) ||
		(boardInfo[yd - 3][xu + 6] == BLACKSTONE || (yd - 3 < 0 || xu + 6 > 28)) && (boardInfo[yu + 3][xd - 6] == BLACKSTONE || (yu + 3 > 14 || xd - 6 < 0)) ||
		(boardInfo[yd - 2][xu + 4] == WHITESTONE || (yd - 2 < 0 || xu + 4 > 28)) && (boardInfo[yu + 3][xd - 6] == BLACKSTONE || (yu + 3 > 14 || xd - 6 < 0)) ||
		(boardInfo[yd - 3][xu + 6] == BLACKSTONE || (yd - 3 < 0 || xu + 6 > 28)) && (boardInfo[yu + 2][xd - 4] == WHITESTONE || (yu + 2 > 14 || xd - 4 < 0)) ||
		xd == 0 || xu == 28 || yd == 0 || yu == 14)
		blackCount[2] = 0;
	else if (boardInfo[y + 1][x - 2] == 0 && boardInfo[y + 2][x - 4] == BLACKSTONE && boardInfo[y - 1][x + 2] == 0 && boardInfo[y - 2][x + 4] == BLACKSTONE)
		blackCount[2] = 0;

	/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- Diagonal( \ ) +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-*/
	end1 = false, end2 = false;
	emptyCount[0] = 0; emptyCount[1] = 0;
	xu = x; xd = x; yu = y; yd = y;
	for (int i = 1; i <= 4; i++)
	{
		if (boardInfo[y + i][x + (i * 2)] == WHITESTONE)
			end1 = true;
		if (!end1 && boardInfo[y + i][x + (i * 2)] == 0)
			emptyCount[0]++;
		if (x + (i * 2) < 28 && y + i < 14 && !end1 && boardInfo[y + i][x + (i * 2)] == boardInfo[y][x] && emptyCount[0] <= 1)
		{
			blackCount[3]++;
			xu = x + (i * 2);
			yu = y + i;
		}

		if (boardInfo[y - i][x - (i * 2)] == WHITESTONE)
			end2 = true;
		if (!end2 && boardInfo[y - i][x - (i * 2)] == 0)
			emptyCount[1]++;
		if (x - (i * 2) > 0 && y - i > 0 && !end2 && boardInfo[y - i][x - (i * 2)] == boardInfo[y][x] && emptyCount[1] <= 1)
		{
			blackCount[3]++;
			xd = x - (i * 2);
			yd = y - i;
		}
	}
	if (boardInfo[yu + 1][xu + 2] == WHITESTONE || boardInfo[yd - 1][xd - 2] == WHITESTONE ||
		(blackCount[3] == 3 && (boardInfo[yu + 1][xu + 2] == BLACKSTONE || boardInfo[yd - 1][xd - 2] == BLACKSTONE)))
		blackCount[3] = 0;
	else if (((boardInfo[yu + 2][xu + 4] == WHITESTONE || (yu + 2 > 14 || xu + 4 > 28)) && (boardInfo[yd - 2][xd - 4] == WHITESTONE || (yd - 2 < 0 || xd - 4 < 0))) ||
		((boardInfo[yu + 3][xu + 6] == BLACKSTONE || (yu + 3 > 14 || xu + 6 > 28)) && (boardInfo[yd - 3][xd - 6] == BLACKSTONE || (yd - 3 < 0 || xd - 6 < 0))) ||
		((boardInfo[yu + 2][xu + 4] == WHITESTONE || (yu + 2 > 14 || xu + 4 > 28)) && (boardInfo[yd - 2][xd - 4] == WHITESTONE || (yd - 2 < 0 || xd - 4 < 0))) ||
		((boardInfo[yu + 3][xu + 6] == BLACKSTONE || (yu + 3 > 14 || xu + 6 > 28)) && (boardInfo[yd - 3][xd - 6] == BLACKSTONE || (yd - 3 < 0 || xd - 6 < 0))) ||
		xd == 0 || xu == 28 || yd == 0 || yu == 14)
		blackCount[3] = 0;
	else if (boardInfo[y - 1][x - 2] == 0 && boardInfo[y - 2][x - 4] == BLACKSTONE && boardInfo[y + 1][x + 2] == 0 && boardInfo[y + 2][x + 4] == BLACKSTONE)
		blackCount[3] = 0;

	for (int i = 0; i < 4; i++)
		if (blackCount[i] == 3)
			threeCount++;

	if (threeCount < 2)
		return NO;

	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
	//                                                                                                                                               //
	//                                                           거짓금수 조사                                                                        //
	//                                                                                                                                               //
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//


	int f_forbidden = 0;
	int f_blackCount[4] = { 0, };
	int f_emptyCount[4] = { 0, };

	// Row ( | )
	if (blackCount[0] == 3)
	{
		for (int i = 4; i >= 0; i--)
		{
			if (y - i >= 0 && y - i + 5 < 15)
			{
				f_blackCount[0] = 0;
				f_emptyCount[0] = 0;
				for (int j = 0; j < 5; j++)
				{
					if (boardInfo[y - i + j][x] == WHITESTONE)
						break;
					if (boardInfo[y - i + j][x] == 0)
					{
						boardInfo[y - i + j][x] = BLACKSTONE;
						if (checkWinner(x, y - i + j) == LONGSTONE || checkWinner(x, y - i + j) == BLACKSTONE || fourFour(x, y - i + j))
						{
							boardInfo[y - i + j][x] = 0;
							break;
						}
						boardInfo[y - i + j][x] = 0;
						f_emptyCount[0]++;
					}
					if (boardInfo[y - i + j][x] == BLACKSTONE)
						f_blackCount[0]++;
				}

				if (f_blackCount[0] == 3 && f_emptyCount[0] == 2)
				{
					f_forbidden++;
					break;
				}
			}
		}
	}

	// Col ( ㅡ )
	if (blackCount[1] == 3)
	{
		for (int i = 4; i >= 0; i--)
		{
			if (x - (i * 2) >= 0 && x - (i * 2) + 10 < 30)
			{
				f_blackCount[1] = 0;
				f_emptyCount[1] = 0;
				for (int j = 0; j < 5; j++)
				{
					if (boardInfo[y][x - (i * 2) + (j * 2)] == WHITESTONE)
						break;
					if (boardInfo[y][x - (i * 2) + (j * 2)] == 0)
					{
						boardInfo[y][x - (i * 2) + (j * 2)] = BLACKSTONE;
						if (checkWinner(x - (i * 2) + (j * 2), y) == LONGSTONE || checkWinner(x - (i * 2) + (j * 2), y) == BLACKSTONE || fourFour(x - (i * 2) + (j * 2), y))
						{
							boardInfo[y][x - (i * 2) + (j * 2)] = 0;
							break;
						}
						boardInfo[y][x - (i * 2) + (j * 2)] = 0;
						f_emptyCount[1]++;
					}
					if (boardInfo[y][x - (i * 2) + (j * 2)] == BLACKSTONE)
						f_blackCount[1]++;
				}

				if (f_blackCount[1] == 3 && f_emptyCount[1] == 2)
				{
					f_forbidden++;
					break;
				}
			}
		}
	}

	// Diagonal ( / )
	if (blackCount[2] == 3)
	{
		for (int i = 4; i >= 0; i--)
		{
			if ((x - (i * 2) >= 0 && x - (i * 2) + 10 < 30) && (y + i - 5 >= 0 && y + i < 15))
			{
				f_blackCount[2] = 0;
				f_emptyCount[2] = 0;
				for (int j = 0; j < 5; j++)
				{
					if (boardInfo[y + i - j][x - (i * 2) + (j * 2)] == WHITESTONE)
						break;
					if (boardInfo[y + i - j][x - (i * 2) + (j * 2)] == 0)
					{
						boardInfo[y + i - j][x - (i * 2) + (j * 2)] = BLACKSTONE;
						if (checkWinner(x - (i * 2) + (j * 2), y + i - j) == LONGSTONE || checkWinner(x - (i * 2) + (j * 2), y + i - j) == BLACKSTONE || fourFour(x - (i * 2) + (j * 2), y + i - j))
						{
							boardInfo[y + i - j][x - (i * 2) + (j * 2)] = 0;
							break;
						}
						boardInfo[y + i - j][x - (i * 2) + (j * 2)] = 0;
						f_emptyCount[2]++;
					}
					if (boardInfo[y + i - j][x - (i * 2) + (j * 2)] == BLACKSTONE)
						f_blackCount[2]++;
				}

				if (f_blackCount[2] == 3 && f_emptyCount[2] == 2)
				{
					f_forbidden++;
					break;
				}
			}
		}
	}

	// Diagonal ( \ )
	if (blackCount[3] == 3)
	{
		for (int i = 4; i >= 0; i--)
		{
			if ((x - (i * 2) >= 0 && x - (i * 2) + 10 < 30) && (y - i >= 0 && y - i + 5 < 15))
			{
				f_blackCount[3] = 0;
				f_emptyCount[3] = 0;
				for (int j = 0; j < 5; j++)
				{
					if (boardInfo[y - i + j][x - (i * 2) + (j * 2)] == WHITESTONE)
						break;
					if (boardInfo[y - i + j][x - (i * 2) + (j * 2)] == 0)
					{
						boardInfo[y - i + j][x - (i * 2) + (j * 2)] = BLACKSTONE;
						if (checkWinner(x - (i * 2) + (j * 2), y - i + j) == LONGSTONE || checkWinner(x - (i * 2) + (j * 2), y - i + j) == BLACKSTONE || fourFour(x - (i * 2) + (j * 2), y - i + j))
						{
							boardInfo[y - i + j][x - (i * 2) + (j * 2)] = 0;
							break;
						}
						boardInfo[y - i + j][x - (i * 2) + (j * 2)] = 0;
						f_emptyCount[3]++;
					}
					if (boardInfo[y - i + j][x - (i * 2) + (j * 2)] == BLACKSTONE)
						f_blackCount[3]++;
				}

				if (f_blackCount[3] == 3 && f_emptyCount[3] == 2)
				{
					f_forbidden++;
					break;
				}
			}
		}
	}
	
	if (f_forbidden >= 2)
		return OK;

	return NO;
}