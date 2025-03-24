#include"QLearning.h"


extern uint64_t hashTable[BOARD_SIZE][BOARD_SIZE][2];

map<uint64_t, QTABLE> MapHashQTable;
map<uint64_t, QTABLE> MapHashQTable2;
map<uint64_t, QTABLE> MapHashQTableBlue;

//读文件中的Q表
void readFileQTable()
{
    int i, j;
    QTABLE QTable;

    FILE* QTableFilePtr;

    //打开文件
    if ((QTableFilePtr = fopen("data\\QLearning.dat", "r")) == NULL)
    {
        printf("Open QLearning.dat error!");
        perror("because:");
        exit(0);
    }
    else
    {

        if (fgetc(QTableFilePtr) == EOF)
        {

            cout << "QLearning hash all deposit into map . Total hash value are : 0" << endl << endl;

            //关闭文件
            fclose(QTableFilePtr);

            return;
        }
        rewind(QTableFilePtr);

        //文件中是否结束
        while (!feof(QTableFilePtr))
        {
            fscanf(QTableFilePtr, "%llu ", &QTable.state);


            for (i = 0; i < BOARD_SIZE; i++)
            {
                for (j = 0; j < BOARD_SIZE; j++)
                {
                    fscanf(QTableFilePtr, "%f ", &QTable.Q[i][j]);
                }
            }

            //存入map
            MapHashQTable.insert(pair<uint64_t, QTABLE>(QTable.state, QTable));
            //MapHashTwoStepQTable.insert(pair<uint64_t,QTABLE>(QTable.state,QTable));//前俩步

//printf("<%d>",MapHashTwoStepQTable.size());
            //printf("%llu %f\n",hashValue,value);
        }

        //关闭文件
        fclose(QTableFilePtr);


        cout << "QLearning hash all deposit into map .Total hash value are : " << MapHashQTable.size() << endl << endl;


    }
}

//读文件中的Q表
void readFileQTableBlue()
{
    int i, j;
    QTABLE QTable;

    FILE* QTableFilePtr;

    //打开文件
    if ((QTableFilePtr = fopen("data\\QLearningBlue.dat", "r")) == NULL)
    {
        printf("Open QLearningBlue.dat error!");
        perror("because:");
        exit(0);
    }
    else
    {

        if (fgetc(QTableFilePtr) == EOF)
        {

            cout << "QLearningBlue hash all deposit into map . Total hash value are : 0" << endl << endl;

            //关闭文件
            fclose(QTableFilePtr);

            return;
        }
        rewind(QTableFilePtr);

        //文件中是否结束
        while (!feof(QTableFilePtr))
        {
            fscanf(QTableFilePtr, "%llu ", &QTable.state);


            for (i = 0; i < BOARD_SIZE; i++)
            {
                for (j = 0; j < BOARD_SIZE; j++)
                {
                    fscanf(QTableFilePtr, "%f ", &QTable.Q[i][j]);
                }
            }

            //存入map
            MapHashQTableBlue.insert(pair<uint64_t, QTABLE>(QTable.state, QTable));
            //MapHashTwoStepQTable.insert(pair<uint64_t,QTABLE>(QTable.state,QTable));//前俩步

//printf("<%d>",MapHashTwoStepQTable.size());
            //printf("%llu %f\n",hashValue,value);
        }

        //关闭文件
        fclose(QTableFilePtr);


        cout << "QLearningBlue hash all deposit into map .Total hash value are : " << MapHashQTableBlue.size() << endl << endl;


    }
}

