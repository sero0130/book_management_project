#ifndef COLOR_H
#define COLOR_H
#pragma once
/*
* 콘솔 색상 관련 헤더 파일
*/

/*
* 콘솔 색상 관련 열거형 정의
*/
typedef enum ColorType {
    None = -1,
    COLOR_BLACK = 0,
    COLOR_DARK_BLUE,
    COLOR_DARK_GREEN,
    COLOR_DARK_SKYBLUE,
    COLOR_DARK_RED,
    COLOR_DARK_PURPLE,
    COLOR_DARK_YELLOW,
    COLOR_GRAY,
    COLOR_DARK_GRAY,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_SKYBLUE,
    COLOR_RED,
    COLOR_PURPLE,
    COLOR_YELLOW,
    COLOR_WHITE
} ColorType;

/*
* 콘솔 색상 설정 함수 원형
*/
void SetColorBG(ColorType color);    // 콘솔 배경 색상 설정 함수
void SetColorFont(ColorType color);  // 콘솔 글자 색상 설정 함수
#endif // !COLOR_H