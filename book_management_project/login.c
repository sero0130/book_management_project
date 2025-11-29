#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "login.h"
#include "structs.h"


//	로그인 관련 함수


//	로그인 함수
int testlogin(void)
{

	FILE* file;
	file = fopen("user.txt", "r");

	LOGIN logininfo[MAX_USER_COUNT];

	int usercount = 0;

	//	파일에서 로그인 정보 읽기

	if (file == NULL)
	{
		printf("존재 하지않는 파일입니다.\n");
		return DB_FILE_NOT_FOUND;
	}

	while (fscanf(file, "%d %28s %48s",
		&logininfo[usercount].accountType,
		logininfo[usercount].loginID,
		logininfo[usercount].loginPW) != EOF)
	{
		usercount++;
	}

	fclose(file);


	//	id와 pw 저장 변수
	char id[MAX_USER_ID_LENGTH];
	char pw[MAX_USER_PASSWORD_LENGHTH];

	//	잘못된 로그인 시도 저장 
	int wrongcount = 0;


	//	무한루프를 돌면서 아이디와 비밀번호를 입력받고 확인
	while (1)
	{
		// 일정 시도 초과
		if (WRONGCOUNT_FAIL <= wrongcount)
		{
			printf("\n너무 많은 잘못된 로그인 시도입니다.\n프로그램을 종료합니다.\n");
			return -1;
		}
		else
		{
			if (wrongcount < 3)
			{
				//	아이디와 비밀번호 입력
				printf("\n아이디와 비밀번호를 입력하세요.\n");
			}
			else
			{
				printf("\n--%d회 이상 로그인을 실패하셨습니다.--\n10회 이상 로그인 실패시 로그인이 금지됩니다.\n", wrongcount);
			}

			printf("ID:");
			scanf(" %28s", id);		//	공백 문자 건너뛰기 

			printf("Password:");
			scanf(" %48s", pw);		//	공백 문자 건너뛰기 
		}

		//	반복문을 통한 비교
		for (int i = 0; i < usercount; i++)
		{

			//	아이디, 비밀번호 확인
			if (strcmp(id, logininfo[i].loginID) == 0 && strcmp(pw, logininfo[i].loginPW) == 0)
			{
				//	관리자
				if (logininfo[i].accountType == ACCOUNT_TYPE_ADMIN)
				{
					printf("\n관리자 %s님 환영합니다.\n", logininfo[i].loginID);
					wrongcount = 0;
					return logininfo[i].accountType;
				}

				//	사용자
				else
				{
					printf("\n사용자 %s님 환영합니다.\n", logininfo[i].loginID);
					wrongcount = 0;
					return logininfo[i].accountType;
				}
			}
		}

		//	로그인 실패
		printf("로그인 실패 : 아이디 또는 비밀번호가 잘못되었습니다.\n\n");
		wrongcount++;
	}
}