void writeFileQTableBlue()//Q表写入文件中
{
    printf("\nWrite QLearningBlue.dat start:");
    printf("All state are %d.\n", MapHashQTableBlue.size());

    map<uint64_t, QTABLE>::iterator it;

    QTABLE QTable;

    FILE* QTableFilePtr;

    //打开文件
    if ((QTableFilePtr = fopen("data\\QLearningBlue.dat", "w+")) == NULL)
    {
        printf("Open QLearningBlue.dat error!");
        exit(0);
    }
    else
    {
        //fseek(QTableFilePtr,0,SEEK_END);


        for (it = MapHashQTableBlue.begin(); it != MapHashQTableBlue.end(); it++)
        {

            fprintf(QTableFilePtr, "%llu ", it->first);

            for (int i = 0; i < BOARD_SIZE; i++)
            {
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    fprintf(QTableFilePtr, "%0.3f ", it->second.Q[i][j]);
                }
            }

        }


        //关闭文件
        fclose(QTableFilePtr);
    }

    printf("Write QLearningBlue.dat end.\n");
}

void writeFileQTable()//Q表写入文件中
{

    printf("\nWrite QLearning.dat start:");
    printf("All state are %d.\n", MapHashQTable.size());

    map<uint64_t, QTABLE>::iterator it;

    QTABLE QTable;

    FILE* QTableFilePtr;

    //打开文件
    if ((QTableFilePtr = fopen("data\\QLearning.dat", "w+")) == NULL)
    {
        printf("Open QLearning.dat error!");
        exit(0);
    }
    else
    {
        //fseek(QTableFilePtr,0,SEEK_END);


        for (it = MapHashQTable.begin(); it != MapHashQTable.end(); it++)
        {

            fprintf(QTableFilePtr, "%llu ", it->first);

            for (int i = 0; i < BOARD_SIZE; i++)
            {
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    fprintf(QTableFilePtr, "%0.3f ", it->second.Q[i][j]);
                }
            }

        }


        //关闭文件
        fclose(QTableFilePtr);
    }

    printf("Write QTableTwoStep\\QTableTwoStep.dat end.\n");
}

//创建Q表0-0.2
void createQTable(float QTable[][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            QTable[i][j] = (float)(rand() % 1000) / 1000;
            //QTable[i][j] += 0.4;
            //QTable[i][j] = 0;
        }
    }
    //displayQTable(QTable);
}

void displayQTable(float QTable[][BOARD_SIZE])
{
    printf("\n\n   ");
    printf("  ");
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        printf("%2d      ", j);
    }
    printf("\n\n");

    for (int i = 0; i < BOARD_SIZE; i++)
    {

        printf("%2d  ", i);//打印行号

        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf("%0.4f  ", QTable[i][j]);
        }

        printf("\n\n");//换行

    }
}

void displayVecUINT64_T(vector<uint64_t> vecUint64_t)//显示
{
    printf("\nvecUint64_t:\n");
    //int i=0;
    for (auto it = vecUint64_t.begin(); it != vecUint64_t.end(); it++)
    {
        //i++;
        printf("(%llu) ", (*it));
    }
    printf("\n");
}

//修剪Q表，将不合适的位置选为-1
void pruneQTable(float QTable[][BOARD_SIZE], int** board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            //有棋子或并不在正确位置中
            if (board[i][j])
            {
                QTable[i][j] = -1.00;
            }
        }
    }

}

//sw=stateWin,aw=actionWin
//sl=stateLose,al=actionLose
float findQTableMaxValue(float QTable[][BOARD_SIZE])
{
    float maxQ = -7;
    int pos = -1;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (QTable[i][j] > maxQ)
            {
                maxQ = QTable[i][j];
                //pos = (i+1)*13 + j+1;
            }
        }
    }

    return maxQ;
}

int findQTableMaxPos(float QTable[][BOARD_SIZE])
{
    float maxQ = -7;
    int pos = -1;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (QTable[i][j] > maxQ)
            {
                maxQ = QTable[i][j];
                pos = i * BOARD_SIZE + j;
            }
        }
    }

    return pos;
}


