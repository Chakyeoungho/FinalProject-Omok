#ifndef __DRAWBOARD_H__    // 같은 이름의 헤더 파일이 있을 수 있어 오류를 방지하기 위해 사용한다
#define __DRAWBOARD_H__

void drawBoard();                                // 보드판을 그리는 함수
void cursor_view(int boolean);                   // 커서 사이즈를 정하는 함수
void ColorSet(int backColor, int textColor);    // 콘솔장과 글자의 색을 결정하는 함수
int printRuleOrWinner(int winner_rule);          // 화면에 승자나 규칙, 금수를 출력한다
void drawBanedStone();                           // 보드판에 금수를 출력하기 위한 함수
void clearBanedStone();                          // 금수 표시를 없애는 함수

#endif // !__DRAWBOARD_H__