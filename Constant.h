#ifndef __CONSTANT_H__    // 같은 이름의 헤더 파일이 있을 수 있어 오류를 방지하기 위해 사용한다
#define __CONSTANT_H__

// 콘솔창과 글자색을 결정하는 열거형 상수 / 배경, 글자가 각각 4비트씩 할당되므로 16가지의 색이 가능하다
typedef enum _ColorKinds
{
	black,
	blue,
	green,
	skyBlue,
	red,
	pink,
	orange,
	white,
	gray,
	lightBlue,
	brightGreen,
	sky,
	birghtRed,
	brightPink,
	brightYellow,
	brightWhite
} ColorKinds;

// 방향키를 입력받을때 들어오는 숫자
#define LEFT  75
#define RIGHT 77
#define UP    72
#define DOWN  80
#define SPACE 32

// 돌
#define BLACKSTONE '●'
#define WHITESTONE '○'

// 규칙과 금수를 상수로 표현
#define NO            0
#define OK            1
#define WIN           2
#define THREEANDTHREE 3
#define FOURANDFOUR   4
#define OPENFOUR      5
#define LONGSTONE     6
#define DRAW          7
#define FORBIDDEN    'Ⅹ'

#endif // !__CONSTANT_H__