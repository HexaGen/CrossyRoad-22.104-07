#define _CRT_SECURE_NO_WARNINGS

// LIBRARY
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>

//USER UNIVERSAL
#include "extendedFunc.h"
#include "cursorControl.h"
#include "style.h"

//INNER PROGRAM
#include "userControl.h"
#include "game.h"


void titleMain(void);
void loginMain(void);
void registerationMain(void);
void exitMain(void);

void innerMain(const char* _Id);
void rankingMain(const char* _Id);
void gotchaMain(const char* _Id);
void profileMain(const char* _Id);
void gameMain(const char* _Id);

const unsigned int gotchaCost = 500;
void gotchaStart(_Id);
void history_print(user_history, int, int, int);

void DEBUG_MAIN(void);

int main(void) {
	srand((unsigned int)time(NULL));
	/*
	debugALL();
	//user_history user_record = *userHistory_get("1q1q");
	user_history user_record = *userHistory_get("test");
	//user_history user_record = *userHistory_get("testlow");

	printf("[%s %u]\n\n", user_record.best.endTime, user_record.best.record);
	//userRank_write(user_record.id, user_record.best.endTime, user_record.best.record);

	user_ranks rankings = *userRank_get();
	for (int i = 0; i < 10; i++) {
		printf("\n[%d]%s(%s) - %u",i, rankings.user[i].id, rankings.user[i].nickname, rankings.user[i].best.record);

	}
	//gotchaMain("1q1q");
	*/
	cursorMove_abs(0, 0);
	cursorDisplay("hide");
	logoPrint(); printf("\n");

	unsigned int currentButton = 0;
	bool NEXT = false;
	while (true) {
		titleMainButton(currentButton);
		buttonState(&currentButton, TITLE_TOTAL_BUTTON, &NEXT);
		deleteConsoleLine(TITLE_TOTAL_BUTTON + 1);
		if (NEXT) {
			cursorDisplay("reveal");
			switch (currentButton)
			{
			case 0:
				loginMain();
				break;
			case 1:
				registerationMain();
				break;
			case 2:
				exitMain();
			}
		}
	}


	
	return 0;
}


void exitMain(void) {
	cursorDisplay("hide");

	printf("%60s", "[END]");
	exit(0);
}
void titleMain(void) {
	cursorDisplay("hide");

	unsigned int currentButton = 0;
	bool NEXT = false;
	while (true) {
		titleMainButton(currentButton);
		buttonState(&currentButton, TITLE_TOTAL_BUTTON, &NEXT);
		deleteConsoleLine(TITLE_TOTAL_BUTTON+1);
		if (NEXT) {
			cursorDisplay("reveal");
			switch (currentButton)
			{
			case 0:
				loginMain();
				break;
			case 1:
				registerationMain();
				break;
			case 2:
				exitMain();
			}
		}
	}
}
void loginMain(void) {
	int attempt = 0;
	char *id_input, *pw_input;
	for (int i = 0; i < 3; i++) {
		printf("%s", alignSpace_Q1p5);
		id_input = userInput_id("ID");
		if (NULL == id_input) { deleteConsoleLine(1); break; }

		printf("%s", alignSpace_Q1p5);
		pw_input = userInput_pw("PW");
		if (NULL == pw_input) { deleteConsoleLine(2); break; }
		deleteConsoleLine(3);

		if (NULL == userInfo_get(id_input)) {
			printf("%s", alignSpace_Q1);
			printf("회원정보가 없습니다. 가입하시겠습니까? y[Y]/n[N] : ");
			char c = getchar();
			if (c == '\n')
				getchar();	// 버퍼비우기
			deleteConsoleLine(2);
			if ('y' == c || 'Y' == c) {
				registerationMain();
			}
			else {
				titleMain();
			}
		}
		else {
			if (false == userPW_check(id_input, pw_input)) {
				printf("\n%s", alignSpace_Q1p5);
				printf("Password Incurrect");

				Sleep(850);
				deleteConsoleLine(2);

				attempt++;
			}
			else {
				printf("\n%s", alignSpace_Q1p5);
				txtDesign(_None, _White, _Blue);
				user_info t = *userInfo_get(id_input);
				printf("반갑습니다 \"%s\"님", t.nickname);
				txt_allReset();

				Sleep(1000);
				deleteConsoleLine(2);

				innerMain(id_input);
			}
		}

	}
	if (attempt == 2)
		printf("비밀번호를 3회 잘못 입력했습니다.");

	titleMain();
}
void registerationMain(void) {
	int attempt = 0;
	char *id_input, *nick_input, *pw_input;
	for (int i = 0; i < 1; i++) {
		printf("%s", alignSpace_Q1p5);
		id_input = userInput_id("ID");
		if (NULL == id_input) { deleteConsoleLine(1); break; }
		else if (NULL != userInfo_get(id_input)) {
			deleteConsoleLine(2);
			printf("%s", alignSpace_Q1p5);
			printf("사용중인 ID[%s]입니다.", id_input);

			Sleep(1250);
			deleteConsoleLine(1);
			registerationMain();
		}
		
		printf("%s", alignSpace_Q1p5);
		nick_input = userInput_id("NICKNAME");
		if (NULL == nick_input) { deleteConsoleLine(2); break; }
		
		printf("%s", alignSpace_Q1p5);
		pw_input = userInput_pw("PW");
		if (NULL == pw_input) { deleteConsoleLine(3); break; }

		deleteConsoleLine(4);
		// 데이터 추가.
		userInfo_write(id_input, nick_input);
		userHistory_write(id_input, nick_input);
		userPW_write(id_input, pw_input);

		printf("%s", alignSpace_Q1p5);
		printf("회원가입 완료!!");
		Sleep(1000);
		deleteConsoleLine(1);

		printf("%s", alignSpace_Q1p5);
		printf("입력한 ID/PW로 로그인해주세요");
		Sleep(850);
		deleteConsoleLine(1);
	}
	titleMain();
}


