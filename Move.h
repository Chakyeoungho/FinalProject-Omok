#ifndef __MOVE_H__    // 같은 이름의 헤더 파일이 있을 수 있어 오류를 방지하기 위해 사용한다
#define __NOVE_H__

int boardInfo[15][30];

void gotoxy(int x, int y);    // 커서를 움직이기 휘한 함수
void Move_Key();              // 키를 입력받아 커서를 움직이는 함수

#endif // !__MOVE_H__