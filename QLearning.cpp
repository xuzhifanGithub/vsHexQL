#include"QLearning.h"


extern uint64_t hashTable[BOARD_SIZE][BOARD_SIZE][2];

map<uint64_t, QTABLE> MapHashQTable;
map<uint64_t, QTABLE> MapHashQTable2;
map<uint64_t, QTABLE> MapHashQTableBlue;

//���ļ��е�Q��
void readFileQTable()
{
    int i, j;
    QTABLE QTable;

    FILE* QTableFilePtr;

    //���ļ�
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

            //�ر��ļ�
            fclose(QTableFilePtr);

            return;
        }
        rewind(QTableFilePtr);

        //�ļ����Ƿ����
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

            //����map
            MapHashQTable.insert(pair<uint64_t, QTABLE>(QTable.state, QTable));
            //MapHashTwoStepQTable.insert(pair<uint64_t,QTABLE>(QTable.state,QTable));//ǰ����

//printf("<%d>",MapHashTwoStepQTable.size());
            //printf("%llu %f\n",hashValue,value);
        }

        //�ر��ļ�
        fclose(QTableFilePtr);


        cout << "QLearning hash all deposit into map .Total hash value are : " << MapHashQTable.size() << endl << endl;


    }
}

//���ļ��е�Q��
void readFileQTableBlue()
{
    int i, j;
    QTABLE QTable;

    FILE* QTableFilePtr;

    //���ļ�
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

            //�ر��ļ�
            fclose(QTableFilePtr);

            return;
        }
        rewind(QTableFilePtr);

        //�ļ����Ƿ����
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

            //����map
            MapHashQTableBlue.insert(pair<uint64_t, QTABLE>(QTable.state, QTable));
            //MapHashTwoStepQTable.insert(pair<uint64_t,QTABLE>(QTable.state,QTable));//ǰ����

//printf("<%d>",MapHashTwoStepQTable.size());
            //printf("%llu %f\n",hashValue,value);
        }

        //�ر��ļ�
        fclose(QTableFilePtr);


        cout << "QLearningBlue hash all deposit into map .Total hash value are : " << MapHashQTableBlue.size() << endl << endl;


    }
}

void writeFileQTableBlue()//Q��д���ļ���
{
    printf("\nWrite QLearningBlue.dat start:");
    printf("All state are %d.\n", MapHashQTableBlue.size());

    map<uint64_t, QTABLE>::iterator it;

    QTABLE QTable;

    FILE* QTableFilePtr;

    //���ļ�
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


        //�ر��ļ�
        fclose(QTableFilePtr);
    }

    printf("Write QLearningBlue.dat end.\n");
}

void writeFileQTable()//Q��д���ļ���
{

    printf("\nWrite QLearning.dat start:");
    printf("All state are %d.\n", MapHashQTable.size());

    map<uint64_t, QTABLE>::iterator it;

    QTABLE QTable;

    FILE* QTableFilePtr;

    //���ļ�
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


        //�ر��ļ�
        fclose(QTableFilePtr);
    }

    printf("Write QTableTwoStep\\QTableTwoStep.dat end.\n");
}

//����Q��0-0.2
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

        printf("%2d  ", i);//��ӡ�к�

        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf("%0.4f  ", QTable[i][j]);
        }

        printf("\n\n");//����

    }
}

void displayVecUINT64_T(vector<uint64_t> vecUint64_t)//��ʾ
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

