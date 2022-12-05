#pragma once

#include <process.h>
#include "gameFigure.h"

void gameStart(const char* _Id) {
	system("cls");
	system("mode con cols=51 lines=30");
	cursorDisplay("hide");
	layout_game();
	/*
	{
		printf("[gameStart][game.h][initFunc] ID : %s\r", _Id);
		_getch();
		deleteConsoleLine(2);
	}
	*/

	// init game
	user_info player = *userInfo_get(_Id);
	char _Player = player.currentInven + 48;

	unsigned int score = 0;
	unsigned long delta_time = 0;
	char keyIn[6];
	bool EndofGame = false;
	bool WriteRecord = true;
	
	cursorMove_abs(4, 6);	printf("게임을 시작하려면 아무 키를 눌러주세요.");
	_getch();
	cursorMove_abs(4, 6);	printf("                                         ");

	//게임 시작
	Map_init(_Player, Map_reduced); // 맵만들기
	Map_print(5,8);

	do {
		Map_print(5,8);

		strcpy(keyIn, Player_keyIn());
		if (strSame(keyIn, "ESC")) {
			WriteRecord = false;
			break;
		}

		Player_move(_Player,keyIn, obj_barrier, obj_car, obj_route, &score, &EndofGame);

		Sleep(1);
		delta_time++;

		if (delta_time % 50 == 0 && delta_time != 0) {
			Map_objMove(_Player, obj_car, &EndofGame);
			delta_time = 0;
		}
		/*
		cursorMove_abs(21, 20);
		printf("time : %3d  ", delta_time);
		printf("(%d, %d)", player_pos.row, player_pos.col);
		*/
	} while (!EndofGame);

	cursorMove_abs(15, 22);
	printf("Game Over");
	if (WriteRecord) {
		char *endTime = timeStamp();
		// record 기록하기
		unit_record record = { 0, };
		record.record = score;
		strcpy(record.endTime, endTime);
		userHistory_append(_Id, record);

		// 스코어만큼 재화지급
		player.wallet += score;
		userInfo_modify(_Id, player);

		// 끝난 시각과 점수 확인용
		cursorMove_abs(17, 8);	printf("%s", endTime);
		cursorMove_abs(18, 8);	printf("Score : %u", score);
	}
	cursorMove_abs(21, 8);	printf("[ENTER]를 눌러 새게임");
	cursorMove_abs(22, 8);	printf("[ESC]를 눌러 메인화면으로");

	char Endkey;
	do {
		Endkey = _getch();
		if (13 == Endkey) {
			gameStart(_Id);
		}
	}
	while (27 != Endkey);
}