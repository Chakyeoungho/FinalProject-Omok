#include <stdio.h>        // 표준 입출력 헤더파일
#include <conio.h>        // 콘솔장의 입출력과 관련된 헤더파일
#include <Windows.h>      // 콘솔창의 크기를 조절하고 프로그램이 잠시 쉬는 Sleep을 사용하기 위한 헤더파일
#include "DrawBoard.h"    // 배경을 그리기 위한 함수를 모아놓은 헤더파일
#include "Move.h"         // 커서를 조작하고 돌을 착수하기 위한 함수를 모하놓은 헤더파일
#include "PrintInfo.h"    // 시작할 때 게임의 정보를 출력하기 위한 헤더파일

// 메인함수
int main(int argc, char *argv[])
{
	char start;    // 시작할 때 입력을 받는 문자 변수
	char retry;    // 다시 시작할지 확인하기 위해 입력을 받는 문자 변수
	system("mode con cols=60 lines=17");    // 콘솔창의 크기를 가로 60, 시로 17칸으로 조절
	printInfo();    // 게임의 정보를 출력
	
	while (1)
	{
		if (_kbhit())    // 입력이 있으면 실행
		{
			start = _getch();    // start 변수에 값을 입력
			switch (start)
			{
			case 'y': case 'Y':    // y또는 Y가 입력돠면 실행
				system("cls");     // 화면 초기화
				goto RETRY;        // goto는 이중 반복문 꼴을 빠져나오기 좋다
			default:    // 다른 입력이 들어오면 다시 반복
				break;
			}
		}
	}

RETRY:    // 다시 시작하기 위해 필요한 레이블
	drawBoard();    // 보드판을 그린다
	Move_Key();     // 커서를 조작하고 착수하기 위한 함수
	
	gotoxy(35, 7);    // 35, 7로 이동
	printf("Try again? [ Y / N ]");    // 다시 시작할지 여부를 물어본다
	while (1)
	{
		if (_kbhit())    // 입력이 있으면 실행
		{
			retry = _getch();    // retry 변수에 입력받는다
			switch (retry)
			{
			case 'y': case 'Y':    // y나 Y를 입력받으면 RETRY 레이블로 이동하여 게임을 다시 시작한다
				system("cls");     // 화면 초기화
				goto RETRY;
			case 'n': case 'N':    // n이나 N을 입력받으면 종료한다
				system("cls");
				gotoxy(25, 7);    // 25, 7로 이동
				printf("Quit...");  // 출력
				Sleep(1000); // 프로그램 1초동안 정지
				return 0;    // 종료
			default:    // 다른 입력이 들어오면 계속 반복
				break;
			}
		}
	}

	return 0;   
}