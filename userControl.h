#pragma once

//#include <stdio.h>
//#include <conio.h>
//#include <malloc.h>
//#include <string.h>
//#include "extendedFunc.h"
#include "style.h"

//우리가 쓸 상수들
//자료형 크기
#define USER_PASSWORD_MAX 32
#define USER_ID_MAX 32
#define USER_NICKNAME_MAX 32

#define USER_HISTORY_MAX 40
#define HISTORY_ROUTE_SIZE 54


//파일경로
#define USER_PASSWORD_FILE "data/.pw"
#define USER_INFO_FILE "data/user.data"
#define USER_RANK_FILE "data/.rankings"

#define USER_HISTORY_FILE "data/user_history/"

// 파일저장에 쓰일 구조체
typedef struct __password__ {
	char id[USER_ID_MAX];
	char password[USER_PASSWORD_MAX];
} user_password;

typedef struct __user__ {
	char id[USER_ID_MAX];
	char nickname[USER_NICKNAME_MAX];
} user_info;

//unit_record.endTime = "yyyy/mm/dd - hh:mm:ss" 21 + 1
typedef struct __unitRecord__ {
	char endTime[22];
	unsigned int record;
}unit_record;

typedef struct __history__ {
	char id[USER_ID_MAX];
	char nickname[USER_NICKNAME_MAX];
	unit_record best;
	unit_record total[USER_HISTORY_MAX];
}user_history;

typedef struct __unitRank__ {
	char id[USER_ID_MAX];
	char nickname[USER_NICKNAME_MAX];
	unit_record best;
}unit_rank;

typedef struct __rank__ {
	unit_rank user[10];
}user_ranks;

// 문자열함수에서 쓰기 위한 변수
// 놀랍게도 NULL == 0 이므로, strchr 사용시  문자열 맨앞에 ' '을 넣어 준다.
const char* ENGChar = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char* engChar = " abcdefghijklmnopqrstuvwxyz";
const char* numChar = " 0123456789";
const char* specialChar = " !#$%%&'()+,-.;<=>[]^_`{}@~";
const char* notAllowedChar = "  /\\:*?\"<>|";

// [MODE] 1. 대문자,   2. 소문자,   3. 숫자,   4. 특수문자   5. 비허용문자
bool checkCharType(const char c, const int _type) {
	bool result = false;
	// _type에 따라서 c가 대/소문자,숫자,특수문자인지 확인한다.
	switch (_type)
	{
	case ' ':
		result = ' ' == c ? true : false;
	case 1:
		result = strchr(ENGChar, c) ? true : false;
		break;
	case 2:
		result = strchr(engChar, c) ? true : false;
		break;
	case 3:
		result = strchr(numChar, c) ? true : false;
		break;
	case 4:
		result = strchr(specialChar, c) ? true : false;
		break;
	case 5:
		result = strchr(notAllowedChar, c) ? true : false;
		break;
	default:
		printf("[userControl.h][checkCharType] 올바르지 않은 argument (_type 입력)[FUNC_ERROR]\n");
		return false;
	}
	return result;
}


// #########################################################
// 파일 비밀번호
// #########################################################

//파일크기를 파일형식의크기로 나누어 유저들의 수
long userPopulation_get() {
	FILE* userPasswordData = fopen(USER_PASSWORD_FILE, "rb");
	if (NULL == userPasswordData) {
		//printf("[userPopulation_get][userControl.h][ ERROR ] there is noting in \"%s\"\n", USER_PASSWORD_FILE);
		return 0;
	}
	else {
		fseek(userPasswordData, 0, SEEK_END);	// 첫번째(0)에 있는 커서를 마지막(SEEK_END)로 옮겨준다.
		// 현재 파일 안에서의 커서를 첫번째를 기준으로 말해준다.(즉, 맨 마지막에 커서가 위치하면, 파일의 크기를 의미한다.)
		long fileSize = ftell(userPasswordData);
		return (fileSize / sizeof(user_password));
	}
}

// 패스워드추가
void userPW_write(const char* _Id, const char* _Password) {
	FILE* userPasswordData = fopen(USER_PASSWORD_FILE, "ab");
	user_password newUser = { 0, };

	strcpy(newUser.id, _Id);
	strcpy(newUser.password, _Password);

	fwrite(&newUser, sizeof(user_password), 1, userPasswordData);
	fclose(userPasswordData);
}

