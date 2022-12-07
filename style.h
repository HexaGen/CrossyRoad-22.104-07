#pragma once

#define LOGO_PATH "data/.logo"
#define LOGO_WIDTH 121
#define LOGO_HEIGTH 24

#define TITLE_TOTAL_BUTTON 3
#define GAME_TOTAL_BUTTON 4
#define PROFILE_TOTAL_BUTTON 3

//console MAX 120
//�������(IQR) �������� �ۼ���

// 120��
const char* alignSpace_Q5   = "                                                                                                                        ";
// 105��
const char* alignSpace_Q3p5 = "                                                                                                         ";
// 90��
const char* alignSpace_Q3   = "                                                                                          ";
const char* alignSpace_Q2p5 = "                                                                           ";// 75��
const char* alignSpace_Q2   = "                                                            ";// 60��
const char* alignSpace_Q1p5 = "                                             ";// 45��
const char* alignSpace_Q1   = "                              ";// 30��
const char* alignSpace_Q0p5 = "               ";// 15��
const char* alignSpace_Q0   = "";// 0��

void box_oneline(const char* _Str, int row, int col) {
	int _Length = strlen(_Str);
	cursorMove_abs(row, col);
	printf("��"); for (int i = 0; i < _Length + 2; i++) { printf("��"); }; printf("��");

	cursorMove_abs(row+1, col);
	printf("�� "); printf("%s",_Str); printf(" ��");
	
	cursorMove_abs(row+2, col);
	printf("��"); for (int i = 0; i < _Length+2; i++) { printf("��"); }; printf("��");
}

//������������������ ����
void layout_default(void) {
	cursorMove_abs(0, 0);
	int i;
	//ù��° ��
	printf("��");
	for (i = 0; i < 117; i++) printf("��");
	printf("��\n");
	//���� ù��° ��
	printf("�� ��");
	for (i = 0; i < 113; i++) printf("��");
	printf("�� ��\n");


	for (i = 0; i < 24; i++) printf("�� ��%113s�� ��\n", "");


	//���� ������ ��
	printf("�� ��");
	for (i = 0; i < 113; i++) printf("��");
	printf("�� ��\n");
	//������ ��
	printf("��");
	for (i = 0; i < 117; i++) printf("��");
	printf("��\n");

	cursorMove_abs(3,5);
}
void layout_rank(void) {
	layout_default();
	int i;
	cursorMove_abs(4, 3);
	printf("��");
	for (i = 0; i < 113; i++) printf("��");
	printf("��");

	cursorMove_abs(25, 3);
	printf("��");
	for (i = 0; i < 113; i++) printf("��");
	printf("��");

	cursorMove_abs(2, 10); printf("��");
	cursorMove_abs(2, 45); printf("��");
	cursorMove_abs(2, 80); printf("��");

	cursorMove_abs(4, 10); printf("��");
	cursorMove_abs(4, 45); printf("��");
	cursorMove_abs(4, 80); printf("��");

	cursorMove_abs(3, 5);
}

void layout_profile(void)
{
	cursorMove_abs(0, 0);

	int i;

	//ù��° ��
	printf("��");
	for (i = 0; i < 117; i++) printf("��");
	printf("��\n");

	//���� ù��° ��
	//printf("��%117s��\n", "");
	//for (i = 0; i < 117; i++) printf("");

	//���� �ι�° ��
	printf("�� ��");
	for (i = 0; i < 10; i++) printf("��");
	printf("��");
	for (i = 0; i < 102; i++) printf("��");
	printf("�� ��\n");

	//���� �߰� ��
	for (i = 0; i < 5; i++) printf("�� ��          ��%102s�� ��\n", "");
	printf("�� ������������������������");
	for (i = 0; i < 102; i++) printf("��");
	printf("�� ��\n");
	for (i = 0; i < 12; i++) printf("�� ��%113s�� ��\n", "");
	printf("�� ��");
	for (i = 0; i < 113; i++) printf("��");
	printf("�� ��\n");
	for (i = 0; i < 5; i++) printf("�� ��%113s�� ��\n", "");

	//���� ������1 ��
	printf("�� ��");
	for (i = 0; i < 113; i++) printf("��");
	printf("�� ��\n");

	//���� ������2 ��
	//printf("��%117s��\n", "");
	//for (i = 0; i < 113; i++) printf("");

	//������ ��
	printf("��");
	for (i = 0; i < 117; i++) printf("��");
	printf("��\n");

	cursorMove_abs(3, 5);
}
void layout_gotcha(void) {
	cursorMove_abs(0, 0);

	int i;
	//ù��° ��
	printf("��");
	for (i = 0; i < 69; i++) printf("��");
	printf("��\n");
	//���� ù��° ��
	printf("�� ��");
	for (i = 0; i < 65; i++) printf("��");
	printf("�� ��\n");


	for (i = 0; i < 25; i++) printf("�� ��%65s�� ��\n", "");


	//���� ������ ��
	printf("�� ��");
	for (i = 0; i < 65; i++) printf("��");
	printf("�� ��\n");
	//������ ��
	printf("��");
	for (i = 0; i < 69; i++) printf("��");
	printf("��\n");

	cursorMove_abs(3, 5);
}
void layout_game(void) {
	cursorMove_abs(0, 0);

	int i;
	//ù��° ��
	printf("��");
	for (i = 0; i < 48; i++) printf("��");
	printf("��\n");
	//���� ù��° ��
	printf("�� ��");
	for (i = 0; i < 44; i++) printf("��");
	printf("�� ��\n");


	for (i = 0; i < 25; i++) printf("�� ��%44s�� ��\n", "");


	//���� ������ ��
	printf("�� ��");
	for (i = 0; i < 44; i++) printf("��");
	printf("�� ��\n");
	//������ ��
	printf("��");
	for (i = 0; i < 48; i++) printf("��");
	printf("��\n");

	cursorMove_abs(3, 5);
}

