
#pragma once

#include <process.h>
#include "gameFigure.h"

void gameStart(const char* _Id) {
	system("cls");
	system("mode con cols=51 lines=30");
	cursorDisplay("hide");
	layout_game();

	// init game
	user_info player = *userInfo_get(_Id);

	unsigned int score = 0;
	unsigned long delta_time = 0;
	char keyIn[6];
	bool EndofGame = false, WriteRecord = true;

	cursorMove_abs(4, 6);	printf("게임을 시작하려면 아무 키를 눌러주세요.");
	Map_init(obj_player_default, Map_reduced); // 맵만들기
	Map_print(5, 8);
	while (!_kbhit());	// 키 입력 있을 때 시작
	cursorMove_abs(4, 6);	printf("                                         ");

	//게임 시작

	do {
		Map_print(5, 8);

		cursorMove_abs(4, 17);	printf("[ score : %6d ]", score);

		strcpy(keyIn, Player_keyIn());
		if (strSame(keyIn, "ESC")) {
			WriteRecord = false;
			break;
		}

		Player_move(obj_player_default, keyIn, obj_barrier, obj_car, obj_route, &score, &EndofGame);

		Sleep(1);
		delta_time++;

		if (delta_time % 50 == 0 && delta_time != 0) {
			Map_objMove(obj_player_default, obj_car, &EndofGame);
			delta_time = 0;
		}
	} while (!EndofGame);
	cursorMove_abs(15, 22);	printf("Game Over");

	if (WriteRecord) {

		unit_record record = { 0, };			// record 만들기
		record.record = score;
		char* endTime = timeStamp();
		strcpy(record.endTime, endTime);
		userHistory_append(_Id, record);		// 기록 갱신
		
		user_history his = *userHistory_get(_Id);
		userRank_write(_Id, his.best.record);	// 랭크갱신

		
		cursorMove_abs(17, 8);	printf("%s", endTime);			// 끝난 시각,점수 확인용
		cursorMove_abs(18, 8);	printf("Score : %u", score);
	}
	cursorMove_abs(21, 8);	printf("[ENTER]를 눌러 새게임");
	cursorMove_abs(22, 8);	printf("[ESC]를 눌러 메인화면으로");

	unsigned char Endkey=0;
	while(true){
		Endkey = _getch();
		if (13 == Endkey) {		// ENTER 이면 새게임
			gameStart(_Id);
		}
		else if(27==Endkey){	// ESC 이면 종료
			return;
		}
		else if (224 == Endkey) {	// 방향키 같은 두개의 입력 무시
			_getch();
			continue;
		}

	}
}