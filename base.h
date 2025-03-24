#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<random>
#include <algorithm>
#include<vector>
#include<ctime>
#include<iostream>
#include<omp.h>
#include<map>
#include <io.h>
#include <direct.h>
#include< sstream >


#define BOARD_SIZE 4
#define RED_SIDE   1
#define BLUE_SIDE  -1
#define EMPTY_POS  0
#define VEC_GRAPH_SIZE (BOARD_SIZE*BOARD_SIZE+2)


const int dx4[] = { -1,0,1,0 };
const int dy4[] = { 0,1,0,-1 };

const int dx6[] = { -1,-1,0,0,1,1 };
const int dy6[] = { 0,1,-1,1,-1,0 };

const double UCT_C = 0.5;

const float REWARD = 1.0;//����
const float GAMMA = 1.0;//�ۿ�ϵ��
const float ALPHA = 0.4;//ѧϰϵ��
const float EXPLORE = 0.1;

const int QLimitStep = 16;


using namespace std;


struct POS
{
    int posX;
    int posY;
};

struct MoveValue
{
    int x;
    int y;
    double value;
};

struct COMP
{
    //�Զ���"С��"
    bool operator()(const MoveValue& a, const MoveValue& b)
    {
        if (a.value > b.value)
        {
            return true;
        }
        else if (a.value == b.value && a.x < b.x)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

};


struct QTABLE
{
    uint64_t state;
    float Q[BOARD_SIZE][BOARD_SIZE];
};


//����uct�㷨
struct UCTNode
{
    int x;
    int y;
    int side;
    int win;
    int attempt;
    double r;

    UCTNode* parent;
    vector<UCTNode*> vecNodes;
};
