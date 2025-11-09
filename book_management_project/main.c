#include "structs.h"
#include "assistant.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

int main(void) {
	// 메인 화면 출력
	DisplayMainScreen();
	// 프로그램 종료 전 대기

	getchar();

	return 0;
}