//�޼�Q���������ʵ�λ��ѡΪ-1
void pruneQTable(float QTable[][BOARD_SIZE], int** board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            //�����ӻ򲢲�����ȷλ����
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


    //��ʤ������
    //winSize--;
    int actionX, actionY;
    uint64_t boardHash = 0;
    float QNextValue;
    map<uint64_t, QTABLE>::iterator it;

    if (option == 1)
    {
        winSize--;
        it = MapHashQTable.find(vecSW[winSize]);//��ʤ���һ��State
        actionX = vecAW[winSize] / BOARD_SIZE; actionY = vecAW[winSize] % BOARD_SIZE;//��ʤ���һ��actionPos
        //displayQTable(it->second.Q);
        //printf("WIN Start:\n(%llu,%d,%d,[Lq:%f]  ",vecSW[winSize],actionX,actionY, it->second.Q[actionX][actionY]);

        it->second.Q[actionX][actionY] += ALPHA * (REWARD - it->second.Q[actionX][actionY]);//������ʤ��
        //printf("[Q:%f])\n", it->second.Q[actionX][actionY]);
        //displayQTable(it->second.Q);
        QNextValue = findQTableMaxValue(it->second.Q);//�Ҵ�state���maxQ������ǰһ��
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
            QNextValue = findQTableMaxValue(it->second.Q);//�����maxQ
            winSize--;
        }//��ʤ���������
    }
    else if (option == 2)
    {
        //ʧ�ܷ�����
        loseSize--;
        it = MapHashQTable.find(vecSL[loseSize]);//lose���һ��State
        actionX = vecAL[loseSize] / BOARD_SIZE; actionY = vecAL[loseSize] % BOARD_SIZE;//lose���һ��actionPos
        //printf("\nLose start:\n(%llu,%d,%d, [LQ:%f]  ",vecSL[loseSize],actionX,actionY, it->second.Q[actionX][actionY]);
        it->second.Q[actionX][actionY] += ALPHA * (0 - it->second.Q[actionX][actionY]);//�ͷ�ʧ�ܲ�
        //printf("[Q:%f])\n", it->second.Q[actionX][actionY]);
        QNextValue = findQTableMaxValue(it->second.Q);//�Ҵ�state���maxQ������ǰһ��
        loseSize--;
        while (loseSize != -1)//
        {
            it = MapHashQTable.find(vecSL[loseSize]);
            actionX = vecAL[loseSize] / BOARD_SIZE; actionY = vecAL[loseSize] % BOARD_SIZE;
            //printf("(%llu,%d,%d, [LQ:%f] ",vecSL[loseSize],actionX,actionY, it->second.Q[actionX][actionY]);
            it->second.Q[actionX][actionY] += ALPHA * (GAMMA * QNextValue - it->second.Q[actionX][actionY]);
            //printf("[Q:%f])\n", it->second.Q[actionX][actionY]);
            QNextValue = findQTableMaxValue(it->second.Q);//�����maxQ
            loseSize--;
        }
    }
    


}