void updateQTable(vector<uint64_t> vecSW, vector<int> vecAW,
    vector<uint64_t> vecSL, vector<int> vecAL, map<uint64_t, QTABLE>& MapHashQTable,int option)
{
    int winSize = vecSW.size();
    int loseSize = vecSL.size();
    if (winSize != vecAW.size() || loseSize != vecAL.size() || winSize == 0 || loseSize == 0)
    {
        cout << "updateQTable winSize error" << endl;
        exit(0);
    }
    int** board;

    for (auto i = vecSW.begin(); i != vecSW.end(); i++)
    {
        if (!isFindState((*i), board, 0))
        {
            cout << "updateQTable state error1" << endl;
        }
    }

    for (auto i = vecSL.begin(); i != vecSL.end(); i++)
    {
        if (!isFindState((*i), board, 0))
        {
            cout << "updateQTable state error2" << endl;
        }
    }


    //获胜方操作
    //winSize--;
    int actionX, actionY;
    uint64_t boardHash = 0;
    float QNextValue;
    map<uint64_t, QTABLE>::iterator it;

    if (option == 1)
    {
        winSize--;
        it = MapHashQTable.find(vecSW[winSize]);//获胜最后一步State
        actionX = vecAW[winSize] / BOARD_SIZE; actionY = vecAW[winSize] % BOARD_SIZE;//获胜最后一步actionPos
        //displayQTable(it->second.Q);
        //printf("WIN Start:\n(%llu,%d,%d,[Lq:%f]  ",vecSW[winSize],actionX,actionY, it->second.Q[actionX][actionY]);

        it->second.Q[actionX][actionY] += ALPHA * (REWARD - it->second.Q[actionX][actionY]);//奖励获胜步
        //printf("[Q:%f])\n", it->second.Q[actionX][actionY]);
        //displayQTable(it->second.Q);
        QNextValue = findQTableMaxValue(it->second.Q);//找此state最大maxQ，用于前一步
        winSize--;
        while (winSize != -1)//
        {
            it = MapHashQTable.find(vecSW[winSize]);
            actionX = vecAW[winSize] / BOARD_SIZE; actionY = vecAW[winSize] % BOARD_SIZE;
            //displayQTable(it->second.Q);
           // printf("(%llu,%d,%d,[Lq:%f]  ",vecSW[winSize],actionX,actionY, it->second.Q[actionX][actionY]);
            it->second.Q[actionX][actionY] += ALPHA * (GAMMA * QNextValue - it->second.Q[actionX][actionY]);
            //printf("[Q:%f])\n", it->second.Q[actionX][actionY]);
            //displayQTable(it->second.Q);
            QNextValue = findQTableMaxValue(it->second.Q);//找最大maxQ
            winSize--;
        }//获胜方更新完毕
    }
    else if (option == 2)
    {
        //失败方操作
        loseSize--;
        it = MapHashQTable.find(vecSL[loseSize]);//lose最后一步State
        actionX = vecAL[loseSize] / BOARD_SIZE; actionY = vecAL[loseSize] % BOARD_SIZE;//lose最后一步actionPos
        //printf("\nLose start:\n(%llu,%d,%d, [LQ:%f]  ",vecSL[loseSize],actionX,actionY, it->second.Q[actionX][actionY]);
        it->second.Q[actionX][actionY] += ALPHA * (0 - it->second.Q[actionX][actionY]);//惩罚失败步
        //printf("[Q:%f])\n", it->second.Q[actionX][actionY]);
        QNextValue = findQTableMaxValue(it->second.Q);//找此state最大maxQ，用于前一步
        loseSize--;
        while (loseSize != -1)//
        {
            it = MapHashQTable.find(vecSL[loseSize]);
            actionX = vecAL[loseSize] / BOARD_SIZE; actionY = vecAL[loseSize] % BOARD_SIZE;
            //printf("(%llu,%d,%d, [LQ:%f] ",vecSL[loseSize],actionX,actionY, it->second.Q[actionX][actionY]);
            it->second.Q[actionX][actionY] += ALPHA * (GAMMA * QNextValue - it->second.Q[actionX][actionY]);
            //printf("[Q:%f])\n", it->second.Q[actionX][actionY]);
            QNextValue = findQTableMaxValue(it->second.Q);//找最大maxQ
            loseSize--;
        }
    }
    


}