// �ΰ� ����ϱ�
void logoPrint() {
	FILE* logoFile = fopen(LOGO_PATH, "r");
	if (NULL == logoFile) {
		printf("[logoPrint][gameFigure.h][ ERROR ] there is noting in \"%s\"", LOGO_PATH);
		return;
	}
	else {
		char logo[LOGO_HEIGTH][LOGO_WIDTH] = { 0, };
		for (int i = 0; i < LOGO_HEIGTH; i++) {
			fgets(logo[i], LOGO_WIDTH + 1, logoFile);
			printf("%s", logo[i]);
		}
		printf("\n");
	}
	//printf("[LOGO END]");	//�ӽ�
	fclose(logoFile);
}

// _Print : ��ư�̸�, DISPLAY_CURRENT : ���� ��ư�� ��ġ
void unitButton(const char* _Print, bool DISPLAY_CURRENT) {
	if (DISPLAY_CURRENT)
		printf("  > ");
	else
		printf("    ");
	printf("%s", _Print);
}

// _Controller : �����ư��ġ, _MAX : �ִ� ��ư ����, NEXT : �����ൿ���� �÷��׺���
void buttonState(unsigned int* _Controller, const unsigned int _MAX, bool* NEXT) {
	int key;
	while (true) {
		key = _getch();
		//����ġ�� �����ൿ!
		if (key == 224) {
			//����Ű�� �� �� ����� �޾���
			key = _getch();
			if (key == 80 || key == 72 || key == 75 || key == 77)
				break;
			else
				continue;
		}
		else if (key == 13) {
			*NEXT = true;
			return;
			//return *_Controller;
		}
	}

	//UP(72), DOWN(80)
	if ((key == 80 || key == 77) && ((*_Controller) + 1) < _MAX) {
		(*_Controller)++;
	}
	else if ((key == 72 || key == 75) && (*_Controller) > 0) {
		(*_Controller)--;
	}
	//printf("[1][%u %d %d]", *_Controller, _MAX, *_Controller < _MAX);
}

void titleMainButton(const unsigned int _type) {
	if (0 == _type) {
		printf("%s", alignSpace_Q1p5);
		txtDesign(_Bold, _Black, _White);
		unitButton("login       ", true);
		txt_allReset(); putchar('\n');

		printf("%s", alignSpace_Q1p5);
		unitButton("register\n", false);
		printf("%s", alignSpace_Q1p5);
		unitButton("exit\n", false);
	}
	else if (1 == _type) {
		printf("%s", alignSpace_Q1p5);
		unitButton("login\n", false);

		printf("%s", alignSpace_Q1p5);

		txtDesign(_Bold, _Black, _White);
		unitButton("register    ", true);
		txt_allReset(); putchar('\n');

		printf("%s", alignSpace_Q1p5);
		unitButton("exit\n", false);
	}
	else if (2 == _type) {
		printf("%s", alignSpace_Q1p5);
		unitButton("login\n", false);
		printf("%s", alignSpace_Q1p5);
		unitButton("register\n", false);

		printf("%s", alignSpace_Q1p5);

		txtDesign(_Bold, _Black, _White);
		unitButton("exit        ", true);
		txt_allReset(); putchar('\n');
	}
}

void gameMainButton(const unsigned int _type) {
	char* align = "                          ";
	if (0 == _type) {
		printf("%s", align);
		txtDesign(_Bold, _Black, _White);
		unitButton("GameStart   ", true);
		txt_allReset();

		unitButton("Ranking     ", false);
		unitButton("Profile     ", false);
		unitButton("Logout      \n", false);

	}
	else if (1 == _type) {
		printf("%s", align);
		unitButton("GameStart   ", false);

		txtDesign(_Bold, _Black, _White);
		unitButton("Ranking     ", true);
		txt_allReset();

		unitButton("Profile     ", false);
		unitButton("Logout      \n", false);
	}
	else if (2 == _type) {
		printf("%s", align);
		unitButton("GameStart   ", false);
		unitButton("Ranking     ", false);

		txtDesign(_Bold, _Black, _White);
		unitButton("Profile     ", true);
		txt_allReset();

		unitButton("Logout      \n", false);
	}
	else if (3 == _type) {
		printf("%s", align);
		unitButton("GameStart   ", false);
		unitButton("Ranking     ", false);
		unitButton("Profile     ", false);

		txtDesign(_Bold, _Black, _White);
		unitButton("Logout      ", true);
		txt_allReset(); putchar('\n');
	}
}

void rankingMainButton(const unsigned int _type) {
	if (0 == _type) {
		txtDesign(_Bold, _Black, _White);
		unitButton("Back        ", true);
		txt_allReset(); putchar('\n');
	}
}

void profileMainButton(const unsigned int _type) {
	char* align = "                  ";
	if (0 == _type) {
		txtDesign(_Bold, _Black, _White);
		unitButton("PrevPage    ", true);
		txt_allReset();
		unitButton("NextPage    ", false);

		unitButton("Back        ", false);
	}
	else if (1 == _type) {
		unitButton("PrevPage    ", false);

		txtDesign(_Bold, _Black, _White);
		unitButton("NextPage    ", true);
		txt_allReset();

		unitButton("Back        ", false);
	}

	else if (2 == _type) {
		unitButton("PrevPage    ", false);
		unitButton("NextPage    ", false);

		txtDesign(_Bold, _Black, _White);
		unitButton("Back        ", true);
		txt_allReset();
	}
}