void innerMain(const char* _Id) {
	cursorMove_abs(0, 0);
	cursorDisplay("hide");
	/*
	{
		txtDesign(_Italic, _Yellow, _Blue);
		printf("[gameMain][mainSpace.c][initFunc] ID : %s", _Id);
		_getch();
		txt_allReset();
		deleteConsoleLine(2);
	}
	*/

	logoPrint(); printf("\n\n");

	unsigned int currentButton = 0;
	bool NEXT = false;
	while (true) {
		gameMainButton(currentButton);
		buttonState(&currentButton, GAME_TOTAL_BUTTON, &NEXT);
		deleteConsoleLine(2);
		if (NEXT) {
			cursorDisplay("reveal");
			switch (currentButton)
			{
			case 0:
				gameMain(_Id);
				break;
			case 1:
				rankingMain(_Id);
				break;
			case 2:
				gotchaMain(_Id);
				break;
			case 3:
				profileMain(_Id);
				break;
			case 4:
				main();
			}
		}
	}
}

void gameMain(const char* _Id) {
	cursorDisplay("hide");
	/*
	{
		txtDesign(_Italic, _Yellow, _Blue);
		printf("[gameMain][mainSpace.c][ initCheck ] ID : %s", _Id);
		txt_allReset();
		_getch();
		system("cls");
		//deleteConsoleLine(2);
	}
	*/
	gameStart(_Id);
	system("cls");
	system("mode con cols=120 lines=30");
	innerMain(_Id);
}

void rankingMain(const char* _Id) {
	system("cls");
	cursorDisplay("hide");
	layout_rank();
	/*
	{
		txtDesign(_Italic, _Yellow, _Blue);
		printf("[rankingMain][mainSpace.c][ initCheck ] ID : %s", _Id);
		txt_allReset();
		_getch();
		deleteConsoleLine(2);
	}
	*/
	//char* str = timeStamp();
	printf("%4s │ %32s │ %-32s │ %s", "RANK", "ID", "NICKNAME", "SCORE");

	user_ranks rankings = *userRank_get();
	for (int i = 0; i < 10; i++) {
		cursorMove_abs(3 + (i+1) * 2, 5);
		printf(" %02d  │ %32s │ %-32s │ %u", i+1, rankings.user[i].id, rankings.user[i].nickname, rankings.user[i].best.record);
		Sleep(25);
	}

	cursorMove_abs(26, 5);
	user_history user_record = *userHistory_get(_Id);
	if (0 != user_record.best.record)
		printf("MY BEST SCORE is '%d' (at %s )", user_record.best.record, user_record.best.endTime);
	else
		printf("YOU NEED TO PLAY A GAME for RECORD YOUR BEST SCORE");

	unsigned int currentButton = 0;

	bool NEXT = false;
	while (true) {
		cursorMove_abs(0, 7);
		rankingMainButton(currentButton);
		buttonState(&currentButton, 1, &NEXT);
		if (NEXT) {
			//cursorDisplay("reveal");
			switch (currentButton)
			{
			case 0:
				system("cls");
				innerMain(_Id);
			}
		}
	}

	innerMain(_Id);
}

