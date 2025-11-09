//UI 소스 파일
#define _CRT_SECURE_NO_WARNINGS
#include "color.h"
#include "assistant.h"
#include <conio.h>				// _getch() 함수 사용을 위한 헤더 파일 포함
#include <stdio.h>
#include <Windows.h>

/*
* ─│┌ ┐┘└├ ┤┬ ┴ ┼
*/

/*
* 메인 화면 출력 함수
* 매개변수 : 없음
* 반환값 : 없음
*/

void DisplayMainScreen(void)
{
	InitConsole();
	DrawSquare(100, 30, 0, 0);
	DrawSquare(25, 4, 37, 5);
	MoveCursor(41, 7);
	printf("도서관 관리 프로그램");
	DrawSquare(30, 15, 35, 13);
	DrawSquare(11, 2, 44, 17);
	MoveCursor(48, 18);
	printf("로그인");
	DrawSquare(11, 2, 44, 20);
	MoveCursor(47, 21);
	printf("회원가입");

	return;
}