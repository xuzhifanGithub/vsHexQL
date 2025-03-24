#pragma once
#include"base.h"
#include"board.h"
#include"mcts.h"
#include"hash.h"


void readFileQTable();//读文件中的Q表
void readFileQTableBlue();//读文件中的Q表
void writeFileQTable();//写入文件中前俩步的Q表
void writeFileQTableBlue();//写入文件中前俩步的Q表


void createQTable(float QTable[][BOARD_SIZE]);//创造一个初始化的Q表
void displayQTable(float QTable[][BOARD_SIZE]);//显示Q表
void pruneQTable(float QTable[][BOARD_SIZE], int** board);//修剪Q表，将不合适的位置选为-1

void displayVecUINT64_T(vector<uint64_t> vecUint64_t);//显示

void updateQTable(vector<uint64_t> vecSW, vector<int> vecAW, vector<uint64_t> vecSL, vector<int> vecAL, 
										map<uint64_t, QTABLE>& MapHashQTable,int optino);



bool isFindState(uint64_t state, int** board, int isDepositMap = 0);
float findQTableMaxValue(float QTable[][BOARD_SIZE]);
int findQTableMaxPos(float QTable[][BOARD_SIZE]);

void writeFileQValue(string selectFile, int openOption);//记录结点Q值变化

void QLearning();//Q学习

void selfPlayExecQ();


void updateQTableExec(vector<int> vecAllPos, vector<uint64_t> vecSW, vector<int> vecAW, 
	vector<uint64_t> vecSL, vector<int> vecAL, map<uint64_t, QTABLE> MapHashQTable);
