#pragma once
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <WinUser.h>
#include <malloc.h>
#pragma once

//�ڷ��� ũ��
#define USER_PASSWORD_MAX 33
#define USER_ID_MAX 33
#define USER_NICKNAME_MAX 33
#define USER_INVENTORY_SIZE 64

//���� ũ��
#define USER_DEAULT_WALLET 0

//���ϰ��
#define USER_PASSWORD_FILE ".pw
#define USER_INFO_FILE "user.data"
#define USER_RANK_FILE "rank.data"
#define USER_HISTORY_FILE ".his"

/*
* (STR) user_info.id[32 + 1] : {user_input} , ### NOT allow specialChar, ' ' ###
* (STR) user_info.nickname[32 + 1] : {user_input} , ### NOT allow specialChar, ' ' ###
* (unsigned int) user_info.wallet[4] : 0 , �⺻ �ڱ��� 0
* (bool) user_info.inventory[64] : {true, false, false, ..., false, -1, -1, ..., -1}, ### �⺻ ĳ���͸� �κ��丮�� �ִ�. ###*/
typedef struct __user__ {
	char id[33];
	char nickname[33];
	unsigned int wallet;
	bool inventory[64];
} user_info;

// ����Ե� NULL == 0 �̹Ƿ�, strchr ����  ���ڿ� �Ǿտ� ' '�� �־� �ش�.
const char* ENGChar = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char* engChar = " abcdefghijklmnopqrstuvwxyz";
const char* numChar = " 0123456789";
const char* specialChar = " !#$%%&'()+,-.;<=>[]^_`{}@~";
const char* notAllowedChar = "  /\\:*?\"<>|";

// [MODE] 1. �빮��,   2. �ҹ���,   3. ����,   4. Ư������   5. ����빮��
bool checkCharType(const char c, const int _type) {
	bool result = false;
	// _type�� ���� c�� ��/�ҹ���,����,Ư���������� Ȯ���Ѵ�.
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
		printf("[userControl.h][checkCharType] �ùٸ��� ���� argument (_type �Է�)[FUNC_ERROR]");
		return false;
	}
	return result;
}
char* user_GETidentity(const char* identity_type) {
	char* getUser_identity = (char*)calloc(sizeof(char), USER_ID_MAX);
	char* result = getUser_identity;

	printf(" %s : ", identity_type);
	int nicknameLength = 0;
	while (1) {
		// �Է¹ޱ�
		*getUser_identity = _getch();

		if (identity_type == "ID" && checkCharType(*getUser_identity, 1))
			continue;
		if (VK_SPACE == *getUser_identity || checkCharType(*getUser_identity, 4) || checkCharType(*getUser_identity, 5))
			continue;
		if (VK_RETURN == *getUser_identity) {
			if (nicknameLength < 4)
				continue;
			else {
				*getUser_identity = '\0';
				putchar('\n');
				return result;
			}
		}
		// ���� �����
		if (VK_BACK == *getUser_identity) {
			if (nicknameLength > 0) {
				putchar(VK_BACK);
				putchar(VK_SPACE);
				putchar(VK_BACK);

				*getUser_identity = '\0';
				getUser_identity--; nicknameLength--;
				continue;
			}
			else {
				continue;
			}
		}
		// ���� ���� 32���̸� ������
		if (USER_ID_MAX - 1 == nicknameLength)
			continue;
		// ���� ��ġ ����
		putchar(*getUser_identity);
		getUser_identity++;
		nicknameLength++;
	}
	return NULL;
}
char* user_GETpw(const char* pw_title) {
	char* getUser_pw = (char*)calloc(sizeof(char), USER_PASSWORD_MAX);
	char* result = getUser_pw;
	//{ �빮��, �ҹ���, ����, Ư������ }
	bool CHAR[4] = { false, false ,false ,false };

	printf(" %s : ", pw_title);
	int pwLength = 0;
	while (1) {
		// �Է¹ޱ�
		*getUser_pw = _getch();

		if (VK_SPACE == *getUser_pw && checkCharType(*getUser_pw, 5))
			continue;
		// PW_CONDITION = (�빮��, �ҹ���, ����, Ư������ } ��� �ϳ��� �־����)
		// PW_CONDITION [CHECK]
		for (int i = 1; i <= 4; i++) {
			if (!CHAR[i - 1])
				CHAR[i - 1] = checkCharType(*getUser_pw, i);
		}
		if (VK_RETURN == *getUser_pw) {
			// PW_CONDITION �������� ������ [SKIP]
			if (!((CHAR[0] && CHAR[1]) && (CHAR[2] && CHAR[3])))
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
		// ���� �����
		if (VK_BACK == *getUser_pw) {
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

		// ���� ��ġ ����
		putchar('*');
		getUser_pw++;
		pwLength++;
	}
	return NULL;
}
// ������ �߰�
void userDB_ADD(const char* user_id);
// ������ ��û
void userDB_GET(const char* user_id);
// ������ ����
void userDB_CHANGE(const char* user_id);


void userPWDB_ADD(const char* user_id, bool ADD_USER);
void userPWDB_CMP(const char* user_id, const char* user_pw);
void userPWDB_CHANGE(const char* user_id, const char* user_pw);
//
//
//void userHistoryDB_GET(const char* user_id);
//	// >> void userBestHistory();
//void userHistoryDB_ADD(const char* user_id, bool MEMO_SCORE);
//
//	// >>void rankDB_ADD()
//	//	   >>void rankDB_SORT()
//
//void rankDB_GET(void)
//void rankDB_CHANGE()


void user_registration(void) {

}
// MUST_INPUT�� true�� �Է±��� ��ٸ�, false�� �Է��� ~�� ���� ��ٸ�
void buttonInteract(int _button, bool MUST_INPUT) {
	int buttonClick = _getch();
	if (MUST_INPUT) {
		buttonClick = _getch();
	}
	//else {

	//	buttonClick 
	//}
}