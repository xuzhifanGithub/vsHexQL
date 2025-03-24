#include"mcts.h"


void initRedGraph(vector<int> vecGraph[])
{
    vecGraph[0] = { 0,1,2,3,4,5,6,7,8,9,10 };
    vecGraph[1] = { -1,1,11 };
    vecGraph[2] = { -1,0,2,11,12 };
    vecGraph[3] = { -1,1,3,12,13 };
    vecGraph[4] = { -1,2,4,13,14 };
    vecGraph[5] = { -1,3,5,14,15 };
    vecGraph[6] = { -1,4,6,15,16 };
    vecGraph[7] = { -1,5,7,16,17 };
    vecGraph[8] = { -1,6,8,17,18 };
    vecGraph[9] = { -1,7,9,18,19 };
    vecGraph[10] = { -1,8,10,19,20 };
    vecGraph[11] = { -1,9,20,21 };
    vecGraph[12] = { 0,1,12,22 };
    vecGraph[13] = { 1,2,11,13,22,23 };
    vecGraph[14] = { 2,3,12,14,23,24 };
    vecGraph[15] = { 3,4,13,15,24,25 };
    vecGraph[16] = { 4,5,14,16,25,26 };
    vecGraph[17] = { 5,6,15,17,26,27 };
    vecGraph[18] = { 6,7,16,18,27,28 };
    vecGraph[19] = { 7,8,17,19,28,29 };
    vecGraph[20] = { 8,9,18,20,29,30 };
    vecGraph[21] = { 9,10,19,21,30,31 };
    vecGraph[22] = { 10,20,31,32 };
    vecGraph[23] = { 11,12,23,33 };
    vecGraph[24] = { 12,13,22,24,33,34 };
    vecGraph[25] = { 13,14,23,25,34,35 };
    vecGraph[26] = { 14,15,24,26,35,36 };
    vecGraph[27] = { 15,16,25,27,36,37 };
    vecGraph[28] = { 16,17,26,28,37,38 };
    vecGraph[29] = { 17,18,27,29,38,39 };
    vecGraph[30] = { 18,19,28,30,39,40 };
    vecGraph[31] = { 19,20,29,31,40,41 };
    vecGraph[32] = { 20,21,30,32,41,42 };
    vecGraph[33] = { 21,31,42,43 };
    vecGraph[34] = { 22,23,34,44 };
    vecGraph[35] = { 23,24,33,35,44,45 };
    vecGraph[36] = { 24,25,34,36,45,46 };
    vecGraph[37] = { 25,26,35,37,46,47 };
    vecGraph[38] = { 26,27,36,38,47,48 };
    vecGraph[39] = { 27,28,37,39,48,49 };
    vecGraph[40] = { 28,29,38,40,49,50 };
    vecGraph[41] = { 29,30,39,41,50,51 };
    vecGraph[42] = { 30,31,40,42,51,52 };
    vecGraph[43] = { 31,32,41,43,52,53 };
    vecGraph[44] = { 32,42,53,54 };
    vecGraph[45] = { 33,34,45,55 };
    vecGraph[46] = { 34,35,44,46,55,56 };
    vecGraph[47] = { 35,36,45,47,56,57 };
    vecGraph[48] = { 36,37,46,48,57,58 };
    vecGraph[49] = { 37,38,47,49,58,59 };
    vecGraph[50] = { 38,39,48,50,59,60 };
    vecGraph[51] = { 39,40,49,51,60,61 };
    vecGraph[52] = { 40,41,50,52,61,62 };
    vecGraph[53] = { 41,42,51,53,62,63 };
    vecGraph[54] = { 42,43,52,54,63,64 };
    vecGraph[55] = { 43,53,64,65 };
    vecGraph[56] = { 44,45,56,66 };
    vecGraph[57] = { 45,46,55,57,66,67 };
    vecGraph[58] = { 46,47,56,58,67,68 };
    vecGraph[59] = { 47,48,57,59,68,69 };
    vecGraph[60] = { 48,49,58,60,69,70 };
    vecGraph[61] = { 49,50,59,61,70,71 };
    vecGraph[62] = { 50,51,60,62,71,72 };
    vecGraph[63] = { 51,52,61,63,72,73 };
    vecGraph[64] = { 52,53,62,64,73,74 };
    vecGraph[65] = { 53,54,63,65,74,75 };
    vecGraph[66] = { 54,64,75,76 };
    vecGraph[67] = { 55,56,67,77 };
    vecGraph[68] = { 56,57,66,68,77,78 };
    vecGraph[69] = { 57,58,67,69,78,79 };
    vecGraph[70] = { 58,59,68,70,79,80 };
    vecGraph[71] = { 59,60,69,71,80,81 };
    vecGraph[72] = { 60,61,70,72,81,82 };
    vecGraph[73] = { 61,62,71,73,82,83 };
    vecGraph[74] = { 62,63,72,74,83,84 };
    vecGraph[75] = { 63,64,73,75,84,85 };
    vecGraph[76] = { 64,65,74,76,85,86 };
    vecGraph[77] = { 65,75,86,87 };
    vecGraph[78] = { 66,67,78,88 };
    vecGraph[79] = { 67,68,77,79,88,89 };
    vecGraph[80] = { 68,69,78,80,89,90 };
    vecGraph[81] = { 69,70,79,81,90,91 };
    vecGraph[82] = { 70,71,80,82,91,92 };
    vecGraph[83] = { 71,72,81,83,92,93 };
    vecGraph[84] = { 72,73,82,84,93,94 };
    vecGraph[85] = { 73,74,83,85,94,95 };
    vecGraph[86] = { 74,75,84,86,95,96 };
    vecGraph[87] = { 75,76,85,87,96,97 };
    vecGraph[88] = { 76,86,97,98 };
    vecGraph[89] = { 77,78,89,99 };
    vecGraph[90] = { 78,79,88,90,99,100 };
    vecGraph[91] = { 79,80,89,91,100,101 };
    vecGraph[92] = { 80,81,90,92,101,102 };
    vecGraph[93] = { 81,82,91,93,102,103 };
    vecGraph[94] = { 82,83,92,94,103,104 };
    vecGraph[95] = { 83,84,93,95,104,105 };
    vecGraph[96] = { 84,85,94,96,105,106 };
    vecGraph[97] = { 85,86,95,97,106,107 };
    vecGraph[98] = { 86,87,96,98,107,108 };
    vecGraph[99] = { 87,97,108,109 };
    vecGraph[100] = { 88,89,100,110 };
    vecGraph[101] = { 89,90,99,101,110,111 };
    vecGraph[102] = { 90,91,100,102,111,112 };
    vecGraph[103] = { 91,92,101,103,112,113 };
    vecGraph[104] = { 92,93,102,104,113,114 };
    vecGraph[105] = { 93,94,103,105,114,115 };
    vecGraph[106] = { 94,95,104,106,115,116 };
    vecGraph[107] = { 95,96,105,107,116,117 };
    vecGraph[108] = { 96,97,106,108,117,118 };
    vecGraph[109] = { 97,98,107,109,118,119 };
    vecGraph[110] = { 98,108,119,120 };
    vecGraph[111] = { 121,99,100,111 };
    vecGraph[112] = { 121,100,101,110,112 };
    vecGraph[113] = { 121,101,102,111,113 };
    vecGraph[114] = { 121,102,103,112,114 };
    vecGraph[115] = { 121,103,104,113,115 };
    vecGraph[116] = { 121,104,105,114,116 };
    vecGraph[117] = { 121,105,106,115,117 };
    vecGraph[118] = { 121,106,107,116,118 };
    vecGraph[119] = { 121,107,108,117,119 };
    vecGraph[120] = { 121,108,109,118,120 };
    vecGraph[121] = { 121,109,119 };
    vecGraph[122] = { 110,111,112,113,114,115,116,117,118,119,120 };
}

