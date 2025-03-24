#pragma once
#include"base.h"
#include"board.h"
#include"mcts.h"
#include"hash.h"


void readFileQTable();//���ļ��е�Q��
void readFileQTableBlue();//���ļ��е�Q��
void writeFileQTable();//д���ļ���ǰ������Q��
void writeFileQTableBlue();//д���ļ���ǰ������Q��


void createQTable(float QTable[][BOARD_SIZE]);//����һ����ʼ����Q��
void displayQTable(float QTable[][BOARD_SIZE]);//��ʾQ��
void pruneQTable(float QTable[][BOARD_SIZE], int** board);//�޼�Q���������ʵ�λ��ѡΪ-1

void displayVecUINT64_T(vector<uint64_t> vecUint64_t);//��ʾ

void updateQTable(vector<uint64_t> vecSW, vector<int> vecAW, vector<uint64_t> vecSL, vector<int> vecAL, 
										map<uint64_t, QTABLE>& MapHashQTable,int optino);



bool isFindState(uint64_t state, int** board, int isDepositMap = 0);
float findQTableMaxValue(float QTable[][BOARD_SIZE]);
int findQTableMaxPos(float QTable[][BOARD_SIZE]);

void writeFileQValue(string selectFile, int openOption);//��¼���Qֵ�仯

void QLearning();//Qѧϰ

void selfPlayExecQ();


void updateQTableExec(vector<int> vecAllPos, vector<uint64_t> vecSW, vector<int> vecAW, 
	vector<uint64_t> vecSL, vector<int> vecAL, map<uint64_t, QTABLE> MapHashQTable);
