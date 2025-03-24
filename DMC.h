#pragma once
#include"base.h"
#include"board.h"
#include"mcts.h"
#include"net.h"

struct train_data {
	Tensor2D state;
	float true_value;
	int side;
};


void dmc();
void dmc(Net model);
void dmc(Net modelRed, Net modelblue, int choice = 1);

int findMaxQPos(int** board, Tensor2D onehot,Net model,int side);

vector<train_data> colletData(Net modelRed, Net modelblue, int round = 1*10000);
float trainNet(Net modelRed, Net modelblue, vector<train_data> vec_trainData);

void displayStateQ(int** board, Net model,int side);

Tensor2D board_trans_onehot(int** hexBoard);

float board_net_Qvalue(int** hexBoard, Net net);

float board_net_Qvalue(Tensor2D onehot, Net net);

void selfPlayExecQ(Net net, int num = 100);

int isEqual(float a, float b);



float updateQlearning(vector<Tensor2D> vecState, Net model, vector<int> vecPos, int isWin, int side);