void initBlueGraph(vector<int> vecGraph[])
{
    vecGraph[0] = { 0,11,22,33,44,55,66,77,88,99,110 };
    vecGraph[1] = { -1,1,11 };
    vecGraph[2] = { 0,2,11,12 };
    vecGraph[3] = { 1,3,12,13 };
    vecGraph[4] = { 2,4,13,14 };
    vecGraph[5] = { 3,5,14,15 };
    vecGraph[6] = { 4,6,15,16 };
    vecGraph[7] = { 5,7,16,17 };
    vecGraph[8] = { 6,8,17,18 };
    vecGraph[9] = { 7,9,18,19 };
    vecGraph[10] = { 8,10,19,20 };
    vecGraph[11] = { 121,9,20,21 };
    vecGraph[12] = { -1,0,1,12,22 };
    vecGraph[13] = { 1,2,11,13,22,23 };
    vecGraph[14] = { 2,3,12,14,23,24 };
    vecGraph[15] = { 3,4,13,15,24,25 };
    vecGraph[16] = { 4,5,14,16,25,26 };
    vecGraph[17] = { 5,6,15,17,26,27 };
    vecGraph[18] = { 6,7,16,18,27,28 };
    vecGraph[19] = { 7,8,17,19,28,29 };
    vecGraph[20] = { 8,9,18,20,29,30 };
    vecGraph[21] = { 9,10,19,21,30,31 };
    vecGraph[22] = { 121,10,20,31,32 };
    vecGraph[23] = { -1,11,12,23,33 };
    vecGraph[24] = { 12,13,22,24,33,34 };
    vecGraph[25] = { 13,14,23,25,34,35 };
    vecGraph[26] = { 14,15,24,26,35,36 };
    vecGraph[27] = { 15,16,25,27,36,37 };
    vecGraph[28] = { 16,17,26,28,37,38 };
    vecGraph[29] = { 17,18,27,29,38,39 };
    vecGraph[30] = { 18,19,28,30,39,40 };
    vecGraph[31] = { 19,20,29,31,40,41 };
    vecGraph[32] = { 20,21,30,32,41,42 };
    vecGraph[33] = { 121,21,31,42,43 };
    vecGraph[34] = { -1,22,23,34,44 };
    vecGraph[35] = { 23,24,33,35,44,45 };
    vecGraph[36] = { 24,25,34,36,45,46 };
    vecGraph[37] = { 25,26,35,37,46,47 };
    vecGraph[38] = { 26,27,36,38,47,48 };
    vecGraph[39] = { 27,28,37,39,48,49 };
    vecGraph[40] = { 28,29,38,40,49,50 };
    vecGraph[41] = { 29,30,39,41,50,51 };
    vecGraph[42] = { 30,31,40,42,51,52 };
    vecGraph[43] = { 31,32,41,43,52,53 };
    vecGraph[44] = { 121,32,42,53,54 };
    vecGraph[45] = { -1,33,34,45,55 };
    vecGraph[46] = { 34,35,44,46,55,56 };
    vecGraph[47] = { 35,36,45,47,56,57 };
    vecGraph[48] = { 36,37,46,48,57,58 };
    vecGraph[49] = { 37,38,47,49,58,59 };
    vecGraph[50] = { 38,39,48,50,59,60 };
    vecGraph[51] = { 39,40,49,51,60,61 };
    vecGraph[52] = { 40,41,50,52,61,62 };
    vecGraph[53] = { 41,42,51,53,62,63 };
    vecGraph[54] = { 42,43,52,54,63,64 };
    vecGraph[55] = { 121,43,53,64,65 };
    vecGraph[56] = { -1,44,45,56,66 };
    vecGraph[57] = { 45,46,55,57,66,67 };
    vecGraph[58] = { 46,47,56,58,67,68 };
    vecGraph[59] = { 47,48,57,59,68,69 };
    vecGraph[60] = { 48,49,58,60,69,70 };
    vecGraph[61] = { 49,50,59,61,70,71 };
    vecGraph[62] = { 50,51,60,62,71,72 };
    vecGraph[63] = { 51,52,61,63,72,73 };
    vecGraph[64] = { 52,53,62,64,73,74 };
    vecGraph[65] = { 53,54,63,65,74,75 };
    vecGraph[66] = { 121,54,64,75,76 };
    vecGraph[67] = { -1,55,56,67,77 };
    vecGraph[68] = { 56,57,66,68,77,78 };
    vecGraph[69] = { 57,58,67,69,78,79 };
    vecGraph[70] = { 58,59,68,70,79,80 };
    vecGraph[71] = { 59,60,69,71,80,81 };
    vecGraph[72] = { 60,61,70,72,81,82 };
    vecGraph[73] = { 61,62,71,73,82,83 };
    vecGraph[74] = { 62,63,72,74,83,84 };
    vecGraph[75] = { 63,64,73,75,84,85 };
    vecGraph[76] = { 64,65,74,76,85,86 };
    vecGraph[77] = { 121,65,75,86,87 };
    vecGraph[78] = { -1,66,67,78,88 };
    vecGraph[79] = { 67,68,77,79,88,89 };
    vecGraph[80] = { 68,69,78,80,89,90 };
    vecGraph[81] = { 69,70,79,81,90,91 };
    vecGraph[82] = { 70,71,80,82,91,92 };
    vecGraph[83] = { 71,72,81,83,92,93 };
    vecGraph[84] = { 72,73,82,84,93,94 };
    vecGraph[85] = { 73,74,83,85,94,95 };
    vecGraph[86] = { 74,75,84,86,95,96 };
    vecGraph[87] = { 75,76,85,87,96,97 };
    vecGraph[88] = { 121,76,86,97,98 };
    vecGraph[89] = { -1,77,78,89,99 };
    vecGraph[90] = { 78,79,88,90,99,100 };
    vecGraph[91] = { 79,80,89,91,100,101 };
    vecGraph[92] = { 80,81,90,92,101,102 };
    vecGraph[93] = { 81,82,91,93,102,103 };
    vecGraph[94] = { 82,83,92,94,103,104 };
    vecGraph[95] = { 83,84,93,95,104,105 };
    vecGraph[96] = { 84,85,94,96,105,106 };
    vecGraph[97] = { 85,86,95,97,106,107 };
    vecGraph[98] = { 86,87,96,98,107,108 };
    vecGraph[99] = { 121,87,97,108,109 };
    vecGraph[100] = { -1,88,89,100,110 };
    vecGraph[101] = { 89,90,99,101,110,111 };
    vecGraph[102] = { 90,91,100,102,111,112 };
    vecGraph[103] = { 91,92,101,103,112,113 };
    vecGraph[104] = { 92,93,102,104,113,114 };
    vecGraph[105] = { 93,94,103,105,114,115 };
    vecGraph[106] = { 94,95,104,106,115,116 };
    vecGraph[107] = { 95,96,105,107,116,117 };
    vecGraph[108] = { 96,97,106,108,117,118 };
    vecGraph[109] = { 97,98,107,109,118,119 };
    vecGraph[110] = { 121,98,108,119,120 };
    vecGraph[111] = { -1,99,100,111 };
    vecGraph[112] = { 100,101,110,112 };
    vecGraph[113] = { 101,102,111,113 };
    vecGraph[114] = { 102,103,112,114 };
    vecGraph[115] = { 103,104,113,115 };
    vecGraph[116] = { 104,105,114,116 };
    vecGraph[117] = { 105,106,115,117 };
    vecGraph[118] = { 106,107,116,118 };
    vecGraph[119] = { 107,108,117,119 };
    vecGraph[120] = { 108,109,118,120 };
    vecGraph[121] = { 121,109,119 };
    vecGraph[122] = { 10,21,32,43,54,65,76,87,98,109,120 };
}

