#pragma once

#include "gameTerms.h"

/// {element}가 있는 {l}에만 '속도'부여
Velocity Line_unitSpeed(Line* l, Element element) {
	for (unsigned int i = 0; i < strlen(l); i++)
	{
		if (l[i] == element)
			return Line_SpeedRand();
	}
	return 0;
}
Velocity* Line_SpeedSet(Map map[Map_reduced_row][Map_reduced_col], Element element) {
	static Velocity Map_rowVel[Map_reduced_row] = { 0, };

	for (int row = 0; row < Map_reduced_row; row++)
		Map_rowVel[row] = Line_unitSpeed(map[row], element);
	return Map_rowVel;
}



/*
* LINE CONTROL
*/

/// <returns>e1, e2로 이루어진 축소된 Map의 가로 길이(Map_reduced_col) 크기의 Line을 하나 만든다.</returns>
Line* unitLine_gen(double e1_probability, Element e1, Element e2) {
	Line l[Map_reduced_col] = { 0, };
	for (int i = 0; i < Map_reduced_col - 1; i++) {
		if (uniformDis(e1_probability))
			l[i] = e1;
		else
			l[i] = e2;
	}
	l[Map_reduced_col - 1] = 0;

	return l;
}
Line* unitLine_genRand(void) {
	double num = random();
	if (num < .5)
		return unitLine_gen(3. / 38, obj_car, obj_route);
	else if (.5 <= num && num < .8)
		return unitLine_gen(5. / 38, obj_barrier, obj_route);
	else if (.8 <= num && num <= 1)
		return unitLine_gen(1, obj_train, obj_route);
}

///	{Line_original}을 {_ShiftVect}만큼 '순환SHIFT'해줌
Line_CTRL Line_shift(Line* Line_original, Vect _ShiftVect) {
	Line l_shift[shiftSpace_col] = { 0, };

	int len = strlen(Line_original);
	strcpy(l_shift, Line_original);
	strcat(l_shift, Line_original);

	if (_ShiftVect > 0) {
		for (int i = len - _ShiftVect; i < 2 * len - _ShiftVect; i++)
			Line_original[i - (len - _ShiftVect)] = l_shift[i];
	}
	else if (_ShiftVect < 0) {
		for (int i = 0 - _ShiftVect; i < len - _ShiftVect; i++)
			Line_original[i - (0 - _ShiftVect)] = l_shift[i];
	}
	else {
		return;
	}
}



/*
* MAP CONTROL
*/

/// {obj_player_default} 중심으로 한 칸씩, Map의 (r, c) = (5,18)에 {obj_player}를 배치
Map_CTRL Player_init(Element _Player, Element _Route) {
	player_pos.row = 5;	player_pos.col = 18;

	for (int r = player_pos.row-1; r <= player_pos.row+1; r++)
		for (int c = player_pos.col-1; c <= player_pos.col+1; c++) {
			if (Map_reduced[r][c] != _Route)
				Map_reduced[r][c] = _Route;
		}

	Map_reduced[ player_pos.row ][ player_pos.col ] = _Player;
}

/// 초기맵을 만들기
Map_CTRL Map_init(Element _Player, Map map[Map_reduced_row][Map_reduced_col]) {
	for (int i = 0; i < Map_reduced_row; i++)
		strcpy(map[i], unitLine_genRand());
	Velocity* mem = Line_SpeedSet(map, obj_car);
	for (int i = 0; i < Map_reduced_row; i++) {
		vel_SET[i] = mem[i];
	}
	Player_init(_Player, obj_route);
}

/// {map}의 {rowA}번째 행과 {rowB}번째 행을 '행SWAP'해줌 
Map_CTRL Map_rowSwap(Map map[Map_reduced_row][Map_reduced_col], Pos rowA, Pos rowB) {
	char temp = 0;

	for (int i = 0; i < Map_reduced_col; i++)	{
		temp = map[rowA][i];
		map[rowA][i] = map[rowB][i];
		map[rowB][i] = temp;
	}
}

/// Map 아래로 한칸 SHIFT하고, 가장위에 새로운 Line을 생성한다.
Map_CTRL Map_down(Map map[Map_reduced_row][Map_reduced_col]) {
	for (int i = (Map_reduced_row - 1); i > 0; i--)
		Map_rowSwap(map, i, i - 1);

	strcpy(map[0], unitLine_genRand());
}

