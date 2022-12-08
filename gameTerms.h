#pragma once

//맵 전체 크기
#define MAP_ROW 24
#define MAP_COL 114

//(축소된)맵 전체 크기
#define Map_reduced_row 8			// ( 8 )
#define Map_reduced_col 38		// ( 37 + sizeof('\0') )
#define shiftSpace_col 75		// ( 37*2 + sizeof('\0') )

//게임 요소
#define obj_grass '_'
#define obj_route ' '
#define obj_player_default '1'
#define obj_car '@'					// 차
#define obj_rail '#'				// 기차
#define obj_barrier '&'				// 돌, 나무


// KEY BINDING
#define UP_arrow 72
#define LEFT_arrow 75
#define RIGHT_arrow 77
#define DOWN_arrow 80 

// 타입

typedef const char Element;
typedef const char Direct;

typedef char Map;
typedef char Line;

typedef void Map_CTRL;
typedef void Line_CTRL;

typedef int Velocity;
typedef int Vect;
typedef int Pos;

typedef struct __position__ { int row; int col; }player_position;
typedef struct __direct__ { char up[3]; char down[5]; char left[5]; char right[6]; } dim2Unit;

// 축소된 Map
Map Map_reduced[Map_reduced_row][Map_reduced_col] = { 0, };

// map Velocity
static Velocity vel_SET[Map_reduced_row] = {0,};

// 플레이어 기본위치
player_position player_pos = { 5,18 };

// 2차원 직교 방향
char control_up[4] = { UP_arrow,'w','W',' ' };
char control_down[3] = { DOWN_arrow,'s','S' };
char control_left[3] = { LEFT_arrow,'a','A' };
char control_right[3] = { RIGHT_arrow,'d','D' };
Direct* directVect[4] = { control_up ,control_down ,control_left,control_right };

// 2차원 직교 방향 단위 벡터
Direct* directMode[4] = { "up","down","left","right" };
dim2Unit unitVect = { "up","down","left","right" };

Vect directionVector(Direct* keyInput) {
	if (strSame(directMode[0], keyInput))
		return -1;
	else if (strSame(directMode[1], keyInput))
		return 1;
	else if (strSame(directMode[2], keyInput))
		return -1;
	else if (strSame(directMode[3], keyInput))
		return 1;
}

/// <returns>무작위 정수 Z  in [-2 , 2] (단, 0을 제외한 Z)</returns>
Velocity Line_SpeedRand() {
	double range = 5.;
	int t = (int)(range * random() - range /2);
	while (1)
		if (t == 0)
			t = (int)(range * random() - range/2);
		else
			break;

	return t;
}
void Vel_swap(Velocity l[Map_reduced_row], Pos rowA, Pos rowB) {
	Velocity temp = l[rowA];
	l[rowA] = l[rowB];
	l[rowB] = temp;
}
void Vel_down(Velocity vels[Map_reduced_row]) {
	for (int i = (Map_reduced_row - 1); i > 0; i--)
		Vel_swap(vels, i, i - 1);
	vels[0] = Line_unitSpeed(Map_reduced[0], obj_car);
}


/*
* KEY INPUT
*/

/// 키입력받기
Direct* Player_keyIn(void) {
	int key;
	if (_kbhit())
	{
		key = _getch();

		if (27 == key) {
			return "ESC";
		}

		if (224 == key) {
			key = _getch();

			for (int i = 0; i < 4; i++)
			{
				if (key == directVect[i][0])
					return directMode[i];
			}
		}
		else if (224 != key) {
			for (int i = 0; i < 4; i++) {
				for (int j = 1; j < sizeof(directMode[i]); j++)
				{
					if (directVect[i][j] == key)
						return directMode[i];
				}
			}

			return  " ";
		}
	}
	else
	{
		return  " ";
	}
}