void initBoardGraph(int** board, int playSide, vector<int> vecGraph[])
{
    int maxNum = BOARD_SIZE * BOARD_SIZE + 2;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (playSide == RED_SIDE)
        {
            if (board[0][i] != -playSide)
            {
                vecGraph[0].push_back(i);
                vecGraph[i + 1].push_back(-1);
            }

            int lastX = maxNum - 1;
            if (board[BOARD_SIZE - 1][i] != -playSide)
            {
                int temp = (BOARD_SIZE - 1) * BOARD_SIZE + i;
                vecGraph[lastX].push_back(temp);
                vecGraph[temp + 1].push_back(121);
            }
        }
        else//蓝方
        {
            if (board[i][0] != -playSide)
            {
                int temp = i * BOARD_SIZE;
                vecGraph[0].push_back(temp);
                vecGraph[temp + 1].push_back(-1);
            }

            int lastX = maxNum - 1;
            if (board[i][BOARD_SIZE - 1] != -playSide)
            {
                int temp = i * BOARD_SIZE + (BOARD_SIZE - 1);
                vecGraph[lastX].push_back(temp);
                vecGraph[temp + 1].push_back(121);
            }
        }
    }

    int tempX, tempY;
    vector<int> vecSide;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == -playSide)
            {
                continue;
            }
            else if (board[i][j] == playSide)
            {
                vecSide.push_back(i * BOARD_SIZE + j);
            }

            int posIndex = i * BOARD_SIZE + j;

            tempX = i + dx6[0]; tempY = j + dy6[0];
            if (tempX >= 0 && board[tempX][tempY] != -playSide)
            {
                vecGraph[posIndex + 1].push_back(tempX * BOARD_SIZE + tempY);
            }


            tempX = i + dx6[1]; tempY = j + dy6[1];
            if (tempX >= 0 && tempY < BOARD_SIZE && board[tempX][tempY] != -playSide)
            {
                vecGraph[posIndex + 1].push_back(tempX * BOARD_SIZE + tempY);
            }

            tempX = i + dx6[2]; tempY = j + dy6[2];
            if (tempY >= 0 && board[tempX][tempY] != -playSide)
            {
                vecGraph[posIndex + 1].push_back(tempX * BOARD_SIZE + tempY);
            }

            tempX = i + dx6[3]; tempY = j + dy6[3];
            if (tempY < BOARD_SIZE && board[tempX][tempY] != -playSide)
            {
                vecGraph[posIndex + 1].push_back(tempX * BOARD_SIZE + tempY);
            }

            tempX = i + dx6[4]; tempY = j + dy6[4];
            if (tempX < BOARD_SIZE && tempY >= 0 && board[tempX][tempY] != -playSide)
            {
                vecGraph[posIndex + 1].push_back(tempX * BOARD_SIZE + tempY);
            }

            tempX = i + dx6[5]; tempY = j + dy6[5];
            if (tempX < BOARD_SIZE && board[tempX][tempY] != -playSide)
            {
                vecGraph[posIndex + 1].push_back(tempX * BOARD_SIZE + tempY);
            }
        }

    }



    for (int i = 0; i < vecSide.size(); i++)
    {
        addNode(vecGraph, vecSide[i]);
    }
    //vecGraph[0] = {0,1};

    /*printf("\n");
    for(int i=0;i<BOARD_SIZE*BOARD_SIZE+2;i++)
    {
        printf("vecGraph[%d] = {",i);
        for(int j=0;j<vecGraph[i].size();j++)
        {
            printf("%d",vecGraph[i][j]);
            j == vecGraph[i].size()-1 ?  printf("};"):printf(",");
        }
        printf("\n");
    }*/

    //return vecGraph;
}

