#ifndef __CHECK_H__    // 같은 이름의 헤더 파일이 있을 수 있어 오류를 방지하기 위해 사용한다
#define __CHECK_H__

int checkRule(unsigned char *i);    // 첫 돌으 천원에 두거나 돌을 번갈아 가며 놓고 금수를 체크하는 함수
int checkWinner(int x, int y);      // 승자를 확인하는 함수 장목도 여기서 체크한다
int threeThree(int x, int y);       // 3x3을 체크하는 함수
int fourFour(int x, int y);         // 4x4를 체크하는 함수

#endif // !__CHECK_H__