/// {element}만 움직임.
Map_CTRL Map_objMove(Element _Player, Element element, bool* gameOver) {
	/*printf("Map_objMove");
	for (int i = 0; i < Map_reduced_row; i++)
		printf("[%d]", vel_SET[i]);*/

	char playerLocal[4] = {
		Map_reduced[player_pos.row + (-1)][player_pos.col],	//up
		Map_reduced[player_pos.row + (+1)][player_pos.col],	//down
		Map_reduced[player_pos.row][player_pos.col + (-1)],	//left
		Map_reduced[player_pos.row][player_pos.col + (+1)]	//right
	};
	// 위치변경
	if (vel_SET[5] != 0) {
		if (Map_reduced[player_pos.row][player_pos.col - vel_SET[5]] == element) {
			*gameOver = true; // End of Game
		}
		Map_reduced[player_pos.row][player_pos.col] = obj_route;
		Map_reduced[player_pos.row][player_pos.col - vel_SET[5]] = _Player;
	}
	for (int i = 0; i < Map_reduced_row; i++)
		Line_shift(Map_reduced[i], vel_SET[i]);
}

/// {playerLocal}에 {element}가 있는지 확인
bool Player_unitInteract(Element* playerLocal, Element element){
	return (playerLocal == element);
}
/// {keyInput} 방향에 {element}가 있는지 확인
bool Player_interact(Direct* keyInput, Element* playerLocal, Element element) {
	if (strSame(keyInput, unitVect.up)) {
		return Player_unitInteract(playerLocal[0], element);
	}
	else if (strSame(keyInput, unitVect.down)) {
		return Player_unitInteract(playerLocal[1], element);
	}
	else if (strSame(keyInput, unitVect.left)) {
		return Player_unitInteract(playerLocal[2], element);
	}
	else if (strSame(keyInput, unitVect.right)) {
		return Player_unitInteract(playerLocal[3], element);
	}
	else {
		return false;
	}
}

void Player_move
(
	Element _Player, Direct* keyInput,
	Element _Barrier, Element _Dead, Element _Route,
	unsigned int* score, bool* gameOver
){
	if (strSame(keyInput," ")) {
		return;
	}

	Element playerLocal[4] = {
		Map_reduced[player_pos.row + (-1)][player_pos.col],	//up
		Map_reduced[player_pos.row + (+1)][player_pos.col],	//down
		Map_reduced[player_pos.row][player_pos.col + (-1)],	//left
		Map_reduced[player_pos.row][player_pos.col + (+1)]	//right
	};

	if (Player_interact(keyInput, playerLocal, _Dead))
	{
		//printf("gameOver");
		*gameOver = true; // End of Game
	}
	else if (Player_interact(keyInput, playerLocal, _Barrier))
	{
		//printf("STAY");
	}
	else if (Player_interact(keyInput, playerLocal, _Route) || Player_interact(keyInput, playerLocal, obj_train))
	{

		if (strSame(keyInput, unitVect.up))
		{
			(*score)++;
			Map_reduced[player_pos.row][player_pos.col] = _Route;
			Map_down(Map_reduced);
			Vel_down(vel_SET);
			Map_reduced[player_pos.row][player_pos.col] = _Player;
			return;
		}
		else if (strSame(keyInput, unitVect.down))
		{
			return;
		}
		else if (strSame(keyInput, unitVect.left))
		{
			Map_reduced[player_pos.row][player_pos.col] = _Route;
			if (Player_interact(keyInput, playerLocal, obj_train))
				Map_reduced[player_pos.row][player_pos.col] = obj_train;

			player_pos.col += directionVector(keyInput);
			Map_reduced[player_pos.row][player_pos.col] = _Player;

			return;
		}
		else if (strSame(keyInput, unitVect.right))
		{
			Map_reduced[player_pos.row][player_pos.col] = _Route;
			if (Player_interact(keyInput, playerLocal, obj_train))
				Map_reduced[player_pos.row][player_pos.col] = obj_train;


			player_pos.col += directionVector(keyInput);
			Map_reduced[player_pos.row][player_pos.col] = _Player;

			return;
		}
		else
		{
			return;
		}

	}
	else
	{
		return;
	}
}

Map_CTRL Map_print(Pos row, Pos col) {
	for (int i = 0; i < Map_reduced_row; i++) {
		cursorMove_abs(row + i, col);
		printf("%s", Map_reduced[i]);
	}
}