void gotchaMain(const char* _Id) {
	system("cls");
	system("mode con cols=72 lines=30");
	cursorDisplay("hide");
	/*
	{
		txtDesign(_Italic, _Yellow, _Blue);
		printf("[gotchaMain][mainSpace.c][ initCheck ] ID : %s", _Id);
		txt_allReset();
		_getch();
		cursorMove_abs(0, 0);
		deleteConsoleLine(1);
	}
	//userInfo_print(_Id);
	//_getch();
	*/
	layout_gotcha();
	user_info targetUser = *userInfo_get(_Id);

	cursorMove_abs(16, 7);
	printf("반가워요 %s 님", targetUser.nickname);
	cursorMove_abs(17, 7);
	printf("[wallet : %-16u]", targetUser.wallet);

	unsigned int currentButton = 0;
	bool NEXT = false;

	while (true) {
		cursorMove_abs(0, 7);
		gotchaMainButton(currentButton);
		buttonState(&currentButton, GOTCHA_TOTAL_BUTTON, &NEXT);
		if (NEXT) {
			switch (currentButton)
			{
			case 0:
				gotchaStart(_Id);
				NEXT = false;
				break;
			case 1:
				system("mode con cols=120 lines=30");
				innerMain(_Id);
				break;
			}
		}
	}
}

void history_print(user_history hist,int now_index,int row, int col) {
	cursorMove_abs(row, col);
	int last_index = now_index + 7;
	if (last_index > 39) {
		last_index = 39;
		return;
	}
	for (int i = now_index; i <= now_index + 3; i++) {
		printf("[%2d] %s    %06d", i + 1, hist.total[i].endTime, hist.total[i].record);
		cursorMove_abs(row + 2 * (i - now_index + 1), col);
		Sleep(15);
	}
	cursorMove_abs(row, col + 40);
	for (int i = now_index + 4; i <= last_index; i++) {
		printf("[%2d] %s    %06d", i + 1, hist.total[i].endTime, hist.total[i].record);
		cursorMove_abs(row + 2 * (i - (now_index + 4) + 1), col + 40);
		Sleep(15);
	}
}
void nextHistory(int* HIS_NEXT) {
	if ((*HIS_NEXT) + 8 >= 40)
		return;
	(*HIS_NEXT)++;
}
void prevHistory(int* HIS_NEXT) {
	if ((*HIS_NEXT) - 1 < 0)
		return;
	(*HIS_NEXT)--;
}
void profileMain(const char* _Id) {
	/*
	{
		printf("[profileMain][mainSpace.c][ initCheck ] ID : %s", _Id);
		_getch();
		deleteConsoleLine(2);
	}
	*/
	user_info targetUser = *userInfo_get(_Id);
	user_history user_record = *userHistory_get(_Id);
	
	system("cls");
	cursorDisplay("hide");

	layout_profile();
	cursorMove_abs(4, 18);
	printf("%s", targetUser.nickname);

	cursorMove_abs(6, 18);
	printf("ID : %-32s", targetUser.id);

	char temp[50];
	sprintf(temp, "%s    %d", user_record.best.endTime, user_record.best.record);
	box_oneline(temp, 10, 19);
	box_oneline("Your Best", 10, 7);
	cursorMove_abs(10, 19);printf("┬");
	cursorMove_abs(12, 19);printf("┴");

	history_print(user_record, 0, 13, 21);

	//cursorMove_abs(0, 10);

	unsigned int currentButton = 0;
	unsigned int HIS_NEXT=0;
	bool NEXT = false;
	while (true) {
		cursorMove_abs(0, 7);
		//printf("%d", HIS_NEXT);
		profileMainButton(currentButton);
		buttonState(&currentButton, PROFILE_TOTAL_BUTTON, &NEXT);
		if (NEXT) {
			//cursorDisplay("reveal");
			if (0 == currentButton) {
				prevHistory(&HIS_NEXT);
				history_print(user_record, HIS_NEXT, 13, 21);
				NEXT = false;
				continue;
			}
			else if (1 == currentButton) {
				nextHistory(&HIS_NEXT);
				history_print(user_record, HIS_NEXT, 13, 21);
				NEXT = false;
				continue;
			}
			else if (2 == currentButton) {

			}
			else if (3 == currentButton) {
				system("cls");
				innerMain(_Id);
				break;
			}
		}
	}
	system("cls");
	innerMain(_Id);
}

