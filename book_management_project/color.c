//콘솔창 색상 변경 소스 파일
#define _CRT_SECURE_NO_WARNINGS
#include "color.h"
#include <Windows.h>
#include <stdio.h>


/*
* 콘솔 배경 색상 설정 함수
* 매개변수 : enum ColorType color - 설정할 배경 색상
* 반환값 : 없음
*/

void SetColorBG(ColorType color) {
	char BGcolor[20] = { 0 };
	snprintf(BGcolor, sizeof(BGcolor), "color %X", color);
	system(BGcolor);

	return;
}

/*
* 콘솔 글자 색상 설정 함수
* 매개변수 : enum ColorType color - 설정할 글자 색상
* 반환값 : 없음
*/

void SetColorFont(ColorType color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);

	return;
}

