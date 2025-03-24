// vsHexQL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "global.h"


int main() {

 

   
    Net modelRed,modelBlue;
    modelRed.init();modelBlue.init();
     //modelRed.load_mode("model\\newmodelRed-size-4.dat"); modelBlue.load_mode("model\\newmodelBlue-size-4.dat");
    //modelRed.display(false); modelBlue.display(false);
    selfPlayExecQ(modelRed,0);
    for (int i = 0; i < 40000; ++i) {
        //printf("[lose:%f]",trainNet(modelRed, modelBlue, colletData(modelRed, modelBlue)));

        dmc(modelRed, modelBlue,1);
        //modelRed.save_mode("model\\modelRed-size-4.dat");modelBlue.save_mode("model\\modelBlue-size-4.dat");
        selfPlayExecQ(modelRed,5);
    }
    
    
    return 0;
}
/*
int main()
{
    srand((unsigned)time(0));

    int** hexBoard = (int**)malloc(sizeof(int*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        hexBoard[i] = (int*)malloc(sizeof(int) * BOARD_SIZE);
    }

    initBoard(hexBoard);

    //bool ** a = initGraph();
    //findMinPath(hexBoard);
    vector<int> vecRedGraph[VEC_GRAPH_SIZE], vecBlueGraph[VEC_GRAPH_SIZE];
    //initRedGraph(vecRedGraph);initBlueGraph(vecBlueGraph);printf("A");
    //addNode(vecRedGraph,60);
//valueRed(vecRedGraph,vecBlueGraph);

    //uctAll(hexBoard,RED_SIDE,3);
    displayBoard(hexBoard);


    //readFileQTable();
    //writeFileQValue("100",1);
    //QLearning();
    selfPlayExecQ();



    return 0;
}*/


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
