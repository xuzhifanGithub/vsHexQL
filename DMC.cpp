

#include"DMC.h"

void dmc() {
    srand((unsigned)time(NULL));
    int** hexBoard = (int**)malloc(sizeof(int*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        hexBoard[i] = (int*)malloc(sizeof(int) * BOARD_SIZE);
    }
    initBoard(hexBoard);
    int playSide = RED_SIDE;
    int learn_round = 10000*10000;
    int train_time = 1*3 * 60;
    int train_epoch = 0;
    int pos;
    vector<Tensor2D> vecRedState,vecBlueState;
    int display_loss_round = 10*10000;
    
    Tensor2D onehotBoard = board_trans_onehot(hexBoard);

    Net model;
    model.init();
    clock_t startTime = clock();
    //model.display();
   
    
    while(1)//(learn_round--)
    {
        learn_round--;
        if (learn_round == 0)learn_round = 10000 * 10000;
        clock_t endTime = clock();
        if ((double)(endTime - startTime) / CLOCKS_PER_SEC > train_time) {
            break;
        }

        for (int i = 0; i < vecRedState.size(); ++i) {
            freeTensor(vecRedState[i]);
        }
        for (int i = 0; i < vecBlueState.size(); ++i) {
            freeTensor(vecBlueState[i]);
        }

        vecRedState.clear(); vecBlueState.clear();
        playSide = RED_SIDE;
        initBoard(hexBoard);
        Tensor2D_setzero(onehotBoard);
        //isFindState(0,hexBoard,1);
       

        

        //记录Q值变化，每训练1000次
        if ((learn_round + 1) % 1000 == 0) printf(".");;

        //未赢
        while (!isSideWin(hexBoard, -playSide)) {
            if (playSide == RED_SIDE)
            {
                if ((double)(rand() / RAND_MAX) >= EXPLORE)//贪婪策略
                {
                    vector<int> vecpos = generateSideMovePos(hexBoard);
                    float maxQ = -1000000;
                    pos = vecpos[0];
                    for (int i = 0; i < vecpos.size(); i++) {
                        onehotBoard.data[0][vecpos[i]] = 1.0;
                        float outQvalue = board_net_Qvalue(onehotBoard, model);
                        if (maxQ < outQvalue) {
                            maxQ = outQvalue; pos = vecpos[i];
                        }
                        onehotBoard.data[0][vecpos[i]] = 0;
                    }
                    hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                }
                else
                {
                    vector<int> vecAllMovePos = generateSideMovePos(hexBoard);
                    int randIndex = (rand())%vecAllMovePos.size();
                    pos = vecAllMovePos[randIndex];
                    hexBoard[pos/BOARD_SIZE][pos%BOARD_SIZE] = playSide;
                    //pos = uctAll(hexBoard, playSide, 1);//uct生成
                }
                onehotBoard.data[0][pos] = 1.0;
                Tensor2D temp_state = Tensor2D_copy(onehotBoard);
                vecRedState.push_back(temp_state);
                //freeTensor(temp_state);
            }
            else
            {
                if ((double)(rand() / RAND_MAX) >= EXPLORE)
                {
                    vector<int> vecpos = generateSideMovePos(hexBoard);
                    float maxQ = -1000000;
                    pos = vecpos[0];
                    for (int i = 0; i < vecpos.size(); i++) {
                        onehotBoard.data[0][BOARD_SIZE* BOARD_SIZE + vecpos[i]] = 1.0;
                        float outQvalue = board_net_Qvalue(onehotBoard, model);
                        if (maxQ < outQvalue) {
                            maxQ = outQvalue; pos = vecpos[i];
                        }
                        onehotBoard.data[0][BOARD_SIZE * BOARD_SIZE + vecpos[i]] = 0;
                    }
                    hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                }
                else
                {
                    vector<int> vecAllMovePos = generateSideMovePos(hexBoard);
                    int randIndex = (rand()) % vecAllMovePos.size();
                    pos = vecAllMovePos[randIndex];
                    hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                    //pos = uctAll(hexBoard, playSide, 1);//uct生成
                }
                //pos = uctAll(hexBoard, playSide, 0.01);
                onehotBoard.data[0][BOARD_SIZE * BOARD_SIZE + pos] = 1.0;
                Tensor2D temp_state = Tensor2D_copy(onehotBoard);
                vecBlueState.push_back(temp_state);
                //freeTensor(temp_state);
            }
            playSide = -playSide;
        }
        //printf("\n%d win\n",-playSide);
        //displayBoard(hexBoard);

        /*if (-playSide == RED_SIDE)//红方获胜
        {
            float isredwin = (-playSide == RED_SIDE ? 1.0 : -1.0);
            Tensor2D input,output;
            Tensor2D y_true = Tensor2D_init(1,1, isredwin);
            for (int i = 0; i < vecRedState.size(); i++) {
                input = vecRedState[i];
                output = model.forward(input, true);
                //Tensor2D_display(input);
                //Tensor2D_display(output);
                float lose = model.Linear_loss(output, y_true);
                if((learn_round) % display_loss_round == 0 && i == 0)printf("[lose:%f]", lose);
                //
                //system("pause");
                 model.backward(output, y_true, 0.0001);  
                //freeTensor(input);
                //freeTensor(output);
            }
            freeTensor(y_true);

            Tensor2D y_true2 = Tensor2D_init(1, 1, -isredwin);
            for (int i = 0; i < vecBlueState.size(); i++) {
                input = vecBlueState[i];
                output = model.forward(input, true);
                float lose = model.Linear_loss(output, y_true2);
                if ((learn_round) % display_loss_round == 0 && i == 0)printf("[lose:%f]", lose);
                //printf("[lose:%f]", lose);
                model.backward(output, y_true2, 0.0001);
            }
            
            freeTensor(y_true2);
            //system("pause");
        }*/
        //else
        {
            int forward_num = 10;
            float isRedWin = (-playSide == RED_SIDE ? 1.0 : -1.0);
            Tensor2D input, output;
            Tensor2D y_true = Tensor2D_init(1, 1, isRedWin);
            float men_lose = 0;
            for (int i = 0; i < vecRedState.size(); i++) {
                for (int j = 0; j < forward_num; j++) {
                    input = vecRedState[i];
                    output = model.forward(input, true);
                    float lose = model.Linear_loss(output, y_true);
                    if(j==0)men_lose += lose;
                
                    //printf("[lose:%f]", lose);
                    model.backward(output, y_true, 0.0001);
                }
                
            }
            if ((learn_round) % display_loss_round == 0) {
                printf("[red lose:%f]", men_lose / vecRedState.size());
            };
            freeTensor(y_true);

            Tensor2D y_true2 = Tensor2D_init(1, 1, -isRedWin);
            men_lose = 0;
            for (int i = 0; i < vecBlueState.size(); i++) {
                for (int j = 0; j < forward_num; j++) {
                    input = vecBlueState[i];
                    output = model.forward(input, true);
                    float lose = model.Linear_loss(output, y_true2);
                    if (j == 0)men_lose += lose;
                
                    //printf("[lose:%f]", lose);
                    model.backward(output, y_true2, 0.0001);
                }
                
            }
            if ((learn_round) % display_loss_round == 0) {
                printf("[blue lose:%f]", men_lose / vecBlueState.size());
                initBoard(hexBoard);
                printf("\n");
                for (int i = 0; i < BOARD_SIZE; i++) {
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        hexBoard[i][j] = RED_SIDE;
                        printf("%f,", board_net_Qvalue(hexBoard, model));
                        hexBoard[i][j] = EMPTY_POS;
                    }
                    printf("\n");
                }

            };
            freeTensor(y_true2);
        }
    }
    //model.display(true);
    model.save_mode("model\\model-size-4.dat");

    selfPlayExecQ(model,10);
    
}