// true면 비번 일치 false면 ID 없거나 불일치
bool userPW_check(const char* _Id, const char* _Password) {
	FILE* userPasswordData = fopen(USER_PASSWORD_FILE, "rb");
	user_password targetUser = { 0, };

	if (NULL == userPasswordData) {
		printf("[userPW_check][userControl.h][ ERROR ] there is noting in \"%s\"\n", USER_PASSWORD_FILE);
		return false;
	}
	else {
		for (int i = 0; i < userPopulation_get(); i++) {
			fread(&targetUser, sizeof(user_password), 1, userPasswordData);
			if (strSame(_Id, targetUser.id))
				break;
		}

		fclose(userPasswordData);
		if (strSame(_Id, targetUser.id) && strSame(targetUser.password, _Password)) {
			//printf("[userPW_check][userControl.h][ EoF ] currect Password\n");
			return true;
		}
		else if (strSame(_Id, targetUser.id) && !strSame(targetUser.password, _Password)) {
			//printf("[userPW_check][userControl.h][ ERROR ] uncurrect Password\n");
			return false;
		}
	}
}


// #########################################################
//파일 유저정보
// #########################################################

// DB에 추가하기
void userInfo_write(const char* _Id, const char* _Nickname) {
	FILE* userData = fopen(USER_INFO_FILE, "ab");
	user_info newUser = { 0, };
	// 유저가 입력한 부분
	strcpy(newUser.id, _Id);
	strcpy(newUser.nickname, _Nickname);

	fwrite(&newUser, sizeof(user_info), 1, userData);
	fclose(userData);
}

/*
* NULL == _Id가 userData에 없다.		// 회원가입이 안된 사람
* NULL != _Id가 userData에 있다.		// 회원가입을 한 사람.
*/
user_info* userInfo_get(const char* _Id) {
	FILE* userData = fopen(USER_INFO_FILE, "rb");
	user_info targetUser = { 0, };
	if (NULL == userData) {
		//printf("[userInfo_get][userControl.h][ ERROR ] there is noting in \"%s\"\n", USER_INFO_FILE);
		return NULL;
	}
	else {
		long userPop = userPopulation_get();
		for (int i = 0; i < userPop + 1; i++) {
			fread(&targetUser, sizeof(user_info), 1, userData);
			if (strSame(targetUser.id, _Id))
				break;
			//printf("%s", feof(userData) ? "EOF" : "/");   //임시#####
		}
	}
	if (feof(userData)) {
		//printf("[userInfo_get][userControl.h][ ERROR ] there is no \"%s\" at \"%s\"\n", _Id, USER_INFO_FILE);
		fclose(userData);
		return NULL;
	}
	else {
		//printf("[userInfo_get][userControl.h][ EoF ] there is %s", _Id);
		fclose(userData);
		return &targetUser;
	}
}

// _Id에 해당하는 데이터를 targetUser로 바꾸기
void userInfo_modify(const char* _Id, user_info changedData) {
	int population = userPopulation_get(), targetData_index = 0;
	user_info* originalData = calloc(sizeof(user_info), population);
	if (NULL == userInfo_get(_Id)) {
		printf("[userInfo_modify][userControl.h][ ERROR ] there is no \"%s\" in \"%s\"\n", _Id, USER_INFO_FILE);
		return;
	}
	else {
		// 원본복사
		FILE* userData = fopen(USER_INFO_FILE, "rb");
		for (targetData_index = 0; targetData_index < population; targetData_index++)
			fread((originalData + targetData_index), sizeof(user_info), 1, userData);
		fclose(userData);

		// 바꿀자리(index) 확인
		for (targetData_index = 0; targetData_index < population; targetData_index++)
			if (strSame((originalData + targetData_index)->id, _Id))
				break;

		// 바꾸기
		userData = fopen(USER_INFO_FILE, "wb");
		for (int i = 0; i < population; i++) {
			if (i == targetData_index) {
				fwrite(&changedData, sizeof(user_info), 1, userData);
				continue;
			}
			fwrite((originalData + i), sizeof(user_info), 1, userData);
		}
		free(originalData);
		fclose(userData);
	}
}

// #########################################################
//파일 유저히스토리
// #########################################################

char* _NoneRecord = "####/##/## - ##:##:##";
void userHistory_route(char* _Var, const char* _Id) {
	user_info newUser = *userInfo_get(_Id);
	char fileRoute[HISTORY_ROUTE_SIZE] = { 0, };
	sprintf_s(fileRoute, HISTORY_ROUTE_SIZE, "%s%s.his", USER_HISTORY_FILE, newUser.id);
	strcpy(_Var, fileRoute);
}

