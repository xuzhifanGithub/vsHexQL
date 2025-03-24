#pragma once
#include"base.h"


void initBoard(int** board);
void displayBoard(int** board);
vector<int> generateSideMovePos(int** board);

bool isSideWin(int** board, int moveSide);

bool isRedWin(int** board);
bool isRedWinCheck(int** board, int lastX, int lastY, bool** boolArr);

bool isBlueWin(int** board);
bool isBlueWinCheck(int** board, int lastX, int lastY, bool** boolArr);

void displayVecInt(vector<int> vecInt);


//
void initBoard(int board[][BOARD_SIZE]);
void displayBoard(int board[][BOARD_SIZE]);
vector<int> generateSideMovePos(int board[][BOARD_SIZE]);

bool isSideWin(int board[][BOARD_SIZE], int moveSide);

bool isRedWin(int board[][BOARD_SIZE]);
bool isRedWinCheck(int board[][BOARD_SIZE], int lastX, int lastY, bool** boolArr);

bool isBlueWin(int board[][BOARD_SIZE]);
bool isBlueWinCheck(int board[][BOARD_SIZE], int lastX, int lastY, bool** boolArr);


extern vector<int> vecHistory;