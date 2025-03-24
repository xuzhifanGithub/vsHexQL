#pragma once
#include"base.h"
#include"board.h"


//ͼ����
double bfs(vector<int> vecGraph[]);
void initRedGraph(vector<int> vecGraph[]);
void initBlueGraph(vector<int> vecGraph[]);
void initBoardGraph(int** board, int playSide, vector<int> vecGraph[]);
void disPlayGraph(vector<int> vecGraph[]);
void cutNode(vector<int> vecGraph[], int cutPos);//����ͼ��ϵ��
void addNode(vector<int> vecGraph[], int addPos);//����ͼ��ϵ��

//����
void selfPlay();


//��ֵ
double valueRed(vector<int> vecRedGraph[], vector<int> vecBlueGraph[]);
vector<int> genSidePosValue(int** board);



int uctAll(int** board, int moveSide, double time);//uct�㷨
void uctInit(UCTNode* uctRoot, int moveSide);

UCTNode* uctSelect(UCTNode* node, int** board);//UCT�㷨��ѡ��
void uctExpand(UCTNode* node, int** board);//UCT�㷨����չ

int uctSimulate(UCTNode* node, int** board, int beginSide);
int uctSimulateOMP(int** board, int beginSide, int useThreadsNum);
void uctBackPropagation(UCTNode* node, int isWin);//UCT�㷨�ķ��򴫲�





//board������һ��
UCTNode* uctSelect(UCTNode* node, int board[][BOARD_SIZE]);//UCT�㷨��ѡ��
void uctExpand(UCTNode* node, int board[][BOARD_SIZE]);//UCT�㷨����չ
int uctSimulate(UCTNode* node, int board[][BOARD_SIZE], int beginSide);


double uctGetR(UCTNode* node, double uctC = UCT_C);//�õ�rֵ
void uctDisplayUCTNode(UCTNode* node);//��ʾuct��һ�����
void deleteRoot(UCTNode* node);

//����
//extern vector<int> vecHistory;
//extern uint64_t hashTable[11][11][2];