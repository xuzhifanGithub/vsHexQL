#pragma once
#include"base.h"
#include"board.h"


//图操作
double bfs(vector<int> vecGraph[]);
void initRedGraph(vector<int> vecGraph[]);
void initBlueGraph(vector<int> vecGraph[]);
void initBoardGraph(int** board, int playSide, vector<int> vecGraph[]);
void disPlayGraph(vector<int> vecGraph[]);
void cutNode(vector<int> vecGraph[], int cutPos);//减少图联系点
void addNode(vector<int> vecGraph[], int addPos);//增加图联系点

//对弈
void selfPlay();


//估值
double valueRed(vector<int> vecRedGraph[], vector<int> vecBlueGraph[]);
vector<int> genSidePosValue(int** board);



int uctAll(int** board, int moveSide, double time);//uct算法
void uctInit(UCTNode* uctRoot, int moveSide);

UCTNode* uctSelect(UCTNode* node, int** board);//UCT算法的选择
void uctExpand(UCTNode* node, int** board);//UCT算法的扩展

int uctSimulate(UCTNode* node, int** board, int beginSide);
int uctSimulateOMP(int** board, int beginSide, int useThreadsNum);
void uctBackPropagation(UCTNode* node, int isWin);//UCT算法的反向传播





//board参数不一样
UCTNode* uctSelect(UCTNode* node, int board[][BOARD_SIZE]);//UCT算法的选择
void uctExpand(UCTNode* node, int board[][BOARD_SIZE]);//UCT算法的扩展
int uctSimulate(UCTNode* node, int board[][BOARD_SIZE], int beginSide);


double uctGetR(UCTNode* node, double uctC = UCT_C);//得到r值
void uctDisplayUCTNode(UCTNode* node);//显示uct第一层情况
void deleteRoot(UCTNode* node);

//变量
//extern vector<int> vecHistory;
//extern uint64_t hashTable[11][11][2];