double valueRed(vector<int> vecRedGraph[], vector<int> vecBlueGraph[])
{
    double redValue = bfs(vecRedGraph); cout << redValue << endl;
    double blueValue = bfs(vecBlueGraph); cout << blueValue << endl;
    return -(redValue - blueValue);
}



double bfs(vector<int> vecGraph[])
{
    vector<int> vecQueue1, vecQueue2;
    vecQueue1 = vecGraph[0];

    if (vecQueue1.empty())
    {
        return -1;
    }

    bool** used = (bool**)malloc(sizeof(bool*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        used[i] = (bool*)malloc(sizeof(bool) * BOARD_SIZE);
        memset(used[i], false, sizeof(bool) * BOARD_SIZE);
    }

    int minPath = 0;
    int minPathNumber = 0;
    int tempX, tempY;
    int tempXX, tempYY;
    bool isContinue = true;

    while (isContinue)
    {
        //对于每一个连接的点
        for (int i = 0; i < vecQueue1.size(); i++)
        {
            if (vecQueue1[i] == -1)
            {
                continue;
            }

            if (vecQueue1[i] == 121)
            {
                minPathNumber++;
                isContinue = false;
                continue;
            }

            tempX = vecQueue1[i] / BOARD_SIZE;
            tempY = vecQueue1[i] % BOARD_SIZE;
            used[tempX][tempY] = true;


            for (int j = 0; j < vecGraph[vecQueue1[i] + 1].size(); j++)
            {
                int pos = vecGraph[vecQueue1[i] + 1][j];
                tempXX = pos / BOARD_SIZE;
                tempYY = pos % BOARD_SIZE;
                if (pos == -1)
                {
                    continue;
                }
                if (pos == 121)
                {
                    vecQueue2.push_back(pos);
                    continue;
                }
                if (!used[tempXX][tempYY])
                {
                    used[tempXX][tempYY] = true;
                    vecQueue2.push_back(pos);
                }
            }



        }

        vecQueue1 = vecQueue2;
        vecQueue2.clear();
        minPath++;

    }

    minPath--;

    //printf("min:%d,%d\n",minPath,minPathNumber);

    return minPath + (double)minPathNumber / 1000.0;
}


void disPlayGraph(vector<int> vecGraph[])
{
    printf("\n");
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE + 2; i++)
    {
        printf("%3d.all size:%2d ", i, vecGraph[i].size());
        for (int j = 0; j < vecGraph[i].size(); j++)
        {
            printf("(%d,%d) ", vecGraph[i][j] / BOARD_SIZE, vecGraph[i][j] % BOARD_SIZE);
        }
        printf("\n");
    }
}


