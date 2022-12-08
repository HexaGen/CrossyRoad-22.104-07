
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

	cursorMove_abs(4, 6);	printf("������ �����Ϸ��� �ƹ� Ű�� �����ּ���.");
	Map_init(obj_player_default, Map_reduced); // �ʸ����
	Map_print(5, 8);
	while (!_kbhit());	// Ű �Է� ���� �� ����
	cursorMove_abs(4, 6);	printf("                                         ");

	//���� ����

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

		unit_record record = { 0, };			// record �����
		record.record = score;
		char* endTime = timeStamp();
		strcpy(record.endTime, endTime);
		userHistory_append(_Id, record);		// ��� ����
		
		user_history his = *userHistory_get(_Id);
		userRank_write(_Id, his.best.record);	// ��ũ����

		
		cursorMove_abs(17, 8);	printf("%s", endTime);			// ���� �ð�,���� Ȯ�ο�
		cursorMove_abs(18, 8);	printf("Score : %u", score);
	}
	cursorMove_abs(21, 8);	printf("[ENTER]�� ���� ������");
	cursorMove_abs(22, 8);	printf("[ESC]�� ���� ����ȭ������");

	unsigned char Endkey=0;
	while(true){
		Endkey = _getch();
		if (13 == Endkey) {		// ENTER �̸� ������
			gameStart(_Id);
		}
		else if(27==Endkey){	// ESC �̸� ����
			return;
		}
		else if (224 == Endkey) {	// ����Ű ���� �ΰ��� �Է� ����
			_getch();
			continue;
		}

	}
}