bool isFindState(uint64_t state, int** board, int isDepositMap)
{
    map<uint64_t, QTABLE>::iterator it;

    it = MapHashQTable.find(state);

    //未找到
    if (it == MapHashQTable.end())
    {
        //新建并存入Map
        if (isDepositMap == 1)
        {
            QTABLE QTable;
            QTable.state = state;
            createQTable(QTable.Q);//创建Q表
            pruneQTable(QTable.Q, board);
            //displayQTable(QTable.Q);
            MapHashQTable.insert(pair<uint64_t, QTABLE>(QTable.state, QTable));
        }

        return false;
    }
    else
    {
        return true;
    }
}




void selfPlayExecQ()
{
    getHashTable();//读入文件中的初始化的哈希表
    readFileQTable();//读文件中的Q表
    displayQTable(MapHashQTable.find(0)->second.Q);//显示初始情况
    map<uint64_t, QTABLE>::iterator it;
    uint64_t boardHash;

    int limitQStep = QLimitStep;
    int round = 1000;
    int redWin = 0;
    int blueWin = 0;
    int playSide = RED_SIDE;
    int playStep;

    int** hexBoard = (int**)malloc(sizeof(int*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        hexBoard[i] = (int*)malloc(sizeof(int) * BOARD_SIZE);
    }

    while (round--)
    {
        playSide = RED_SIDE;
        initBoard(hexBoard);
        playStep = 0;

        while (!isSideWin(hexBoard, -playSide))
        {
            if (playSide == RED_SIDE)
            {
                if (playStep < limitQStep)
                {
                    boardHash = calculateHash(hexBoard);
                    it = MapHashQTable.find(boardHash);
                    if (it != MapHashQTable.end())
                    {
                        int pos = findQTableMaxPos(it->second.Q);
                        hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                    }
                    else
                        uctAll(hexBoard, playSide, 1);
                }
                else
                    uctAll(hexBoard, playSide, 1);
            }
            else
            {
                uctAll(hexBoard, playSide, 1);
            }
            playSide = -playSide;
            playStep++;
        }
        - playSide == RED_SIDE ? redWin++ : blueWin++;
        printf("red : blue = [%d,%d]\n", redWin, blueWin);
    }

}




void QLearning()//Q学习
{
    srand((unsigned)time(0));
    int QLRound = 1000;
    vector<uint64_t> vecSRed, vecSBlue;
    vector<int> vecARed, vecABlue, vecAll;
    int playStep = 0;
    int playSide = RED_SIDE;
    uint64_t boardHash = 0;
    int limitQStep = QLimitStep;
    map<uint64_t, QTABLE>::iterator it;
    int pos;

    //int recordQNumber = 10;

    //初始化棋盘
    int** hexBoard = (int**)malloc(sizeof(int*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        hexBoard[i] = (int*)malloc(sizeof(int) * BOARD_SIZE);
    }

    if(0)
    {
        writeFileQValue("10",1);//清空文件夹中所有文件内容，将开头设置为-111
        writeFileQValue("100",1);//清空文件夹中所有文件内容，将开头设置为-111
        writeFileQValue("1000",1);//清空文件夹中所有文件内容，将开头设置为-111
    }
    

    getHashTable();//读入文件中的初始化的哈希表
    readFileQTable();//读文件中的Q表

    initBoard(hexBoard);
    isFindState(0, hexBoard, 1);

    while (QLRound--)
    {
        vecSRed.clear(); vecSBlue.clear();
        vecARed.clear(); vecABlue.clear();
        vecAll.clear();
        playSide = RED_SIDE;
        initBoard(hexBoard);
        //isFindState(0,hexBoard,1);
        playStep = 0;
        printf(".");

        //记录Q值变化，每训练10次
        if ((QLRound + 1) % 10 == 0)
        {

            //displayQTable(MapHashQTable.find(0)->second.Q);
            writeFileQValue("10", 0);
        }

        //记录Q值变化，每训练100次
        if ((QLRound + 1) % 100 == 0)
        {
            displayQTable(MapHashQTable.find(0)->second.Q);
            writeFileQValue("100", 0);
        }

        //记录Q值变化，每训练1000次
        if ((QLRound + 1) % 1000 == 0)
        {
            //displayQTable(MapHashQTable.find(0)->second.Q);
            writeFileQValue("1000", 0);
        }

        //未赢
        while (!isSideWin(hexBoard, -playSide))
        {
            //只收集limitQStep步数据
            if (playStep < limitQStep)
            {
                boardHash = calculateHash(hexBoard);
                isFindState(boardHash, hexBoard, 1);//1代表未找到状态就新建Q表到map
            }


            if (playSide == RED_SIDE && playStep < limitQStep)
                vecSRed.push_back(boardHash);
            else if (playSide == BLUE_SIDE && playStep < limitQStep)
                vecSBlue.push_back(boardHash);

            if (playSide == RED_SIDE)
            {
                if (playStep < limitQStep && (rand() % 100 >= EXPLORE * 100))//贪婪策略
                {
                    it = MapHashQTable.find(boardHash);
                    pos = findQTableMaxPos(it->second.Q);
                    hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;//printf("a");
                    //printf("{R%d,%d}",pos/BOARD_SIZE,pos%BOARD_SIZE);
                    //vecARed.push_back(pos);
                }
                else
                {
                    /*vector<int> vecAllMovePos = generateSideMovePos(hexBoard);
                    int randIndex = (rand())%vecAllMovePos.size();
                    pos = vecAllMovePos[randIndex];
                    hexBoard[pos/BOARD_SIZE][pos%BOARD_SIZE] = playSide;*/
                    pos = uctAll(hexBoard, playSide, 1);//printf("b");

                    //vecARed.push_back(pos);
                }

                vecAll.push_back(pos);

                if (playStep < limitQStep)
                    vecARed.push_back(pos);
            }
            else
            {
                if (playStep < limitQStep && (rand() % 100 >= EXPLORE * 100))
                {
                    it = MapHashQTable.find(boardHash);
                    pos = findQTableMaxPos(it->second.Q);
                    hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;//printf("c");
                    //printf("{B%d,%d}",pos/BOARD_SIZE,pos%BOARD_SIZE);
                    //vecABlue.push_back(pos);
                }
                else
                {
                    /*vector<int> vecAllMovePos = generateSideMovePos(hexBoard);
                    int randIndex = (rand())%vecAllMovePos.size();
                    pos = vecAllMovePos[randIndex];
                    hexBoard[pos/BOARD_SIZE][pos%BOARD_SIZE] = playSide;*/
                    pos = uctAll(hexBoard, playSide, 1);//printf("d");

                    //vecABlue.push_back(pos);
                }

                vecAll.push_back(pos);

                if (playStep < limitQStep)
                    vecABlue.push_back(pos);
            }
            playSide = -playSide;
            playStep++;

            //displayBoard(hexBoard);
            //system("pause");
        }
        //printf("\n%d win\n",-playSide);
        //displayBoard(hexBoard);


        //displayVecInt(vecARed);
        //displayVecInt(vecABlue);
        //system("pause");
        //displayVecUINT64_T(vecSRed);
        //displayVecUINT64_T(vecSBlue);

       // MapHashQTable2 = MapHashQTable;

        if (-playSide == RED_SIDE)//红方获胜
        {
            updateQTable(vecSRed,vecARed,vecSBlue,vecABlue, MapHashQTable,1);//红加蓝减
        }
        else
        {
            updateQTable(vecSBlue,vecABlue,vecSRed,vecARed, MapHashQTable,2);//红减蓝加
        }

        //auto temp = MapHashQTable;
        //MapHashQTable = MapHashQTable2;
        //MapHashQTable2 = temp;

        /*if (-playSide == RED_SIDE)//红方获胜
        {
            updateQTableExec(vecAll, vecSRed, vecARed, vecSBlue, vecABlue, MapHashQTable);
        }
        else
        {
            updateQTableExec(vecAll, vecSBlue, vecABlue, vecSRed, vecARed, MapHashQTable);
        }*/


    }

    writeFileQTable();//Q表写入文件

}



void writeFileQValue(string selectFile, int openOption)
{
    FILE* outfile = NULL;
    map<uint64_t, QTABLE>::iterator it;
    it = MapHashQTable.find(0);
    bool isFind = true;
    if (it == MapHashQTable.end())
    {
        isFind = false;
    }
    //displayQTable(it->second.Q);

    string fileName, fileName2;
    fileName = "data\\QChange" + selectFile;

    // 文件夹不存在则创建文件夹
    if (_access(fileName.c_str(), 0) == -1)
    {
        _mkdir(fileName.c_str());
    }

    fileName += "\\";

    //fileName += fileName + "data\\QValue.txt";

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            fileName2 = fileName;
            fileName2 = fileName2 + std::to_string(i) + "." + std::to_string(j) + ".dat";//打开相应文件

            if (openOption == 0)
            {
                outfile = fopen(fileName2.c_str(), "a");
            }
            else if (openOption == 1)
            {
                outfile = fopen(fileName2.c_str(), "w+");
            }

            if (outfile == NULL)//打开文件失败
            {
                printf("can not open the file!\n");
                exit(0);
            }
            else if (outfile != NULL)//打开文件成功
            {
                if (isFind)
                {
                    fprintf(outfile, "%f,", it->second.Q[i][j]);
                }
                else
                {
                    fprintf(outfile, "-111 ");
                }
            }

            //关闭文件
            fclose(outfile);

        }
    }
}