void cutNode(vector<int> vecGraph[], int cutPos)
{
    for (int i = 0; i < vecGraph[cutPos + 1].size(); i++)
    {
        int tempPos = vecGraph[cutPos + 1][i] + 1;
        vecGraph[tempPos].erase(std::remove(vecGraph[tempPos].begin(), vecGraph[tempPos].end(), cutPos),
            vecGraph[tempPos].end());
    }
    vecGraph[cutPos + 1].clear();

}

void addNode(vector<int> vecGraph[], int addPos)
{
    //找到对应的向量位置
    //遍历所有的该位置连接的点集合A
    //对相应点a的向量数组，删去addpos，加上其他点b属于A&&b!=addpos
    int posSize = vecGraph[addPos + 1].size();
    for (int i = 0; i < posSize; i++)
    {
        int tempPos = vecGraph[addPos + 1][i] + 1;
        for (int j = 0; j < posSize; j++)
        {
            if (j == i)//不能加自身点
            {
                vecGraph[tempPos].erase(remove(vecGraph[tempPos].begin(), vecGraph[tempPos].end(),
                    addPos), vecGraph[tempPos].end());
                continue;
            }


            vecGraph[tempPos].push_back(vecGraph[addPos + 1][j]);

        }

        sort(vecGraph[tempPos].begin(), vecGraph[tempPos].end());

        // 使用std::unique函数和erase方法删除重复元素
        vecGraph[tempPos].erase(unique(vecGraph[tempPos].begin(), vecGraph[tempPos].end()),
            vecGraph[tempPos].end());

    }
    vecGraph[addPos + 1].clear();
}