void userHistory_write(const char* _Id, const char* _Nickname) {
	char history_file_path[HISTORY_ROUTE_SIZE] = { 0, };
	userHistory_route(history_file_path, _Id);
	FILE* userHistory = fopen(history_file_path, "wb");

	user_history newUserHistory = { 0, };
	// 유저가 입력한 부분
	strcpy(newUserHistory.id, _Id);
	strcpy(newUserHistory.nickname, _Nickname);
	// 초기화 부분
	strcpy(newUserHistory.best.endTime, _NoneRecord);
	newUserHistory.best.record = 0;
	for (int i = 0; i < USER_HISTORY_MAX; i++) {
		strcpy(newUserHistory.total[i].endTime, _NoneRecord);
		newUserHistory.total[i].record = 0;
	}

	fwrite(&newUserHistory, sizeof(user_history), 1, userHistory);
	fclose(userHistory);
}

user_history* userHistory_get(const char* _Id) {
	char history_file_path[HISTORY_ROUTE_SIZE] = { 0, };
	userHistory_route(history_file_path, _Id);

	FILE* historyFile = fopen(history_file_path, "rb");
	user_history targetHistory = { 0, };
	if (NULL == historyFile) {
		printf("[userHistory_get][userControl.h][ ERROR ] there is noting in \"%s\"\n", USER_HISTORY_FILE);
		return NULL;
	}
	else {
		fread(&targetHistory, sizeof(user_history), 1, historyFile);
		fclose(historyFile);
		return &targetHistory;
	}
}

void userHistory_append(const char* _Id, unit_record newData) {
	char history_file_path[HISTORY_ROUTE_SIZE] = { 0, };
	userHistory_route(history_file_path, _Id);

	user_history* targetHistory = userHistory_get(_Id);
	user_history originalHis = *targetHistory;
	if (NULL == targetHistory) {
		printf("[userInfo_modify][userControl.h][ ERROR ] there is no \"%s\" in \"%s\"\n", _Id, USER_INFO_FILE);
		return;
	}
	else {
		// 신기록갱신
		if (newData.record > originalHis.best.record) {
			originalHis.best.record = newData.record;
			strcpy(originalHis.best.endTime, newData.endTime);
		}
		// 새로운 기록과 다시 쓰기
		for (int i = (USER_HISTORY_MAX - 1); i > 0; i--) {
			originalHis.total[i].record = originalHis.total[i - 1].record;
			strcpy(originalHis.total[i].endTime, originalHis.total[i - 1].endTime);
		}
		originalHis.total[0].record = newData.record;
		strcpy(originalHis.total[0].endTime, newData.endTime);

		FILE* historyFile = fopen(history_file_path, "wb");
		fwrite(&originalHis, sizeof(user_history), 1, historyFile);
		fclose(historyFile);
	}
}

//	#########################################################
//	RANKING
//	#########################################################
//char* _NoneRecord = "####/##/## - ##:##:##";

user_ranks* userRank_get(void) {
	FILE* userRank_file = fopen(USER_RANK_FILE, "rb");
	if (NULL == userRank_file) {
		//printf("[userRank_get][userControl.h] there is no \"%s\", it will make now", USER_RANK_FILE);
		unit_rank space = {
			".",".",{"####/##/## - ##:##:##",0}
		};
		user_ranks init_rank = {
			space ,space ,space ,space ,space,
			space ,space ,space ,space ,space
		};
		userRank_file = fopen(USER_RANK_FILE, "wb");
		fwrite(&init_rank, sizeof(user_ranks), 1, userRank_file);
		printf("%s", init_rank.user->best.endTime);
		fclose(userRank_file);
		return &init_rank;
	}
	else {
		user_ranks rankings = { 0, };
		fread(&rankings, sizeof(user_ranks), 1, userRank_file);
		fclose(userRank_file);
		return &rankings;
	}

}

void userRank_write(const char* _Id,const unsigned int record) {
	unit_rank newBest_data = { 0, };
	strcpy(newBest_data.id, userInfo_get(_Id)->id);
	strcpy(newBest_data.nickname, userInfo_get(_Id)->nickname);
	strcpy(newBest_data.best.endTime, "####/##/## - ##:##:##");
	newBest_data.best.record = record;

	if (NULL == userRank_get())
	{
		//printf("[userRank_write][userControl.h] there is no \"%s\", it will make now", USER_RANK_FILE);
		unit_rank space = {
			".",".",{"####/##/## - ##:##:##",0}
		};
		user_ranks newRank_data = {
			newBest_data, space, space, space, space,
			       space, space, space, space, space
		};

		FILE* newRank_filePointer = fopen(USER_RANK_FILE, "wb");
		fwrite(&newRank_data, sizeof(user_ranks), 1, newRank_filePointer);
		fclose(newRank_filePointer);
		return;
	}
	else
	{
		user_ranks rankings = *userRank_get();
		// 바꿀자리(index) 확인
		int targetIndex = 0;
		for (targetIndex = 0; targetIndex <= 10; targetIndex++) {
			if (targetIndex == 10)
				break;
			if (newBest_data.best.record >= rankings.user[targetIndex].best.record) {
				break;
			}
		}
		//바꾸기
		if (targetIndex != 10) {
			for (int i = 10-1; i > targetIndex; i--) {
				strcpy(rankings.user[i].id, rankings.user[i-1].id);
				strcpy(rankings.user[i].nickname, rankings.user[i-1].nickname);
				strcpy(rankings.user[i].best.endTime, rankings.user[i-1].best.endTime);
				rankings.user[i].best.record = rankings.user[i-1].best.record;
			}
			strcpy(rankings.user[targetIndex].id, newBest_data.id);
			strcpy(rankings.user[targetIndex].nickname, newBest_data.nickname);
			strcpy(rankings.user[targetIndex].best.endTime, newBest_data.best.endTime);
			rankings.user[targetIndex].best.record = newBest_data.best.record;
		}

		FILE* userRank_file = fopen(USER_RANK_FILE, "wb");
		fwrite(&rankings, sizeof(user_ranks), 1, userRank_file);
		fclose(userRank_file);
		return;
	}
}

