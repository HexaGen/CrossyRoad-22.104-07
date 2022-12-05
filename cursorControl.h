#pragma once
/*
* ANSI C�� ESCAPE SEQ.�� �̿��Ѵ�.
* �ܼ��� ������ '����'(������, ������)�� ���� ����� �޶�����.
*/
#define ESC "\x1b"		// ESCape
#define CSI "\x1b["		// Control Sequence Introducer

#define UP 'A'
#define RIGHT 'C'  
#define DOWN 'B'
#define LEFT 'D'

// ANSI C�� �� ���� �ڵ�
typedef enum color { _Black, _Red, _Green, _Yellow, _Blue, _Magenta, _Cyan, _White, _Default } COLOR_SET;
typedef enum style { _None, _Bold, _Italic = 3, _Underline = 4 } STYLE_SET;
typedef enum foreback { _Fore = 3, _Back = 4 } FOREBACK_SET;

// Ŀ���� ���
void cursorDisplay(const char* _Mode) {
	printf(CSI"5 q");			// Ŀ�� ����� '_'���� �츮�� �˰� �ִ� '|'����
	if ("hide" == _Mode)
		printf(CSI"?25l");		// Ŀ�� �����
	else if ("reveal" == _Mode)
		printf(CSI"?25h");		// Ŀ�� ���̱�
}


void deleteConsoleUnitLine() {
	printf(CSI"2K");			// Ŀ���� ��ġ�ϴ� �ش� ��(line)�� ��� ����(' ')���� �ٲٱ�
	printf("\r");				// Ŀ���� ��ġ�ϴ� �ش� ��(line)�� ���� ������ ������
}
void txt_style(const int _Style) {
	printf(CSI"%dm", _Style);	// ���� 
}
void txt_foreColor(const int _Color) {
	printf(CSI"%d%dm", _Fore, _Color);		// ���ڻ� ����
}
void txt_backColor(const int _Color) {
	printf(CSI"%d%dm", _Back, _Color);		// ���ڹ��� ����
}
void txt_allReset() {
	printf(CSI"0m");						// ���ڹ����� �ʱ�ȭ
}

void txtDesign(const int _Style, const int _ForeColor, const int _BackColor) {
	txt_style(_Style);
	txt_foreColor(_ForeColor);
	txt_backColor(_BackColor);
}

void deleteConsoleLine(int _Lines) {
	for (int i = 0; i < _Lines; i++) {
		deleteConsoleUnitLine();
		if (i != _Lines - 1)
			printf(CSI"1A");	// Ŀ���� ���� ������ ('\n'[LINE FEED]�� �ݴ� ����)
	}
}

void cursorMove_abs(int row, int col) {
	printf(CSI"%d;%dH", row, col);
}
void cursorMove(int row, int col) {
	char rowShift = DOWN;
	char colShift = RIGHT;
	if (row < 0)
		rowShift = UP;
	if (col < 0)
		colShift = LEFT;
	printf(CSI"%d%c", abs(row), rowShift); printf(CSI"%d%c", abs(col), colShift);
}