void updateQTableExec(vector<int> vecAll, vector<uint64_t> vecSW, vector<int> vecAW, 
    vector<uint64_t> vecSL, vector<int> vecAL, map<uint64_t, QTABLE> MapHashQTable2)
{
    //printf("||||%d||",vecAll.size());

    int** hexBoard = (int**)malloc(sizeof(int*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        hexBoard[i] = (int*)malloc(sizeof(int) * BOARD_SIZE);
    }
    initBoard(hexBoard);



    int tempSide = RED_SIDE;
    
    uint64_t* allHash = (uint64_t*)malloc(sizeof(uint64_t) * vecAll.size());
    uint64_t boardHash = 0;

    map<uint64_t, QTABLE>::iterator it;
    //map<uint64_t, QTABLE>::iterator it2;


    if (isFindState(boardHash, hexBoard, 1) == false)
    {
        printf("\n\nupdateQTable,isFindState error1\n");
    }//无state则存入初始化Q表

    int step = 1;

    for (int i = 0; i < vecAll.size() -1; i++)
    {
        hexBoard[vecAll[i] / BOARD_SIZE][vecAll[i] % BOARD_SIZE] = tempSide;
        //printf("(%d,%d)", vecAll[i] / BOARD_SIZE, vecAll[i] % BOARD_SIZE);

        if (tempSide == RED_SIDE)
        {
            boardHash = boardHash ^ hashTable[vecAll[i] / BOARD_SIZE][vecAll[i] % BOARD_SIZE][0];
        }
        else
        {
            boardHash = boardHash ^ hashTable[vecAll[i] / BOARD_SIZE][vecAll[i] % BOARD_SIZE][1];
        }
        allHash[i] = boardHash;
        

        if (isFindState(boardHash, hexBoard, 0) == false)
        {
            displayBoard(hexBoard);
            printf("\n\nupdateQTable,isFindState error2\n");
            system("pause");
        }

        tempSide = -tempSide;
    }

    float QNextValue;
    uint64_t QNextHash;
    int i = vecAll.size() - 1;

    it = MapHashQTable2.find(allHash[i - 1]);//q值在前一个状态里
    //it2 = MapHashQTable.find(allHash[i - 1]);
    if (isFindState(allHash[i - 1], hexBoard) == false)
    {
        cout << "updateQTable error";
    }
    //printf("Start(%llu,%d,%d)",allHash[i-1],vecAll[i]/BOARD_SIZE,vecAll[i]%BOARD_SIZE);

    it->second.Q[vecAll[i] / BOARD_SIZE][vecAll[i] % BOARD_SIZE] += ALPHA * (REWARD - it->second.Q[vecAll[i] / BOARD_SIZE][vecAll[i] % BOARD_SIZE]);
    
    
    QNextValue = findQTableMaxValue(it->second.Q);//it->second.Q[vecAll[i].x-1][vecAll[i].y-1];
    QNextHash = allHash[i - 1];

    i = i - 2;

    //更新获胜方
    for (; i >= 0; i -= 2)
    {
        if (i == 0)
        {
            it = MapHashQTable2.find(0);//第一步棋的前一个状态在hash=0的q表中
            
            //printf("(%llu,%d,%d)",allHash[i-1],vecAll[i]/BOARD_SIZE,vecAll[i]%BOARD_SIZE);
        }
        else
        {
            it = MapHashQTable2.find(allHash[i - 1]);//q值在前一个状态里
            
            //printf("(%llu,%d,%d)",allHash[i-1],vecAll[i]/BOARD_SIZE,vecAll[i]%BOARD_SIZE);
            if (isFindState(allHash[i - 1], hexBoard) == false)
            {
                cout << "updateQTable error";
            }

        }
        
        it->second.Q[vecAll[i] / BOARD_SIZE][vecAll[i] % BOARD_SIZE] = it->second.Q[vecAll[i] / BOARD_SIZE][vecAll[i] % BOARD_SIZE] +
            ALPHA * (GAMMA * QNextValue - it->second.Q[vecAll[i] / BOARD_SIZE][vecAll[i] % BOARD_SIZE]);
        
     
        //QNextValue = it->second.Q[vecAll[i].x-1][vecAll[i].y-1];
        QNextValue = findQTableMaxValue(it->second.Q);
    }


    //惩罚失败方

    i = vecAll.size() - 2;

    it = MapHashQTable2.find(allHash[i - 1]);//q值在前一个状态里
    
    if (isFindState(allHash[i - 1], hexBoard) == false)
    {
        cout << "updateQTable error";
    }
    //printf("Start(%llu,%d,%d)",allHash[i-1],vecAll[i]/BOARD_SIZE,vecAll[i]%BOARD_SIZE);
   
    
    it->second.Q[vecAll[i] / BOARD_SIZE][vecAll[i] % BOARD_SIZE] += ALPHA * (0 - it->second.Q[vecAll[i] / BOARD_SIZE][vecAll[i] % BOARD_SIZE]);
    
    
    //QNextValue = it->second.Q[vecAll[i].x-1][vecAll[i].y-1];
    QNextValue = findQTableMaxValue(it->second.Q);
    i = i - 2;

    //更新失败方
    for (; i >= 0; i -= 2)
    {
        if (i == 0)
        {
            it = MapHashQTable2.find(0);//第一步棋的前一个状态在hash=0的q表中
      
            //printf("(%llu,%d,%d)",allHash[i-1],vecAll[i]/BOARD_SIZE,vecAll[i]%BOARD_SIZE);
        }
        else
        {
            it = MapHashQTable2.find(allHash[i - 1]);//q值在前一个状态里
            
            //printf("(%llu,%d,%d)",allHash[i-1],vecAll[i]/BOARD_SIZE,vecAll[i]%BOARD_SIZE);
            if (isFindState(allHash[i - 1], hexBoard) == false)
            {
                cout << "updateQTable error";
            }

        }
        

        it->second.Q[vecAll[i] / BOARD_SIZE][vecAll[i] % BOARD_SIZE] = it->second.Q[vecAll[i] / BOARD_SIZE][vecAll[i] % BOARD_SIZE] +
            ALPHA * (GAMMA * QNextValue - it->second.Q[vecAll[i] / BOARD_SIZE][vecAll[i] % BOARD_SIZE]);
         
        
        //QNextValue = it->second.Q[vecAll[i].x-1][vecAll[i].y-1];
        QNextValue = findQTableMaxValue(it->second.Q);
    }

}

