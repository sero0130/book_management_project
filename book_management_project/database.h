#ifndef DATABASE_H
#define DATABASE_H
#pragma once
#include <stdio.h>
#include "structs.h"
#include <string.h>

/*
* 데이터 베이스(DB .txt파일) 관련 함수를 정의하는 헤더 파일
*/

void InitDatabase(void);														//데이터베이스 초기화(동적 메모리 할당)
void FreeDatabase(void);														//데이터베이스 해제(동적 메모리 해제)
int countlines(const char* filename);											//파일에서 구조체 개수를 세는 함수
DBERROR UserDatabaseSave(USER user[], LOGIN login[], int lastnum);				//user login 구조체 배열 전체 user.txt 파일에 저장
DBERROR UserDatabaseAppend(const USER* user, const LOGIN* login);				//user.txt에 사용자 한명 추가
DBERROR UserDatabaseLoad(USER user[], LOGIN login[], int max, int* count);		//user login 구조체 배열 전체 user.txt에서 불러오기
DBERROR BookDatabaseSave(BOOK book[], int lastnum);								//book.txt에 구조체 전체를 저장하는 함수


#endif