void selfPlay()
{
    int round = 100;
    int redWin = 0;
    int blueWin = 0;
    int playSide = RED_SIDE;

    int** hexBoard = (int**)malloc(sizeof(int*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        hexBoard[i] = (int*)malloc(sizeof(int) * BOARD_SIZE);
    }

    while (round--)
    {
        playSide = RED_SIDE;
        initBoard(hexBoard);

        while (!isSideWin(hexBoard, -playSide))
        {
            if (playSide == RED_SIDE)
            {
                uctAll(hexBoard, playSide, 1);
            }
            else
            {
                uctAll(hexBoard, playSide, 1);
            }
            playSide = -playSide;
        }
        - playSide == RED_SIDE ? redWin++ : blueWin++;
        printf("red : blue = [%d,%d]\n", redWin, blueWin);
    }
}

int uctAll(int** board, int moveSide, double time)//uct算法
{

    UCTNode* uctTree = new UCTNode;
    int bestPos = -1;

    int** tempBoard = (int**)malloc(sizeof(int*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        tempBoard[i] = (int*)malloc(sizeof(int) * BOARD_SIZE);
        //memcpy(tempBoard[i],board[i],sizeof(int) * BOARD_SIZE);
    }




    /*int recordBoard[BOARD_SIZE][BOARD_SIZE];
    for(int i=0;i<BOARD_SIZE;i++)
    {
        for(int j=0;j<BOARD_SIZE;j++)
        {
            recordBoard[i][j] = board[i][j];
        }
    }

    int recordBoard2[BOARD_SIZE][BOARD_SIZE];

    memcpy(recordBoard2,recordBoard,169*4);//复制当前棋盘*/



    uctInit(uctTree, moveSide);

    UCTNode* currentNode;

    clock_t startTime = clock();




    while (1)
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            memcpy(tempBoard[i], board[i], sizeof(int) * BOARD_SIZE);
        }


        UCTNode* selectNode = uctSelect(uctTree, tempBoard);//选择

        uctExpand(selectNode, tempBoard);//模拟，扩展，反向传播


        //uctCount++;

        clock_t endTime = clock();

        if ((double)(endTime - startTime) / CLOCKS_PER_SEC > time)//|| uctTree->attempt > 10000 * 400 || uctDepth > 10)
        {
            //uctDisplayUCTNode(uctTree);
            double uctWinPro = 0;

            UCTNode* bestNode = uctTree->vecNodes[0];

            for (int i = 0; i < uctTree->vecNodes.size(); i++)
            {
                if (uctTree->vecNodes[i]->attempt > bestNode->attempt)
                {
                    bestNode = uctTree->vecNodes[i];
                }
            }

            uctWinPro = (double)(bestNode->win + bestNode->attempt) / 2 / bestNode->attempt * 100;
            //printf("attempt = %d,win = %f\n",uctTree->attempt,uctWinPro);

            bestPos = bestNode->x * BOARD_SIZE + bestNode->y;


            board[bestNode->x][bestNode->y] = moveSide;


            deleteRoot(uctTree);
            break;
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        free(tempBoard[i]);
    }
    free(tempBoard);


    return bestPos;
}


void uctDisplayUCTNode(UCTNode* node)
{
    if (node->vecNodes.empty() == true)
    {//初始化结点

        printf("no diaplay node!");
        return;
    }

    cout << "first depth:" << endl;

    for (int i = 0; i < node->vecNodes.size(); i++)
    {
        printf("(%f) ", uctGetR(node->vecNodes[i]));
        printf("%3d.(%2d,%2d) ", i + 1, node->vecNodes[i]->x, node->vecNodes[i]->y);
        printf("win:%d,attempt:%d,pro:%0.0f,r:%0.2f\n", (node->vecNodes[i]->win + node->vecNodes[i]->attempt) / 2, node->vecNodes[i]->attempt,
            (double)node->vecNodes[i]->win / node->vecNodes[i]->attempt * 100, node->vecNodes[i]->r);

    }

}

void uctInit(UCTNode* uctRoot, int moveSide)
{
    uctRoot->x = -1;
    uctRoot->y = -1;


    uctRoot->side = -moveSide;
    uctRoot->r = 0;

    uctRoot->win = 0;
    uctRoot->attempt = 0;

    uctRoot->parent = NULL;
}


UCTNode* uctSelect(UCTNode* node, int** board)//UCT算法的选择
{
    int i;
    UCTNode* currentPtr = node;
    UCTNode* nextPtr = node;
    double tempR;
    double bestR;
    //POSITION pos;
    //int j=0;

    while (!currentPtr->vecNodes.empty())
    {
        //j++;
        currentPtr = nextPtr->vecNodes[0];
        bestR = uctGetR(currentPtr, UCT_C);

        //寻找的uct公式最好的一步棋
        for (i = 0; i < nextPtr->vecNodes.size(); i++)
        {

            tempR = uctGetR(nextPtr->vecNodes[i], UCT_C);
            nextPtr->vecNodes[i]->r = tempR;

            if (tempR > bestR)
            {
                bestR = tempR;
                currentPtr = nextPtr->vecNodes[i];
            }
        }

        //下棋
        board[currentPtr->x][currentPtr->y] = currentPtr->side;

        nextPtr = currentPtr;
        //uctDepth++;
    }

    return currentPtr;

}

UCTNode* uctSelect(UCTNode* node, int board[][BOARD_SIZE])//UCT算法的选择
{
    int i;
    UCTNode* currentPtr = node;
    UCTNode* nextPtr = node;
    double tempR;
    double bestR;
    //POSITION pos;
    //int j=0;

    while (!currentPtr->vecNodes.empty())
    {
        //j++;
        currentPtr = nextPtr->vecNodes[0];
        bestR = uctGetR(currentPtr, UCT_C);

        //寻找的uct公式最好的一步棋
        for (i = 0; i < nextPtr->vecNodes.size(); i++)
        {

            tempR = uctGetR(nextPtr->vecNodes[i], UCT_C);
            nextPtr->vecNodes[i]->r = tempR;

            if (tempR > bestR)
            {
                bestR = tempR;
                currentPtr = nextPtr->vecNodes[i];
            }
        }

        //下棋
        board[currentPtr->x][currentPtr->y] = currentPtr->side;

        nextPtr = currentPtr;
        //uctDepth++;
    }

    return currentPtr;

}


void uctExpand(UCTNode* node, int** board)//UCT算法的扩展
{
    UCTNode* currentPtr = node;
    int moveSide = -currentPtr->side;

    //如果棋局能得出胜负
    if (isSideWin(board, -moveSide) == true)
    {
        uctBackPropagation(currentPtr, 1);
        return;
    }

    //结点未满40次不扩展
    if (node->attempt < 50 && node->attempt >= 0)
    {

        if (uctSimulate(node, board, -moveSide) == -moveSide)
            uctBackPropagation(node, 1);
        else//从我方下棋开始且最后我方赢棋
            uctBackPropagation(node, -1);
        return;
    }





    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (!board[i][j])
            {
                UCTNode* newNode = new UCTNode;

                newNode->x = i;
                newNode->y = j;
                newNode->parent = currentPtr;
                newNode->side = newNode->parent->side * -1;
                newNode->attempt = 1;
                newNode->win = 1;

                node->vecNodes.push_back(newNode);
            }
        }
    }

}