//	#########################################################
//	입력 ID,NICK,PW
//	#########################################################


char* userInput_id(const char* identity_type) { // NULL == 취소
	char* getUser_identity = (char*)calloc(sizeof(char), USER_ID_MAX);
	char* result = getUser_identity;

	printf("%-10s : ", identity_type);
	int identityLength = 0;
	while (1) {
		*getUser_identity = _getch();	// 입력받기
		
		if (*getUser_identity == 27)	// ESC 누르면 NULL
			return NULL;
		
		else if (!(0 <= *getUser_identity && *getUser_identity <= 127))		//한글입력방지
			continue;
		if (identity_type == "ID" && checkCharType(*getUser_identity, 1))
			continue;
		if (VK_SPACE == *getUser_identity || checkCharType(*getUser_identity, 4) || checkCharType(*getUser_identity, 5))
			continue;
		if (VK_RETURN == *getUser_identity) {
			if (identityLength < 4)
				continue;
			else {
				*getUser_identity = '\0';
				putchar('\n');
				return result;
			}
		}
		
		if (VK_BACK == *getUser_identity) {		// 글자 지우기
			if (identityLength > 0) {
				putchar(VK_BACK);
				putchar(VK_SPACE);
				putchar(VK_BACK);

				*getUser_identity = '\0';
				getUser_identity--; identityLength--;
				continue;
			}
			else {
				continue;
			}
		}
		
		if (USER_ID_MAX - 1 == identityLength)		// 글자 수가 31개이면 안쳐짐
			continue;

		putchar(*getUser_identity);
		getUser_identity++;
		identityLength++;
	}
	return NULL;
}

char* userInput_pw(const char* pw_title) {
	char* getUser_pw = (char*)calloc(sizeof(char), USER_PASSWORD_MAX);
	char* result = getUser_pw;
	//{ 대문자, 소문자, 숫자, 특수문자 }
	bool CHAR[4] = { false, false ,false ,false };

	printf("%-10s : ", pw_title);
	int pwLength = 0;
	while (1) {		// 입력받기
		*getUser_pw = _getch();

		if (*getUser_pw == 27)	//한글입력방지
			return NULL;
		else if (!(0 <= *getUser_pw && *getUser_pw <= 127))
			continue;
		if (VK_SPACE == *getUser_pw && checkCharType(*getUser_pw, 5))
			continue;
		// PW_CONDITION = ({대문자, 소문자, 숫자, 특수문자 } 각각 적어도 하나는 있어야함
		for (int i = 1; i <= 4; i++) {
			if (!CHAR[i - 1])
				CHAR[i - 1] = checkCharType(*getUser_pw, i);	// PW_CONDITION [CHECK]
		}

		if (VK_RETURN == *getUser_pw)
		{
			
			if (!((CHAR[0] && CHAR[1]) && (CHAR[2] && CHAR[3])))	// PW_CONDITION 부합하지 않으면 [SKIP]
				continue;
			if (pwLength < 4) {
				continue;
			}
			else {
				*getUser_pw = '\0';
				putchar('\n');
				return result;
			}
		}
		
		if (VK_BACK == *getUser_pw)		// 글자 지우기
		{
			if (pwLength > 0) {
				putchar(VK_BACK);
				putchar(VK_SPACE);
				putchar(VK_BACK);

				*getUser_pw = '\0';
				getUser_pw--; pwLength--;
				continue;
			}
			else {
				continue;
			}
		}
		if (USER_PASSWORD_MAX - 1 <= pwLength)
			continue;

		putchar('*');
		getUser_pw++;
		pwLength++;
	}
	return NULL;
}