void dmc(Net model) {
    srand((unsigned)time(NULL));
    int** hexBoard = (int**)malloc(sizeof(int*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        hexBoard[i] = (int*)malloc(sizeof(int) * BOARD_SIZE);
    }
    initBoard(hexBoard);
    int playSide = RED_SIDE;
    int learn_round = 10000 * 10000;
    int train_time = 1 * 3 * 60;
    int train_epoch = 0;
    int pos;
    vector<Tensor2D> vecRedState, vecBlueState;
    int display_loss_round = 10 * 10000;

    Tensor2D onehotBoard = board_trans_onehot(hexBoard);

    //model.init();
    clock_t startTime = clock();
    //model.display();
    //model.save_mode();
    //model.load_mode("model.dat");
    model.display(false);
    //printf("%d", model.netDepth);
    //system("pause");

    while (1)//(learn_round--)
    {
        learn_round--;
        if (learn_round == 0)learn_round = 10000 * 10000;
        clock_t endTime = clock();
        if ((double)(endTime - startTime) / CLOCKS_PER_SEC > train_time) {
            break;
        }

        for (int i = 0; i < vecRedState.size(); ++i) {
            freeTensor(vecRedState[i]);
        }
        for (int i = 0; i < vecBlueState.size(); ++i) {
            freeTensor(vecBlueState[i]);
        }

        vecRedState.clear(); vecBlueState.clear();
        playSide = RED_SIDE;
        initBoard(hexBoard);
        Tensor2D_setzero(onehotBoard);
        //isFindState(0,hexBoard,1);




        //记录Q值变化，每训练1000次
        if ((learn_round + 1) % 1000 == 0) printf(".");;

        //未赢
        while (!isSideWin(hexBoard, -playSide)) {
            if (playSide == RED_SIDE)
            {
                if ((double)(rand() / RAND_MAX) >= EXPLORE)//贪婪策略
                {
                    vector<int> vecpos = generateSideMovePos(hexBoard);
                    float maxQ = -1000000;
                    pos = vecpos[0];
                    for (int i = 0; i < vecpos.size(); i++) {
                        onehotBoard.data[0][vecpos[i]] = 1.0;
                        float outQvalue = board_net_Qvalue(onehotBoard, model);
                        if (maxQ < outQvalue) {
                            maxQ = outQvalue; pos = vecpos[i];
                        }
                        onehotBoard.data[0][vecpos[i]] = 0;
                    }
                    hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                }
                else
                {
                    vector<int> vecAllMovePos = generateSideMovePos(hexBoard);
                    int randIndex = (rand()) % vecAllMovePos.size();
                    pos = vecAllMovePos[randIndex];
                    hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                    //pos = uctAll(hexBoard, playSide, 1);//uct生成
                }
                onehotBoard.data[0][pos] = 1.0;
                Tensor2D temp_state = Tensor2D_copy(onehotBoard);
                vecRedState.push_back(temp_state);
                //freeTensor(temp_state);
            }
            else
            {
                if ((double)(rand() / RAND_MAX) >= EXPLORE)
                {
                    vector<int> vecpos = generateSideMovePos(hexBoard);
                    float maxQ = -1000000;
                    pos = vecpos[0];
                    for (int i = 0; i < vecpos.size(); i++) {
                        onehotBoard.data[0][BOARD_SIZE * BOARD_SIZE + vecpos[i]] = 1.0;
                        float outQvalue = board_net_Qvalue(onehotBoard, model);
                        if (maxQ < outQvalue) {
                            maxQ = outQvalue; pos = vecpos[i];
                        }
                        onehotBoard.data[0][BOARD_SIZE * BOARD_SIZE + vecpos[i]] = 0;
                    }
                    hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                }
                else
                {
                    vector<int> vecAllMovePos = generateSideMovePos(hexBoard);
                    int randIndex = (rand()) % vecAllMovePos.size();
                    pos = vecAllMovePos[randIndex];
                    hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                    //pos = uctAll(hexBoard, playSide, 1);//uct生成
                }
                //pos = uctAll(hexBoard, playSide, 0.01);
                onehotBoard.data[0][BOARD_SIZE * BOARD_SIZE + pos] = 1.0;
                Tensor2D temp_state = Tensor2D_copy(onehotBoard);
                vecBlueState.push_back(temp_state);
                //freeTensor(temp_state);
            }
            playSide = -playSide;
        }
        //printf("\n%d win\n",-playSide);
        //displayBoard(hexBoard);

        /*if (-playSide == RED_SIDE)//红方获胜
        {
            float isredwin = (-playSide == RED_SIDE ? 1.0 : -1.0);
            Tensor2D input,output;
            Tensor2D y_true = Tensor2D_init(1,1, isredwin);
            for (int i = 0; i < vecRedState.size(); i++) {
                input = vecRedState[i];
                output = model.forward(input, true);
                //Tensor2D_display(input);
                //Tensor2D_display(output);
                float lose = model.Linear_loss(output, y_true);
                if((learn_round) % display_loss_round == 0 && i == 0)printf("[lose:%f]", lose);
                //
                //system("pause");
                 model.backward(output, y_true, 0.0001);
                //freeTensor(input);
                //freeTensor(output);
            }
            freeTensor(y_true);

            Tensor2D y_true2 = Tensor2D_init(1, 1, -isredwin);
            for (int i = 0; i < vecBlueState.size(); i++) {
                input = vecBlueState[i];
                output = model.forward(input, true);
                float lose = model.Linear_loss(output, y_true2);
                if ((learn_round) % display_loss_round == 0 && i == 0)printf("[lose:%f]", lose);
                //printf("[lose:%f]", lose);
                model.backward(output, y_true2, 0.0001);
            }

            freeTensor(y_true2);
            //system("pause");
        }*/
        //else
        {
            int forward_num = 10;
            float isRedWin = (-playSide == RED_SIDE ? 1.0 : -1.0);
            Tensor2D input, output;
            Tensor2D y_true = Tensor2D_init(1, 1, isRedWin);
            float men_lose = 0;
            for (int i = 0; i < vecRedState.size(); i++) {
                for (int j = 0; j < forward_num; j++) {
                    input = vecRedState[i];
                    output = model.forward(input, true);
                    float lose = model.Linear_loss(output, y_true);
                    if (j == 0)men_lose += lose;

                    //printf("[lose:%f]", lose);
                    model.backward(output, y_true, 0.0001);
                }

            }
            if ((learn_round) % display_loss_round == 0) {
                printf("[red lose:%f]", men_lose / vecRedState.size());
            };
            freeTensor(y_true);

            Tensor2D y_true2 = Tensor2D_init(1, 1, -isRedWin);
            men_lose = 0;
            for (int i = 0; i < vecBlueState.size(); i++) {
                for (int j = 0; j < forward_num; j++) {
                    input = vecBlueState[i];
                    output = model.forward(input, true);
                    float lose = model.Linear_loss(output, y_true2);
                    if (j == 0)men_lose += lose;

                    //printf("[lose:%f]", lose);
                    model.backward(output, y_true2, 0.0001);
                }

            }
            if ((learn_round) % display_loss_round == 0) {
                printf("[blue lose:%f]", men_lose / vecBlueState.size());
            };
            freeTensor(y_true2);
        }
    }
}

void dmc(Net modelRed, Net modelBlue,int choice) {
    //srand((unsigned)time(NULL));
    std::random_device rd;
    srand(rd());
    int** hexBoard = (int**)malloc(sizeof(int*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        hexBoard[i] = (int*)malloc(sizeof(int) * BOARD_SIZE);
    }
    initBoard(hexBoard);
    int playSide = RED_SIDE;
    int learn_round = 10000 * 10000;
    int train_time = 1 * 1 * 30;
    int train_epoch = 0;
    int pos;
    vector<Tensor2D> vecRedState, vecBlueState;
    int display_loss_round = 1 * 10000;

    Tensor2D onehotBoard = board_trans_onehot(hexBoard);

    clock_t startTime = clock();
    float sum_epoch_red_lose = 0;
    float sum_epoch_blue_lose = 0;
    float sum_epoch_pro = 0;
    int sum_epoch_redwin = 0;
    int sum_epoch_bluewin = 0;
    //modelRed.display(false);
    //modelblue.display(false);
    vector<float> red_maxQ,blue_maxQ;
    vector<int> vec_redpos, vec_blue_pos;

    while (1)//(learn_round--)
    {
        learn_round--;
        if (learn_round == 0)learn_round = 10000 * 10000;
        clock_t endTime = clock();
        if ((double)(endTime - startTime) / CLOCKS_PER_SEC > train_time) {
            break;
        }

        for (int i = 0; i < vecRedState.size(); ++i) {
            freeTensor(vecRedState[i]);
        }
        for (int i = 0; i < vecBlueState.size(); ++i) {
            freeTensor(vecBlueState[i]);
        }

        vecRedState.clear(); vecBlueState.clear();
        vec_redpos.clear(); vec_blue_pos.clear();
        playSide = RED_SIDE;
        initBoard(hexBoard);
        Tensor2D_setzero(onehotBoard);
        onehotBoard = board_trans_onehot(hexBoard);
        //isFindState(0,hexBoard,1);




        //记录Q值变化，每训练1000次
        //if ((learn_round + 1) % 1000 == 0) printf(".");;
        //system("pause");
        //未赢
        while (!isSideWin(hexBoard, -playSide)) {
            //displayBoard(hexBoard);
            //Tensor2D_display(onehotBoard);
            //system("pause");
            if (playSide == RED_SIDE)//红方下棋
            {
                if (((double)rand() / RAND_MAX) >= EXPLORE)//贪婪策略
                {
                    //displayStateQ(hexBoard, modelRed, RED_SIDE);
                    //选取Q值最大的位置
                    /*vector<int> vecpos = generateSideMovePos(hexBoard);
                    onehotBoard.data[0][vecpos[0]] = 1.0;
                    float maxQ = board_net_Qvalue(onehotBoard, modelRed);
                    onehotBoard.data[0][vecpos[0]] = 0.0;
                    pos = vecpos[0];
                    for (int i = 1; i < vecpos.size(); i++) {
                        onehotBoard.data[0][vecpos[i]] = 1.0;
                        float outQvalue = board_net_Qvalue(onehotBoard, modelRed);
                        //printf("%f,", outQvalue);
                        if (maxQ < outQvalue) {
                            maxQ = outQvalue; pos = vecpos[i];
                        }
                        onehotBoard.data[0][vecpos[i]] = 0;
                    }*/
                    pos = findMaxQPos(hexBoard, onehotBoard, modelRed,RED_SIDE);
                    
                }
                else
                {
                    //printf("$$");
                    //printf("b");
                    vector<int> vecAllMovePos = generateSideMovePos(hexBoard);
                    //printf("(%d)", rand());
                    int randIndex = (rand()) % vecAllMovePos.size();
                    //printf("(%d)", rand());
                    pos = vecAllMovePos[randIndex];
                    //hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                    //pos = uctAll(hexBoard, playSide, 1);//uct生成
                }
                hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                vec_redpos.push_back(pos);
                onehotBoard.data[0][pos] = 1.0;
                Tensor2D temp_state = Tensor2D_copy(onehotBoard);
                vecRedState.push_back(temp_state);
                //freeTensor(temp_state);
            }
            else
            {
                //if (vec_blue_pos.empty() == true && (learn_round) % display_loss_round == 0) 
                {
                    //selfPlayExecQ(modelRed, 0);
                    //displayStateQ(hexBoard, modelBlue,BLUE_SIDE); //system("pause");
                }
                if (((double)rand() / RAND_MAX) >= EXPLORE)
                {
                    /*vector<int> vecpos = generateSideMovePos(hexBoard);
                    onehotBoard.data[0][BOARD_SIZE * BOARD_SIZE + vecpos[0]] = 1.0;
                    float maxQ = board_net_Qvalue(onehotBoard, modelBlue);
                    onehotBoard.data[0][BOARD_SIZE * BOARD_SIZE + vecpos[0]] = 0.0;
                    pos = vecpos[0];
                    for (int i = 1; i < vecpos.size(); i++) {
                        onehotBoard.data[0][BOARD_SIZE * BOARD_SIZE + vecpos[i]] = 1.0;
                        float outQvalue = board_net_Qvalue(onehotBoard, modelBlue);
                        if (maxQ < outQvalue) {
                            maxQ = outQvalue; pos = vecpos[i];
                        }
                        onehotBoard.data[0][BOARD_SIZE * BOARD_SIZE + vecpos[i]] = 0.0;
                    }*/
                    pos = findMaxQPos(hexBoard, onehotBoard, modelBlue,BLUE_SIDE);
                    //hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                }
                else
                {
                   // printf("&&");
                    vector<int> vecAllMovePos = generateSideMovePos(hexBoard);
                    int randIndex = (rand()) % vecAllMovePos.size();
                    pos = vecAllMovePos[randIndex];
                    
                    //pos = uctAll(hexBoard, playSide, 1);//uct生成
                }
                hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                //pos = uctAll(hexBoard, playSide,0.01);
                vec_blue_pos.push_back(pos);
                //pos = uctAll(hexBoard, playSide, 0.01);
                onehotBoard.data[0][BOARD_SIZE * BOARD_SIZE + pos] = 1.0;
                Tensor2D temp_state = Tensor2D_copy(onehotBoard);
                vecBlueState.push_back(temp_state);
                //freeTensor(temp_state);
                
            }
            playSide = -playSide;
            //if (vec_blue_pos.size() == 1 && (learn_round) % display_loss_round == 0) 
            {
//displayBoard(hexBoard); 
            }

        }

        //(- playSide == RED_SIDE) ? printf("red win") : printf("blue win");
        //printf("[red win pro:%f]\n", (float)(sum_epoch_redwin) / (sum_epoch_bluewin + sum_epoch_redwin));
        //modelRed.save_mode("model\\newmodelRed-size-4.dat"); modelBlue.save_mode("model\\newmodelBlue-size-4.dat");
   //printf("********************************\n"); system("pause");
        if (-playSide == RED_SIDE) sum_epoch_redwin++;
        else sum_epoch_bluewin++;
        

        
        /*for (int i = 0; i < vec_redpos.size(); ++i) {
            printf("%d,", vec_redpos[i]);
        }
        
        for (int i = 0; i < vecRedState.size(); i++) {
            Tensor2D_display(vecRedState[i]);
        }
        //system("pause");
        for (int i = 0; i < vec_blue_pos.size(); ++i) {
            printf("%d,", vec_blue_pos[i]);
        }
        for (int i = 0; i < vecBlueState.size(); i++) {
            Tensor2D_display(vecBlueState[i]);
        }*/
        //system("pause");

        //displayBoard(hexBoard); system("pause");
        //printf("\n%d win(%d)\n", -playSide,vec_redpos[0]);
        //selfPlayExecQ(modelRed, 0);
        if (choice == 2) {
            for (int j = 0; j < 1; j++) {
                int iswin = -1;
                if (playSide == BLUE_SIDE)iswin = 1;
                float red_lose = updateQlearning(vecRedState, modelRed, vec_redpos, -iswin, RED_SIDE);
                float blue_lose = updateQlearning(vecBlueState, modelBlue, vec_blue_pos, iswin, BLUE_SIDE);
                //sum_epoch_blue_lose += blue_lose;
                sum_epoch_red_lose += red_lose;
                if ((learn_round) % display_loss_round == 0) {
                    //printf("[blue lose:%f]", men_lose / vecBlueState.size());
                    printf("[red epoch lose:%f]", sum_epoch_red_lose / display_loss_round);
                    // printf("[blue epoch lose:%f]\n", sum_epoch_blue_lose / display_loss_round);
                    printf("[red win pro:%f]\n", (float)sum_epoch_redwin / display_loss_round);
                    //printf("[blue win pro:%f]\n", (float)sum_epoch_bluewin / display_loss_round); 
                    sum_epoch_redwin = 0;
                    sum_epoch_bluewin = 0;
                    sum_epoch_blue_lose = 0;
                    sum_epoch_red_lose = 0;
                };
            }
        }
        /*
        }*/
        //selfPlayExecQ(modelRed, 0);
        //system("pause");
        
        if(choice == 1)
        {
            /**/int forward_num = 1;
            float isRedWin = (-playSide == RED_SIDE ? 1.0 : -1.0);
            float red_reword = (-playSide == RED_SIDE ? 1.0 : 0.0);
            float blue_reword = (-playSide == BLUE_SIDE ? 1.0 : 0.0);
            Tensor2D input, output;
            Tensor2D y_true = Tensor2D_init(1, 1, red_reword);
            float men_lose = 0;
            for (int i = 0; i < vecRedState.size(); i++) {//
                //selfPlayExecQ(modelRed, 0); printf("%d", vec_redpos[0]); system("pause");
                for (int j = 0; j < forward_num; j++) {
                    
                    input = vecRedState[i];
                    output = modelRed.forward(input, true);
                    //printf("[%f]", output.data[0][0]);
                    float lose = modelRed.Linear_loss(output, y_true);
                    if (j == 0)men_lose += lose;
                    //y_true.data[0][0] = 0.1;//((double)rand() / RAND_MAX) * 2 - 1;
                    //printf("[lose:%f]", lose);
                    modelRed.backward(output, y_true, 0.01);

                    //input = vecRedState[i];
                    //output = modelRed.forward(input, true);
                    //printf("[\%f,%f]", output.data[0][0], y_true.data[0][0]);
                    
                }
//selfPlayExecQ(modelRed, 0); system("pause");
            }
            sum_epoch_red_lose += men_lose / vecRedState.size();
            if ((learn_round) % display_loss_round == 0) {
                printf("[red lose:%f]", men_lose / vecRedState.size());
                printf("[red epoch lose:%f]", sum_epoch_red_lose / display_loss_round);
                printf("[red win pro:%f]", (float)sum_epoch_redwin / display_loss_round);
                sum_epoch_red_lose = 0; sum_epoch_redwin = 0;
            };
            freeTensor(y_true);

            Tensor2D y_true2 = Tensor2D_init(1, 1, blue_reword);
            men_lose = 0;
            for (int i = 0; i < vecBlueState.size(); i++) {
                for (int j = 0; j < forward_num; j++) {
                    input = vecBlueState[i];
                    output = modelBlue.forward(input, true);
                    float lose = modelBlue.Linear_loss(output, y_true2);
                    if (j == 0)men_lose += lose;

                    //printf("[lose:%f]", lose);
                    //y_true2.data[0][0] = 0.1; //((double)rand() / RAND_MAX) * 2 - 1;
                    modelBlue.backward(output, y_true2, 0.01);
                }

            }
            sum_epoch_blue_lose += men_lose / vecBlueState.size();
            if ((learn_round) % display_loss_round == 0) {
                printf("[blue lose:%f]", men_lose / vecBlueState.size());
                printf("[blue epoch lose:%f]", sum_epoch_blue_lose / display_loss_round);
                printf("[blue win pro:%f]\n", (float)sum_epoch_bluewin / display_loss_round);
                sum_epoch_blue_lose = 0; sum_epoch_bluewin = 0;
            };
            freeTensor(y_true2);/**/
        }
    }
}

void displayStateQ(int** hexBoard, Net model,int side) {
    vector<int> vecpos = generateSideMovePos(hexBoard);
    Tensor2D input,output;
    for (int i = 0; i < vecpos.size(); i++) {
        hexBoard[vecpos[i] / BOARD_SIZE][vecpos[i] % BOARD_SIZE] = side;
        input = board_trans_onehot(hexBoard);
        output = model.forward(input, true);
        printf("(pos:%d,%d,value:%f)\n", vecpos[i] / BOARD_SIZE, vecpos[i] % BOARD_SIZE, output.data[0][0]);
        hexBoard[vecpos[i] / BOARD_SIZE][vecpos[i] % BOARD_SIZE] = EMPTY_POS;
    }
}
int findMaxQPos(int** hexBoard, Tensor2D onehot, Net model,int side) {
    int setpos = side == RED_SIDE ? 0 : BOARD_SIZE * BOARD_SIZE;

    //选取Q值最大的位置
    vector<int> vecpos = generateSideMovePos(hexBoard);
    onehot.data[0][setpos + vecpos[0]] = 1.0;
    float maxQ = board_net_Qvalue(onehot, model);
    onehot.data[0][setpos + vecpos[0]] = 0.0;
    int pos = vecpos[0];
    //if (maxQ < -1.0)return pos;

    for (int i = 1; i < vecpos.size(); i++) {
        onehot.data[0][setpos + vecpos[i]] = 1.0;
        float outQvalue = board_net_Qvalue(onehot, model);
        //printf("%f,", outQvalue);
        //if (outQvalue < -1.0) 
        {
            //onehot.data[0][setpos + vecpos[i]] = 0.0;
            //return vecpos[i];
        }
        if (maxQ < outQvalue) {
            maxQ = outQvalue; pos = vecpos[i];
        }
        
        onehot.data[0][setpos + vecpos[i]] = 0.0;
    }

    if (0)//(maxQ < -0.8) //
    {
        vecpos = generateSideMovePos(hexBoard);
        onehot.data[0][setpos + vecpos[0]] = 1.0;
        float maxQ = board_net_Qvalue(onehot, model);
        onehot.data[0][setpos + vecpos[0]] = 0.0;
        int pos = vecpos[0];
        if (maxQ < -1.0)return pos;

        for (int i = 1; i < vecpos.size(); i++) {
            onehot.data[0][setpos + vecpos[i]] = 1.0;
            float outQvalue = board_net_Qvalue(onehot, model);
            //printf("%f,", outQvalue);
            if (outQvalue < -1.0)
            {
                onehot.data[0][setpos + vecpos[i]] = 0.0;
                return vecpos[i];
            }
            if (maxQ < outQvalue) {
                maxQ = outQvalue; pos = vecpos[i];
            }
            onehot.data[0][setpos + vecpos[i]] = 0;
        }
    }

    /*if (isEqual(maxQ, -1.0)) {
        
        int flag = 0;
        for (int i = 0; i < vecpos.size(); i++) {
            onehot.data[0][vecpos[i]] = 1.0;
            float outQvalue = board_net_Qvalue(onehot, model);
            //printf("%f,", outQvalue);
            if (isEqual(outQvalue, -1.0) == false && outQvalue < -1.0) {
                onehot.data[0][vecpos[i]] = 0;
                flag = i; pos = vecpos[i]; break;
            }
            onehot.data[0][vecpos[i]] = 0;
        }

        for(int i=flag+1; i < vecpos.size(); i++) {
            onehot.data[0][vecpos[i]] = 1.0;
            float outQvalue = board_net_Qvalue(onehot, model);
            //printf("%f,", outQvalue);
            if (isEqual(outQvalue, -1.0) == false && maxQ < outQvalue) {
                maxQ = outQvalue; pos = vecpos[i];
            }
            onehot.data[0][vecpos[i]] = 0;
        }
    }*/
    return pos;
}

vector<train_data> colletData(Net modelRed, Net modelBlue,int round) {
    srand((unsigned)time(NULL));
    int** hexBoard = (int**)malloc(sizeof(int*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        hexBoard[i] = (int*)malloc(sizeof(int) * BOARD_SIZE);
    }
    initBoard(hexBoard);
    int playSide = RED_SIDE;
    int learn_round = round;
    int train_time = 1 * 1 * 30;
    int train_epoch = 0;
    int pos;
    vector<Tensor2D> vecRedState, vecBlueState;

    Tensor2D onehotBoard = board_trans_onehot(hexBoard);

    train_data trainData;
    vector<train_data> vec_trainData;

    while (learn_round--)
    {
        learn_round--;
        vecRedState.clear(); vecBlueState.clear();
        playSide = RED_SIDE;
        initBoard(hexBoard);
        Tensor2D_setzero(onehotBoard);
        //isFindState(0,hexBoard,1);


        //未赢
        while (!isSideWin(hexBoard, -playSide)) {
            if (playSide == RED_SIDE)//红方下棋
            {
                if (((double)rand() / RAND_MAX) >= EXPLORE)//贪婪策略
                {
                    //选取Q值最大的位置
                    vector<int> vecpos = generateSideMovePos(hexBoard);
                    onehotBoard.data[0][vecpos[0]] = 1.0;
                    float maxQ = board_net_Qvalue(onehotBoard, modelRed);
                    onehotBoard.data[0][vecpos[0]] = 0.0;
                    pos = vecpos[0];
                    for (int i = 1; i < vecpos.size(); i++) {
                        onehotBoard.data[0][vecpos[i]] = 1.0;
                        float outQvalue = board_net_Qvalue(onehotBoard, modelRed);
                        //printf("%f,", outQvalue);
                        if (maxQ < outQvalue) {
                            maxQ = outQvalue; pos = vecpos[i];
                        }
                        onehotBoard.data[0][vecpos[i]] = 0;
                    }
                    hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                }
                else
                {
                    //printf("b");
                    vector<int> vecAllMovePos = generateSideMovePos(hexBoard);
                    //printf("(%d)", rand());
                    int randIndex = (rand()) % vecAllMovePos.size();
                    //printf("(%d)", rand());
                    pos = vecAllMovePos[randIndex];
                    hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                    //pos = uctAll(hexBoard, playSide, 1);//uct生成
                }
        
                onehotBoard.data[0][pos] = 1.0;
                Tensor2D temp_state = Tensor2D_copy(onehotBoard);
                vecRedState.push_back(temp_state);

            }
            else
            {
                if (((double)rand() / RAND_MAX) >= EXPLORE)
                {
                    vector<int> vecpos = generateSideMovePos(hexBoard);
                    onehotBoard.data[0][BOARD_SIZE * BOARD_SIZE + vecpos[0]] = 1.0;
                    float maxQ = board_net_Qvalue(onehotBoard, modelBlue);
                    onehotBoard.data[0][BOARD_SIZE * BOARD_SIZE + vecpos[0]] = 0.0;
                    pos = vecpos[0];
                    for (int i = 1; i < vecpos.size(); i++) {
                        onehotBoard.data[0][BOARD_SIZE * BOARD_SIZE + vecpos[i]] = 1.0;
                        float outQvalue = board_net_Qvalue(onehotBoard, modelBlue);
                        if (maxQ < outQvalue) {
                            maxQ = outQvalue; pos = vecpos[i];
                        }
                        onehotBoard.data[0][BOARD_SIZE * BOARD_SIZE + vecpos[i]] = 0.0;
                    }
                    hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                }
                else
                {
                    vector<int> vecAllMovePos = generateSideMovePos(hexBoard);
                    int randIndex = (rand()) % vecAllMovePos.size();
                    pos = vecAllMovePos[randIndex];
                    hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                    //pos = uctAll(hexBoard, playSide, 1);//uct生成
                }
                
                onehotBoard.data[0][BOARD_SIZE * BOARD_SIZE + pos] = 1.0;
                Tensor2D temp_state = Tensor2D_copy(onehotBoard);
                vecBlueState.push_back(temp_state);

            }
            playSide = -playSide;

        }


        
        float isRedWin = (-playSide == RED_SIDE ? 1.0 : -1.0);

        for (int i = 0; i < vecRedState.size(); i++) {
            trainData.side = RED_SIDE;
            trainData.state = vecRedState[i];
            trainData.true_value = isRedWin;
            vec_trainData.push_back(trainData);
        
        }
           
        for (int i = 0; i < vecBlueState.size(); i++) {
            trainData.side = BLUE_SIDE;
            trainData.state = vecBlueState[i];
            trainData.true_value = -isRedWin;
            vec_trainData.push_back(trainData);
        }

    }
    return vec_trainData;
}

float trainNet(Net modelRed, Net modelBlue, vector<train_data> vec_trainData) {
    float men_lose = 0;
    Tensor2D input, output;
    Tensor2D y_true = Tensor2D_init(1, 1, 0);
    Tensor2D_display(vec_trainData[0].state);
    for (int i = 0; i < vec_trainData.size(); ++i) {
        if (vec_trainData[i].side == RED_SIDE) {
            input = vec_trainData[i].state;
            output = modelRed.forward(input, true);
            y_true.data[0][0] = vec_trainData[i].true_value;
            float lose = modelRed.Linear_loss(output, y_true);
            men_lose += lose;
            modelRed.backward(output, y_true, 0.00001);
        }
        else {
            input = vec_trainData[i].state;
            output = modelBlue.forward(input, true);
            y_true.data[0][0] = vec_trainData[i].true_value;
            float lose = modelBlue.Linear_loss(output, y_true);
            men_lose += lose;
            modelBlue.backward(output, y_true, 0.00001);
        }
        freeTensor(vec_trainData[i].state);
    }
    men_lose /= vec_trainData.size();
    freeTensor(y_true);
    return men_lose;
}


int isEqual(float a, float b) {
    return fabs(a - b) < 1e-6;
}

float findMaxStateQ(Net model,Tensor2D tensor,int side) {
    int pos = 0;
    float maxQ = -100000;
    if (side == BLUE_SIDE)pos = BOARD_SIZE * BOARD_SIZE;

    Tensor2D tempTensor = Tensor2D_copy(tensor);

    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i) {
        if (isEqual(0.0, tempTensor.data[0][pos + i])) {
            tempTensor.data[0][pos + i] = 1.0;
            Tensor2D output = model.forward(tempTensor, true);
            //printf("%f,", output.data[0][0]);
            if (output.data[0][0] > maxQ)maxQ = output.data[0][0];
            tempTensor.data[0][pos + i] = 0.0;
        }

    }
    if (isEqual(maxQ,-100000))printf("findMaxStateQ error");
    //printf("^%f#", maxQ);
    freeTensor(tempTensor);

    if (maxQ > 1.0)return 1.0;
    if (maxQ < -1.0)return -1.0;
    return maxQ;
}

float updateQlearning(vector<Tensor2D> vecState, Net model, vector<int> vecPos,int isWin,int side) {
    float men_lose = 0;
    int forward_num = 1;
    Tensor2D input, output;
    Tensor2D y_true = Tensor2D_init(1, 1, (float)isWin);
    int setPos = (side == BLUE_SIDE ? BOARD_SIZE * BOARD_SIZE : 0);

    input = vecState[vecState.size() - 1];
    output = model.forward(input, true);
    //printf("%f,", output.data[0][0]);
    y_true.data[0][0] = output.data[0][0] + ALPHA * (isWin - output.data[0][0]);
    //printf("(%f)", y_true.data[0][0]);
    float lose = model.Linear_loss(output, y_true);
    men_lose += lose;
    model.backward(output, y_true, 0.00001);





    for (int i = vecState.size()-2; i >=0; i--) {
        //for (int j = 0; j < forward_num; j++) {
            
            
            //float outputValue = output.data[0][0];
            //Tensor2D tempout = Tensor2D_init(1, 1, outputValue);
        //Tensor2D_display(vecState[i + 1]);
            input = vecState[i+1];
            input.data[0][setPos + vecPos[i+1]] = 0.0;
            float maxQ = findMaxStateQ(model, input, side);
            input.data[0][setPos + vecPos[i+1]] = 1.0;
          
           // printf("[maxQ:%d,%f]",i, maxQ); 
        //Tensor2D_display(vecState[i + 1]);
            input = vecState[i];
            output = model.forward(input, true);
            y_true.data[0][0] = output.data[0][0] + ALPHA * (GAMMA * maxQ - output.data[0][0]);
            //printf("[maxQ:%d,%f]", i, maxQ);
            //printf("[---:%f,%f]", output.data[0][0], y_true.data[0][0]); system("pause");
            float lose = model.Linear_loss(output, y_true);
            men_lose += lose;
            model.backward(output, y_true, 0.00001);

            //printf("[lose:%f]", lose);
            //model.backward(tempout, y_true, 0.00001);
            //freeTensor(tempout);
        }
     
    freeTensor(y_true);
    return men_lose / vecState.size();
}

Tensor2D board_trans_onehot(int** hexBoard) {
    Tensor2D onehot = Tensor2D_init(1, BOARD_SIZE * BOARD_SIZE * 2, 0.0);
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i) {
        if (hexBoard[i / BOARD_SIZE][i % BOARD_SIZE] == RED_SIDE) {
            onehot.data[0][i] = 1.0;
        }

        if (hexBoard[i / BOARD_SIZE][i % BOARD_SIZE] == BLUE_SIDE) {
            onehot.data[0][i + BOARD_SIZE * BOARD_SIZE] = 1.0;
        }
    }
    return onehot;
}

float board_net_Qvalue(int** hexBoard, Net net) {
    Tensor2D onehot = board_trans_onehot(hexBoard);
    Tensor2D output = net.forward(onehot, true);
    return output.data[0][0];
}

float board_net_Qvalue(Tensor2D onehot, Net net) {
    Tensor2D output = net.forward(onehot, true);
    return output.data[0][0];
}

void selfPlayExecQ(Net net,int num) {
    //net.display(true);
    int** hexBoard = (int**)malloc(sizeof(int*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        hexBoard[i] = (int*)malloc(sizeof(int) * BOARD_SIZE);
    }
    initBoard(hexBoard);
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            hexBoard[i][j] = RED_SIDE;
            printf("%f,", board_net_Qvalue(hexBoard, net));
            hexBoard[i][j] = EMPTY_POS;
        }
        printf("\n");
    }
  
    int round = num;
    int redWin = 0;
    int blueWin = 0;
    int playSide = RED_SIDE;
    int playStep;
    Tensor2D onehotBoard = board_trans_onehot(hexBoard);
    int pos;
    while (round--)
    {
        playSide = RED_SIDE;
        initBoard(hexBoard);
        playStep = 0;
        Tensor2D_setzero(onehotBoard);

        while (!isSideWin(hexBoard, -playSide))
        {
            
            if (playSide == RED_SIDE)
            {
                vector<int> vecpos = generateSideMovePos(hexBoard);
                onehotBoard.data[0][vecpos[0]] = 1.0;
                float maxQ = board_net_Qvalue(onehotBoard, net);
                onehotBoard.data[0][vecpos[0]] = 0.0;
                pos = vecpos[0];
                for (int i = 1; i < vecpos.size(); i++) {
                    onehotBoard.data[0][vecpos[i]] = 1.0;
                    float outQvalue = board_net_Qvalue(onehotBoard, net);
                    if (maxQ < outQvalue) {
                        maxQ = outQvalue; pos = vecpos[i];
                    }
                    onehotBoard.data[0][vecpos[i]] = 0.0;
                }
                hexBoard[pos / BOARD_SIZE][pos % BOARD_SIZE] = playSide;
                onehotBoard.data[0][pos] = 1.0;
            }
            else
            {
                pos = uctAll(hexBoard, playSide, 1);
                onehotBoard.data[0][pos+BOARD_SIZE*BOARD_SIZE] = 1.0;
            }
            playSide = -playSide;
            playStep++;
            //displayBoard(hexBoard); system("pause");
        }
        ( - playSide) == RED_SIDE ? redWin++ : blueWin++;
        printf("red : blue = [%d,%d]\n", redWin, blueWin);
    }
}