void uctExpand(UCTNode* node, int board[][BOARD_SIZE])//UCT算法的扩展
{
    UCTNode* currentPtr = node;
    int moveSide = -currentPtr->side;

    //如果棋局能得出胜负
    if (isSideWin(board, -moveSide) == true)
    {
        uctBackPropagation(currentPtr, 1);
        return;
    }

    //结点未满40次不扩展
    if (node->attempt < 50 && node->attempt >= 0)
    {

        if (uctSimulate(node, board, -moveSide) == -moveSide)
            uctBackPropagation(node, 1);
        else//从我方下棋开始且最后我方赢棋
            uctBackPropagation(node, -1);
        return;
    }



    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (!board[i][j])
            {
                UCTNode* newNode = new UCTNode;

                newNode->x = i;
                newNode->y = j;
                newNode->parent = currentPtr;
                newNode->side = newNode->parent->side * -1;
                newNode->attempt = 1;
                newNode->win = 1;

                node->vecNodes.push_back(newNode);
            }
        }
    }

}


//得到r值
double uctGetR(UCTNode* node, double uctC)
{
    double pro = (double)node->win / node->attempt;
    double explore = uctC * (double)sqrt((double)log(node->parent->attempt) / node->attempt);


    return  pro + explore;
}

int uctSimulate(UCTNode* node, int** board, int beginSide)
{


    vector<int> vecPos = generateSideMovePos(board);
    random_shuffle(vecPos.begin(), vecPos.end());
    for (auto i = vecPos.begin(); i != vecPos.end(); i++)
    {
        board[(*i) / BOARD_SIZE][(*i) % BOARD_SIZE] = beginSide;

        beginSide = -beginSide;
    }
    vecPos.clear();

    if (isRedWin(board))
        return RED_SIDE;
    else
        return BLUE_SIDE;
}

