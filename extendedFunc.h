#pragma once

#define TIME_STR_SIZE 22
bool strSame(const char* str1, const char* str2) {
	bool thisisSTR = strcmp(str1, str2) == 0 ? true : false;
	return thisisSTR;
}

void strSwap(char* str1, char* str2) {
	if (sizeof(str1) != sizeof(str2)) {
		printf("[strSwap][extendedFunc.h][ ERROR ] %s와 %s의 SIZE가 다릅니다.", str1, str2);
		return;
	}
	char* temp = malloc(sizeof(char) * sizeof(str1));
	strcpy(temp, str2);
	strcpy(str2, str1);
	strcpy(str1, temp);
	free(temp);
}

const char* timeStamp(void) {
	static char timeStr[TIME_STR_SIZE] = { 0, };
	time_t rawtime;
	struct tm* koreanStandardTime;

	time(&rawtime);
	koreanStandardTime = localtime(&rawtime);
	sprintf_s(
		timeStr, TIME_STR_SIZE,
		"%4d/%2d/%02d - %02d:%02d:%02d",
		koreanStandardTime->tm_year + 1900,
		koreanStandardTime->tm_mon + 1,
		koreanStandardTime->tm_mday,
		koreanStandardTime->tm_hour,
		koreanStandardTime->tm_min,
		koreanStandardTime->tm_sec
	);
	return timeStr;
}

// 0 ~ 1의 랜덤한 수를 반환
double random(void) { return rand() / ((double)RAND_MAX); }

// _Probability : 0~100
// if _Probability -> 35  100개중 35개 true 나머지는 false
bool uniformDisInt(int _Probability) {
	if (_Probability > 100)
		return true;
	else if (_Probability < 0)
		return false;
	int RN = (int)(random() * 100.);
	if (0 <= RN && RN < _Probability)
		return true;
	return false;
}

bool uniformDis(double _Probability) {
	if (_Probability > 1)
		return true;
	else if (_Probability < 0)
		return false;
	double RN = random();
	if (0 <= RN && RN < _Probability)
		return true;
	return false;
}