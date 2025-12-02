#define _CRT_SECURE_NO_WARNINGS
#include "book.h"
#include "database.h"
#include "assistant.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int FindBookIndexById(const char* bookId)
{
    if (bookId == NULL) return -1;

    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(books[i].bookID, bookId) == 0)
            return i;
    }
    return -1;
}

void SearchBook(const char* keyword)
{
    ClearConsole();
    DrawSquare(100, 30, 0, 0);
    MoveCursor(2, 1);
    printf("[ 검색어 : %s ]\n", keyword);

    int found = 0;
    int y = 3;  // 출력 시작 위치

    for (int i = 0; i < bookCount; i++)
    {
        // 책 제목 또는 작가에 keyword 포함되는지 검사
        if (strstr(books[i].bookName, keyword) != NULL ||
            strstr(books[i].writer, keyword) != NULL)
        {
            found = 1;

            MoveCursor(2, y++);
            printf("──────────────────────────────────────────────────────────────────────────");

            MoveCursor(2, y++);
            printf("책 ID : %s", books[i].bookID);

            MoveCursor(2, y++);
            printf("제목 : %s", books[i].bookName);

            MoveCursor(2, y++);
            printf("저자 : %s", books[i].writer);

            MoveCursor(2, y++);
            printf("출판사 : %s", books[i].maker);

            MoveCursor(2, y++);
            printf("대여 상태 : %s",
                books[i].bookStatus == BOOK_AVAILABLE ? "대여 가능" : "대여 중");

            y++;
        }
    }

    if (!found)
    {
        MoveCursor(2, y + 2);
        printf("검색 결과가 없습니다.");
    }

    MoveCursor(2, y + 4);
    printf("계속하려면 아무 키나 누르세요...");
    _getch();
}

void DisplayBookListInArea(void)
{

    // 출력 가능한 행 수 (헤더 1줄 제외)
    int maxRows = BOOK_AREA_Y2 - BOOK_AREA_Y1 - 1;   // 28 - 6 - 1 = 21줄

    // ─ 헤더 출력 ─
    MoveCursor(BOOK_AREA_X1, BOOK_AREA_Y1);
    // 컬럼 폭: ID(8) 제목(30) 저자(15) 출판사(15) 상태(6) 정도로 배치
    printf("ID      %-30s %-15s %-15s %-6s",
        "제목", "저자", "출판사", "상태");

    // 이전 내용 지우기용으로 영역 안을 대충 공백으로 한번 싹 지워줘도 됨
    for (int y = BOOK_AREA_Y1 + 1; y <= BOOK_AREA_Y2; y++)
    {
        MoveCursor(BOOK_AREA_X1, y);
        for (int x = BOOK_AREA_X1; x <= BOOK_AREA_X2; x++)
            printf(" ");
    }

    // ─ 책 목록 출력 ─
    int row = 0;
    for (int i = 0; i < bookCount && row < maxRows; i++, row++)
    {
        int y = BOOK_AREA_Y1 + 1 + row;

        char statusStr[16] = { 0 };
        if (books[i].bookStatus == BOOK_AVAILABLE)
            strcpy(statusStr, "가능");
        else
            strcpy(statusStr, "대여중");

        MoveCursor(BOOK_AREA_X1, y);
        printf("%-8s %-30.30s %-15.15s %-15.15s %-6.6s",
            books[i].bookID,
            books[i].bookName,
            books[i].writer,
            books[i].maker,
            statusStr);
    }

    // 만약 책이 더 있는데 영역이 부족하면 표시
    if (bookCount > maxRows)
    {
        MoveCursor(BOOK_AREA_X1, BOOK_AREA_Y2);
        printf("※ %d권 중 %d권만 표시됨", bookCount, maxRows);
    }
}

void AddBookInteractive(void)
{
    BOOK newBook;
    memset(&newBook, 0, sizeof(BOOK));

    ClearConsole();
    printf("==== 책 추가 ====\n");

    printf("책 ID 입력 (예: 4301): ");
    scanf("%29s", newBook.bookID);

    // ID 중복 검사
    if (FindBookIndexById(newBook.bookID) != -1)
    {
        printf("이미 존재하는 책 ID 입니다.\n");
        _getch();
        return;
    }

    printf("책 제목 입력: ");
    getchar();  // 앞 scanf의 개행 제거
    fgets(newBook.bookName, MAX_BOOK_NAME_LENGTH, stdin);
    newBook.bookName[strcspn(newBook.bookName, "\r\n")] = '\0';

    printf("저자 입력: ");
    fgets(newBook.writer, MAX_WRITER_LENGTH, stdin);
    newBook.writer[strcspn(newBook.writer, "\r\n")] = '\0';

    printf("출판사 입력: ");
    fgets(newBook.maker, MAX_MAKER_LENGTH, stdin);
    newBook.maker[strcspn(newBook.maker, "\r\n")] = '\0';

    // 기본 상태는 대여 가능
    newBook.bookStatus = BOOK_AVAILABLE;

    // 메모리 상 books 배열에 추가
    AddBook(newBook);

    // DB 파일에 1권만 append
    DBERROR err = BookDatabaseAppend(bookCount - 1);
    if (err != DB_SUCCESS)
    {
        printf("DB 저장 중 오류 발생 (코드: %d)\n", err);
    }
    else
    {
        printf("책이 성공적으로 추가되었습니다.\n");
    }

    _getch();
}