int uctSimulate(UCTNode* node, int board[][BOARD_SIZE], int beginSide)
{
    vector<int> vecPos = generateSideMovePos(board);
    random_shuffle(vecPos.begin(), vecPos.end());
    for (auto i = vecPos.begin(); i != vecPos.end(); i++)
    {
        board[(*i) / BOARD_SIZE][(*i) % BOARD_SIZE] = beginSide;

        beginSide = -beginSide;
    }
    vecPos.clear();

    if (isRedWin(board))
        return RED_SIDE;
    else
        return BLUE_SIDE;
}


int uctSimulateOMP(int** board, int beginSide, int useThreadsNum)
{
    vector<int> vecPos = generateSideMovePos(board);
    int wins = 0;

    //#pragma omp parallel for reduction(+:wins)
#pragma omp parallel for shared(wins),firstprivate(useThreadsNum,board,vecPos,beginSide)
    for (int i = 0; i < useThreadsNum; i++)
    {
        random_shuffle(vecPos.begin(), vecPos.end());
        for (auto i = vecPos.begin(); i != vecPos.end(); i++)
        {
            board[(*i) / BOARD_SIZE][(*i) % BOARD_SIZE] = beginSide;

            beginSide = -beginSide;
        }

        if (isRedWin(board))
            wins++;
        else
            wins--;

    }

    vecPos.clear();

    return wins;

}




void uctBackPropagation(UCTNode* node, int isWin)//UCT算法的反向传播
{
    UCTNode* currentNode = node;
    int winSide = isWin * node->side;


    //将win，attemp传播
    while (currentNode != NULL)
    {
        currentNode->attempt++;

        if (currentNode->side == winSide)
        {
            currentNode->win += 1;
        }

        currentNode = currentNode->parent;
    }

}



void deleteRoot(UCTNode* node)
{
    if (!node->vecNodes.empty())
    {
        for (int i = 0; i < node->vecNodes.size(); i++)
        {
            deleteRoot(node->vecNodes[i]);
        }
        delete(node);
    }
    else
    {
        delete(node);
    }

}



