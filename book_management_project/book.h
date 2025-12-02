#ifndef BOOK_H
#define BOOK_H
#pragma once
#include "structs.h"

#define BOOK_AREA_X1 22
#define BOOK_AREA_X2 96
#define BOOK_AREA_Y1 6
#define BOOK_AREA_Y2 28

/*
* 책 관련 함수를 정의하는 헤더 파일
*/
void SearchBook(const char* keyword);
void DisplayBookListInArea(void);

void AddBookInteractive(void);      // 책 추가
void EditBookInteractive(void);     // 책 수정
void RemoveBookInteractive(void);   // 책 삭제

int FindBookIndexById(const char* bookId);

#endif