bool isFindState(uint64_t state, int** board, int isDepositMap)
{
    map<uint64_t, QTABLE>::iterator it;

    it = MapHashQTable.find(state);

    //δ�ҵ�
    if (it == MapHashQTable.end())
    {
        //�½�������Map
        if (isDepositMap == 1)
        {
            QTABLE QTable;
            QTable.state = state;
            createQTable(QTable.Q);//����Q��
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
    getHashTable();//�����ļ��еĳ�ʼ���Ĺ�ϣ��
    readFileQTable();//���ļ��е�Q��
    displayQTable(MapHashQTable.find(0)->second.Q);//��ʾ��ʼ���
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




void QLearning()//Qѧϰ
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

    //��ʼ������
    int** hexBoard = (int**)malloc(sizeof(int*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        hexBoard[i] = (int*)malloc(sizeof(int) * BOARD_SIZE);
    }

    if(0)
    {
        writeFileQValue("10",1);//����ļ����������ļ����ݣ�����ͷ����Ϊ-111
        writeFileQValue("100",1);//����ļ����������ļ����ݣ�����ͷ����Ϊ-111
        writeFileQValue("1000",1);//����ļ����������ļ����ݣ�����ͷ����Ϊ-111
    }
    

    getHashTable();//�����ļ��еĳ�ʼ���Ĺ�ϣ��
    readFileQTable();//���ļ��е�Q��

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

        //��¼Qֵ�仯��ÿѵ��10��
        if ((QLRound + 1) % 10 == 0)
        {

            //displayQTable(MapHashQTable.find(0)->second.Q);
            writeFileQValue("10", 0);
        }

        //��¼Qֵ�仯��ÿѵ��100��
        if ((QLRound + 1) % 100 == 0)
        {
            displayQTable(MapHashQTable.find(0)->second.Q);
            writeFileQValue("100", 0);
        }

        //��¼Qֵ�仯��ÿѵ��1000��
        if ((QLRound + 1) % 1000 == 0)
        {
            //displayQTable(MapHashQTable.find(0)->second.Q);
            writeFileQValue("1000", 0);
        }

        //δӮ
        while (!isSideWin(hexBoard, -playSide))
        {
            //ֻ�ռ�limitQStep������
            if (playStep < limitQStep)
            {
                boardHash = calculateHash(hexBoard);
                isFindState(boardHash, hexBoard, 1);//1����δ�ҵ�״̬���½�Q��map
            }


            if (playSide == RED_SIDE && playStep < limitQStep)
                vecSRed.push_back(boardHash);
            else if (playSide == BLUE_SIDE && playStep < limitQStep)
                vecSBlue.push_back(boardHash);

            if (playSide == RED_SIDE)
            {
                if (playStep < limitQStep && (rand() % 100 >= EXPLORE * 100))//̰������
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

        if (-playSide == RED_SIDE)//�췽��ʤ
        {
            updateQTable(vecSRed,vecARed,vecSBlue,vecABlue, MapHashQTable,1);//�������
        }
        else
        {
            updateQTable(vecSBlue,vecABlue,vecSRed,vecARed, MapHashQTable,2);//�������
        }

        //auto temp = MapHashQTable;
        //MapHashQTable = MapHashQTable2;
        //MapHashQTable2 = temp;

        /*if (-playSide == RED_SIDE)//�췽��ʤ
        {
            updateQTableExec(vecAll, vecSRed, vecARed, vecSBlue, vecABlue, MapHashQTable);
        }
        else
        {
            updateQTableExec(vecAll, vecSBlue, vecABlue, vecSRed, vecARed, MapHashQTable);
        }*/


    }

    writeFileQTable();//Q��д���ļ�

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

    // �ļ��в������򴴽��ļ���
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
            fileName2 = fileName2 + std::to_string(i) + "." + std::to_string(j) + ".dat";//����Ӧ�ļ�

            if (openOption == 0)
            {
                outfile = fopen(fileName2.c_str(), "a");
            }
            else if (openOption == 1)
            {
                outfile = fopen(fileName2.c_str(), "w+");
            }

            if (outfile == NULL)//���ļ�ʧ��
            {
                printf("can not open the file!\n");
                exit(0);
            }
            else if (outfile != NULL)//���ļ��ɹ�
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

            //�ر��ļ�
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
    }//��state������ʼ��Q��

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

    it = MapHashQTable2.find(allHash[i - 1]);//qֵ��ǰһ��״̬��
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

    //���»�ʤ��
    for (; i >= 0; i -= 2)
    {
        if (i == 0)
        {
            it = MapHashQTable2.find(0);//��һ�����ǰһ��״̬��hash=0��q����
            
            //printf("(%llu,%d,%d)",allHash[i-1],vecAll[i]/BOARD_SIZE,vecAll[i]%BOARD_SIZE);
        }
        else
        {
            it = MapHashQTable2.find(allHash[i - 1]);//qֵ��ǰһ��״̬��
            
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


    //�ͷ�ʧ�ܷ�

    i = vecAll.size() - 2;

    it = MapHashQTable2.find(allHash[i - 1]);//qֵ��ǰһ��״̬��
    
    if (isFindState(allHash[i - 1], hexBoard) == false)
    {
        cout << "updateQTable error";
    }
    //printf("Start(%llu,%d,%d)",allHash[i-1],vecAll[i]/BOARD_SIZE,vecAll[i]%BOARD_SIZE);
   
    
    it->second.Q[vecAll[i] / BOARD_SIZE][vecAll[i] % BOARD_SIZE] += ALPHA * (0 - it->second.Q[vecAll[i] / BOARD_SIZE][vecAll[i] % BOARD_SIZE]);
    
    
    //QNextValue = it->second.Q[vecAll[i].x-1][vecAll[i].y-1];
    QNextValue = findQTableMaxValue(it->second.Q);
    i = i - 2;

    //����ʧ�ܷ�
    for (; i >= 0; i -= 2)
    {
        if (i == 0)
        {
            it = MapHashQTable2.find(0);//��һ�����ǰһ��״̬��hash=0��q����
      
            //printf("(%llu,%d,%d)",allHash[i-1],vecAll[i]/BOARD_SIZE,vecAll[i]%BOARD_SIZE);
        }
        else
        {
            it = MapHashQTable2.find(allHash[i - 1]);//qֵ��ǰһ��״̬��
            
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