void EditBookInteractive(void)
{
    char id[MAX_BOOK_ID_LENGTH] = { 0 };

    ClearConsole();
    printf("==== 책 수정 ====\n");
    printf("수정할 책 ID 입력: ");
    scanf("%29s", id);

    int idx = FindBookIndexById(id);
    if (idx == -1)
    {
        printf("해당 ID의 책을 찾을 수 없습니다.\n");
        _getch();
        return;
    }

    // 현재 정보 출력
    printf("\n[현재 정보]\n");
    printf("ID : %s\n", books[idx].bookID);
    printf("제목 : %s\n", books[idx].bookName);
    printf("저자 : %s\n", books[idx].writer);
    printf("출판사 : %s\n", books[idx].maker);
    printf("상태 : %s\n",
        books[idx].bookStatus == BOOK_AVAILABLE ? "대여 가능" : "대여 중");

    getchar(); // 입력 버퍼 개행 제거

    // 새 정보 입력
    char buffer[512];

    printf("\n새 제목 입력 (그대로 두려면 엔터): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n')
    {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        strncpy(books[idx].bookName, buffer, MAX_BOOK_NAME_LENGTH - 1);
        books[idx].bookName[MAX_BOOK_NAME_LENGTH - 1] = '\0';
    }

    printf("새 저자 입력 (그대로 두려면 엔터): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n')
    {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        strncpy(books[idx].writer, buffer, MAX_WRITER_LENGTH - 1);
        books[idx].writer[MAX_WRITER_LENGTH - 1] = '\0';
    }

    printf("새 출판사 입력 (그대로 두려면 엔터): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n')
    {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        strncpy(books[idx].maker, buffer, MAX_MAKER_LENGTH - 1);
        books[idx].maker[MAX_MAKER_LENGTH - 1] = '\0';
    }

    printf("상태 변경? (0: 대여중, 1: 대여 가능, 엔터: 유지): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n')
    {
        int st = atoi(buffer);
        if (st == 0) books[idx].bookStatus = BOOK_NOT_AVAILABLE;
        else if (st == 1) books[idx].bookStatus = BOOK_AVAILABLE;
    }

    // 전체를 다시 저장
    DBERROR err = BookDatabaseSave(bookCount - 1);
    if (err != DB_SUCCESS)
    {
        printf("DB 저장 중 오류 발생 (코드: %d)\n", err);
    }
    else
    {
        printf("책 정보가 수정되었습니다.\n");
    }

    _getch();
}

void RemoveBookInteractive(void)
{
    char id[MAX_BOOK_ID_LENGTH] = { 0 };

    ClearConsole();
    printf("==== 책 삭제 ====\n");
    printf("삭제할 책 ID 입력: ");
    scanf("%29s", id);

    int idx = FindBookIndexById(id);
    if (idx == -1)
    {
        printf("해당 ID의 책을 찾을 수 없습니다.\n");
        _getch();
        return;
    }

    // 대여 중인 책이면 삭제 불가 (권장)
    if (books[idx].bookStatus == BOOK_NOT_AVAILABLE)
    {
        printf("현재 대여 중인 책은 삭제할 수 없습니다.\n");
        _getch();
        return;
    }

    printf("\n다음 책을 삭제합니다.\n");
    printf("ID : %s\n", books[idx].bookID);
    printf("제목 : %s\n", books[idx].bookName);
    printf("정말 삭제하시겠습니까? (Y/N): ");

    char c;
    getchar();  // 버퍼 정리
    c = (char)getchar();
    if (c != 'Y' && c != 'y')
    {
        printf("\n삭제를 취소했습니다.\n");
        _getch();
        return;
    }

    // 배열에서 한 칸 땡기기 (idx 뒤의 것들을 앞으로 복사)
    for (int i = idx; i < bookCount - 1; i++)
    {
        books[i] = books[i + 1];
    }

    bookCount--;

    // 메모리 줄이기(실패해도 논리적으로는 이미 삭제된 상태라 큰 문제는 없음)
    if (bookCount > 0)
    {
        BOOK* temp = realloc(books, sizeof(BOOK) * bookCount);
        if (temp != NULL)
            books = temp;
    }
    else
    {
        // 하나도 안 남으면 메모리 해제
        free(books);
        books = NULL;
    }

    // 전체 DB 다시 저장
    DBERROR err = BookDatabaseSave(bookCount - 1);
    if (err != DB_SUCCESS)
    {
        printf("DB 저장 중 오류 발생 (코드: %d)\n", err);
    }
    else
    {
        printf("책이 삭제되었습니다.\n");
    }

    _getch();
}