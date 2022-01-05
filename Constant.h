#ifndef __CONSTANT_H__    // ���� �̸��� ��� ������ ���� �� �־� ������ �����ϱ� ���� ����Ѵ�
#define __CONSTANT_H__

// �ܼ�â�� ���ڻ��� �����ϴ� ������ ��� / ���, ���ڰ� ���� 4��Ʈ�� �Ҵ�ǹǷ� 16������ ���� �����ϴ�
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

// ����Ű�� �Է¹����� ������ ����
#define LEFT  75
#define RIGHT 77
#define UP    72
#define DOWN  80
#define SPACE 32

// ��
#define BLACKSTONE '��'
#define WHITESTONE '��'

// ��Ģ�� �ݼ��� ����� ǥ��
#define NO            0
#define OK            1
#define WIN           2
#define THREEANDTHREE 3
#define FOURANDFOUR   4
#define OPENFOUR      5
#define LONGSTONE     6
#define DRAW          7
#define FORBIDDEN    '��'

#endif // !__CONSTANT_H__