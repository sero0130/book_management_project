#include "database.h"
#include 
#include <stdio.h>
#include <string.h>

//데이터 베이스 관련 함수 작성

/*
* 함수명 : UserDatabaseSave()
* 기능 : 유저 데이터 user.txt 파일에 저장
* 매개변수 : 사용자 구조체 배열, 로그인 구조체 배열, 배열의 마지막 인덱스
* 반환 값 : 정수값
*/

DBERROR UserDatabaseSave(USER user[],LOGIN login[], int lastnum)
{
	FILE* userfp = fopen("user.txt", "w");
	if (userfp == NULL)
	{
		return DB_FILE_NOT_FOUND;
	}

	//파일 커서 위치 마지막으로 옮기기
	fseek(userfp, 0, SEEK_END);

	fprintf("%d | %s | %s | %s | %s\n",
		&user[lastnum].accountType,
		login[lastnum].loginID,
		login[lastnum].loginPW,
		user[lastnum].userName,
		user[lastnum].phoneNum);

	printf("사용자 등록 완료.");

	fclose(userfp);
	return DB_SUCCESS;
}

/*
* 함수명 : BookDatabaseSave()
* 기능 : book.txt에 저장하는 함수
* 매개변수 : book 구조체 배열, 배열 마지막 인덱스
* 반환값 : 정수값
*/

DBERROR BookDatabaseSave(BOOK book[],int lastnum)
{
	FILE* bookfp = fopen("book.txt","w");
	if (bookfp == NULL)
	{
		return DB_FILE_NOT_FOUND;
	}

	//파일 커서 옮기기
	fseek(bookfp, 0, SEEK_END);

	fprintf("%s | %s | %s | %s | %s | %s | %s\n",
		book[lastnum].bookID,
		book[lastnum].bookName,
		book[lastnum].writer,
		book[lastnum].translator,
		book[lastnum].bookStatus,
		book[lastnum].maker);

	printf("책 추가 완료.");
	fclose(bookfp);
	return DB_SUCCESS;
}

/*
* 함수명 : borrowDataSave()
* 기능 : 대여 상태 저장 함수
* 매개변수 : 
* 반환값 : 정수값
*/
/*
DBERROR borrowDataSave(BORROW borrow[], int lastnum)
{
	FILE * borrowfp = fopen("borrow.txt", "w");
	if (borrowfp == NULL)
	{
		return DB_FILE_NOT_FOUND;
	}

	//파일 끝으로 커서 옮기기
	fseek(borrowfp, 0, SEEK_END);

	//fprintf("%s | %s | %");

}
				제작중;
*/