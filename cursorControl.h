#pragma once
/*
* ANSI C의 ESCAPE SEQ.를 이용한다.
* 단순히 이진수 '숫자'(숫자형, 문자형)에 따라서 기능이 달라진다.
*/
#define ESC "\x1b"		// ESCape
#define CSI "\x1b["		// Control Sequence Introducer

#define UP 'A'
#define RIGHT 'C'  
#define DOWN 'B'
#define LEFT 'D'

// ANSI C의 색 설정 코드
typedef enum color { _Black, _Red, _Green, _Yellow, _Blue, _Magenta, _Cyan, _White, _Default } COLOR_SET;
typedef enum style { _None, _Bold, _Italic = 3, _Underline = 4 } STYLE_SET;
typedef enum foreback { _Fore = 3, _Back = 4 } FOREBACK_SET;

// 커서의 모양
void cursorDisplay(const char* _Mode) {
	printf(CSI"5 q");			// 커서 모양을 '_'에서 우리가 알고 있는 '|'으로
	if ("hide" == _Mode)
		printf(CSI"?25l");		// 커서 숨기기
	else if ("reveal" == _Mode)
		printf(CSI"?25h");		// 커서 보이기
}


void deleteConsoleUnitLine() {
	printf(CSI"2K");			// 커서가 위치하는 해당 줄(line)을 모두 공백(' ')으로 바꾸기
	printf("\r");				// 커서가 위치하는 해당 줄(line)의 가장 앞으로 보내기
}
void txt_style(const int _Style) {
	printf(CSI"%dm", _Style);	// 글자 
}
void txt_foreColor(const int _Color) {
	printf(CSI"%d%dm", _Fore, _Color);		// 글자색 설정
}
void txt_backColor(const int _Color) {
	printf(CSI"%d%dm", _Back, _Color);		// 글자배경색 설정
}
void txt_allReset() {
	printf(CSI"0m");						// 글자및형식 초기화
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
			printf(CSI"1A");	// 커서를 위로 보내기 ('\n'[LINE FEED]의 반대 역할)
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