//x86 에서만 돌아감
void gotchaStart(const char* _Id) {
	user_info targetUser = *userInfo_get(_Id);
	cursorMove_abs(5, 7);
	if (targetUser.wallet >= gotchaCost) {

		printf("뽑기할래요?(y[Y]/n[N]) : ");
		cursorDisplay("reveal");
		char GOTCHA = getchar();
		cursorDisplay("hide");
		deleteConsoleLine(2);
		//if (GOTCHA == '\n')
		//	_getch();
		if (GOTCHA == 'y' || GOTCHA == 'Y') {
			// 비용지불
			targetUser.wallet -= gotchaCost;
			userInfo_modify(_Id, targetUser);
			targetUser = *userInfo_get(_Id);

			double randomNum = random();
			int GOT_ITEM = 0;
			if (.6 <= randomNum && randomNum < .75) {
				GOT_ITEM = 1;
			}
			else if (.75 <= randomNum && randomNum < .85) {
				GOT_ITEM = 2;
			}
			else if (.85 <= randomNum && randomNum < .95) {
				GOT_ITEM = 3;
			}
			else if (.95 <= randomNum && randomNum < .975) {
				GOT_ITEM = 4;
			}
			else if (.975 <= randomNum && randomNum < 1.) {
				GOT_ITEM = 5;
			}

			//printf("%f, %d", randomNum, GOT_ITEM);

			if (GOT_ITEM) {
				if ('F' == targetUser.inventory[GOT_ITEM]) {
					targetUser.inventory[GOT_ITEM] = 'T';
					userInfo_modify(_Id, targetUser);
					targetUser = *userInfo_get(_Id);

					cursorMove_abs(5, 7);
					printf("새로운캐릭터! 축하합니다~");
					cursorMove_abs(17, 7);
					printf("[wallet : %-16u]", targetUser.wallet);

					Sleep(1250);
				}
				else if ('T' == targetUser.inventory[GOT_ITEM]) {
					targetUser.wallet += 200;
					userInfo_modify(_Id, targetUser);
					targetUser = *userInfo_get(_Id);

					cursorMove_abs(5, 7);
					printf("중복이넹 (0.<)9 - ☆");
					cursorMove_abs(17, 7);
					printf("[wallet : %-16u]", targetUser.wallet);

					Sleep(1250);
				}
				gotchaMain(_Id);
				return;
			}
			else {
				targetUser.wallet += 50;
				userInfo_modify(_Id, targetUser);
				targetUser = *userInfo_get(_Id);

				cursorMove_abs(5, 7);
				printf("아무것도 뽑지 못했습니다 ㅠ,ㅠ");
				cursorMove_abs(17, 7);
				printf("[wallet : %-16u]", targetUser.wallet);

				Sleep(1250);
			}
			gotchaMain(_Id);
			return;
		}
		else {
			gotchaMain(_Id);
			return;
		}
	}
	else {
		cursorMove_abs(5, 7);
		printf("뽑기에 필요한 비용(%u)이 부족합니다.", gotchaCost);
		Sleep(1250);

		cursorMove_abs(9, 7);
		printf("다음에 와주세요!   :]");
		Sleep(850);

		system("mode con cols=120 lines=30");
		innerMain(_Id);
	}
}




void DEBUG_MAIN(void) {
	//innerMain("test");
	//gameMain("testlow");
	if (NULL == userInfo_get("test") || userInfo_get("test")->wallet <= 1000) {
		userInfo_write("test", "TEST_ACCOUNT");
		userPW_write("test", "q1Q!");
		userHistory_write("test", "TEST_ACCOUNT");
		//userRank_write("test", "TEST_ACCOUNT");

		user_info test_account = *userInfo_get("test");
		test_account.wallet = 500000;
		userInfo_modify("test", test_account);
	}
	if (NULL == userInfo_get("testlow")) {
		userInfo_write("testlow", "TEST_ACCOUNT_LOW");
		userPW_write("testlow", "q1Q!");
		userHistory_write("testlow", "TEST_ACCOUNT_LOW");
		//userRank_write("testlow", "TEST_ACCOUNT_LOW");

		user_info test_account = *userInfo_get("testlow");
		test_account.wallet = 0;
		userInfo_modify("testlow", test_account);
		userInfo_print("testlow");
	}
	char* _Id = "test";
	unit_record nd0 = {0,};
	strcpy(nd0.endTime, timeStamp());
	nd0.record = 12;
	userHistory_append(_Id, nd0);
	Sleep(50);
	userHistory_print(_Id, "total");

	unit_record nd1 = { 0, };
	strcpy(nd1.endTime, timeStamp());
	nd1.record = 10;
	Sleep(50);
	userHistory_append(_Id, nd1);
	userHistory_print(_Id, "total");

	unit_record nd2 = { 0, };
	strcpy(nd2.endTime, timeStamp());
	nd2.record = 40;
	userHistory_append(_Id, nd2);
	userHistory_print(_Id, "total");

	_getch();
	/*
	*/
}