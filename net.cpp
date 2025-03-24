#include"net.h"

void Net::init() {
    netDepth = 3;
    net = (FC*)malloc(sizeof(FC) * netDepth);
    actfun.resize(netDepth, "no");
    output = (Tensor2D*)malloc(sizeof(Tensor2D) * (netDepth + 1));
    grid = (Tensor2D*)malloc(sizeof(Tensor2D) * (netDepth + 1));
    have_grid = (bool*)malloc(sizeof(bool));
    *have_grid = false;
    have_output = (bool*)malloc(sizeof(bool));
    *have_output = false;

    int inputsize = BOARD_SIZE * BOARD_SIZE * 2;
    net[0] = Linear_init(inputsize, inputsize); actfun[0] = "relu";
    net[1] = Linear_init(inputsize, inputsize); actfun[1] = "relu";
    net[2] = Linear_init(inputsize, 1); actfun[2] = "sigmoid";

   // net[3] = Linear_init(inputsize, inputsize); actfun[3] = "relu";
    //net[4] = Linear_init(inputsize, 1); actfun[4] = "no";
    //net[5] = Linear_init(inputsize, 1); actfun[5] = "no";

}

bool Net::isSame(Net model1, Net model2) {
    bool ret = true;
    for (int i = 0; i < model1.netDepth; ++i) {
        for (int m = 0; m < model1.net[i].in_features; m++) {
            for (int n = 0; n < model1.net[i].out_features; n++) {
                if (model1.net[i].W.data[m][n] != model2.net[i].W.data[m][n]) {
                    printf("error net[%d] w [%d,%d][%lf ,%lf] [%f]\n", i, m, n, 
                        model1.net[i].W.data[m][n], model2.net[i].W.data[m][n], model1.net[i].W.data[m][n]-model2.net[i].W.data[m][n]); ret = false;
                }
               
            }
        }

        for (int n = 0; n < model1.net[i].out_features; n++) {
            if (model1.net[i].B.data[0][n] != model2.net[i].B.data[0][n]) {
                printf("error net[%d] b [%d,%d][%f ,%f] \n", i, 0, n,
                    model1.net[i].B.data[0][n], model2.net[i].B.data[0][n]); ret = false;
            }

        }

        if (model1.actfun[i] != model2.actfun[i]) {
            printf("error net[%d] actfun [%s,%s]\n", i,
                model1.actfun[i], model2.actfun[i]); ret = false;
        }
        
    }
    return ret;
}

void Net::display(bool printWB) {
    printf("\nNet info:\nnet depth:%d.\n", netDepth);
    for (int i = 0; i < netDepth; ++i) {
        printf("net[%d]: in_features:%d , out_features:%d\n", i, net[i].in_features, net[i].out_features);
        if (printWB == true) {
            printf("weigth:\n");
            Tensor2D_display(net[i].W);
            printf("bias:\n");
            Tensor2D_display(net[i].B);
        }
        
        //printf("\n");
        printf("actfun:%s\n\n", actfun[i].c_str());
    }
}

void Net::save_mode() {
    printf("\nsave model start:");
    
    FILE* modelPtr;
    modelPtr = fopen("model.dat", "w+");
    //打开文件
    if (modelPtr == NULL) {
        perror("Error opening file(save model)");
        exit(0);
    }
    //保存netDepth
    fprintf(modelPtr, "%d ", netDepth);
    //保存网络w，b
    for (int i=0;i< netDepth;++i)
    {
        fprintf(modelPtr, "%d ", net[i].in_features);
        fprintf(modelPtr, "%d ", net[i].out_features);
        for (int m = 0; m < net[i].in_features; m++) {
            for (int n = 0; n < net[i].out_features; n++) {
                fprintf(modelPtr, "%f ", net[i].W.data[m][n]);
            }
        }

        for (int n = 0; n < net[i].out_features; n++) {
            fprintf(modelPtr, "%f ", net[i].B.data[0][n]);
        }
        fprintf(modelPtr, "%s ", actfun[i].c_str());
    }
    //关闭文件
    fclose(modelPtr);
    printf("save model end.\n");
}

void Net::save_mode(std::string path) {
    printf("\nsave model start:");

    FILE* modelPtr;
    modelPtr = fopen(path.c_str(), "w+");
    //打开文件
    if (modelPtr == NULL) {
        perror("Error opening file(save model)");
        exit(0);
    }
    //保存netDepth
    fprintf(modelPtr, "%d ", netDepth);
    //保存网络w，b
    for (int i = 0; i < netDepth; ++i)
    {
        fprintf(modelPtr, "%d ", net[i].in_features);
        fprintf(modelPtr, "%d ", net[i].out_features);
        for (int m = 0; m < net[i].in_features; m++) {
            for (int n = 0; n < net[i].out_features; n++) {
                fprintf(modelPtr, "%f ", net[i].W.data[m][n]);
            }
        }

        for (int n = 0; n < net[i].out_features; n++) {
            fprintf(modelPtr, "%f ", net[i].B.data[0][n]);
        }
        //fputs(actfun[i].c_str(), modelPtr);
        fprintf(modelPtr, "%s ", actfun[i].c_str());
    }
    //关闭文件
    fclose(modelPtr);
    printf("save model end.\n");
}

void Net::load_mode() {
    printf("\nload model start:");

    FILE* modelPtr;
    modelPtr = fopen("model.dat", "r");
    //打开文件
    if (modelPtr == NULL) {
        perror("Error opening file(load model)");
        exit(0);
    }
    //保存netDepth
    fscanf(modelPtr, "%d ", &netDepth);
    net = (FC*)malloc(sizeof(FC) * netDepth);
    actfun.resize(netDepth, "no");
    output = (Tensor2D*)malloc(sizeof(Tensor2D) * (netDepth + 1));
    grid = (Tensor2D*)malloc(sizeof(Tensor2D) * (netDepth + 1));
    have_grid = (bool*)malloc(sizeof(bool));
    *have_grid = false;
    have_output = (bool*)malloc(sizeof(bool));
    *have_output = false;

    //保存网络w，b
    for (int i = 0; i < netDepth; ++i)
    {
        fscanf(modelPtr, "%d ", &net[i].in_features);
        fscanf(modelPtr, "%d ", &net[i].out_features);
        net[i] = Linear_init(net[i].in_features, net[i].out_features);

        for (int m = 0; m < net[i].in_features; m++) {
            for (int n = 0; n < net[i].out_features; n++) {
                fscanf(modelPtr, "%f ", &net[i].W.data[m][n]);
            }
        }

        for (int n = 0; n < net[i].out_features; n++) {
            fscanf(modelPtr, "%f ", &net[i].B.data[0][n]);
        }
        char* cString = (char*)malloc(sizeof(char) * 15);
        fscanf(modelPtr, "%s ", cString);
        actfun[i] = cString;
    }
    //关闭文件
    fclose(modelPtr);
    printf("load model end.\n");
}

void Net::load_mode(std::string path) {
    printf("\nload model start:");

    FILE* modelPtr;
    modelPtr = fopen(path.c_str(), "r");
    //打开文件
    if (modelPtr == NULL) {
        perror("Error opening file(load model)");
        exit(0);
    }
    //保存netDepth
    fscanf(modelPtr, "%d ", &netDepth);
    net = (FC*)malloc(sizeof(FC) * netDepth);
    actfun.resize(netDepth, "no");
    output = (Tensor2D*)malloc(sizeof(Tensor2D) * (netDepth + 1));
    grid = (Tensor2D*)malloc(sizeof(Tensor2D) * (netDepth + 1));
    have_grid = (bool*)malloc(sizeof(bool));
    *have_grid = false;
    have_output = (bool*)malloc(sizeof(bool));
    *have_output = false;

    //保存网络w，b
    for (int i = 0; i < netDepth; ++i)
    {
        fscanf(modelPtr, "%d ", &net[i].in_features);
        fscanf(modelPtr, "%d ", &net[i].out_features);
        net[i] = Linear_init(net[i].in_features, net[i].out_features);

        for (int m = 0; m < net[i].in_features; m++) {
            for (int n = 0; n < net[i].out_features; n++) {
                fscanf(modelPtr, "%f ", &net[i].W.data[m][n]);
            }
        }

        for (int n = 0; n < net[i].out_features; n++) {
            fscanf(modelPtr, "%f ", &net[i].B.data[0][n]);
        }
        char* cString = (char*)malloc(sizeof(char)*15);
        fscanf(modelPtr, "%s ", cString);
        actfun[i] = cString;
    }
    //关闭文件
    fclose(modelPtr);
    printf("load model end.\n");
}

void Net::freeOutput() {
    for (int i = 0; i < netDepth + 1; ++i) {
        freeTensor(output[i]);
    }
    //for (int i = 0; i < netDepth + 1; ++i) {
        //freeTensor(grid[i]);
    //}
}

void Net::freeGrid() {
    for (int i = 0; i < netDepth + 1; ++i) {
        freeTensor(grid[i]);
    }
}

Tensor2D Net::forward(Tensor2D input, bool bias) {
    if (*have_output == true) {
        freeOutput();
    }
    else {
        *have_output = true;
    }
    output[0] = Tensor2D_copy(input);
    for (int i = 1; i < netDepth + 1; ++i) {
        output[i] = Linear_forward(output[i - 1], net[i - 1], bias);
        if (actfun[i - 1] == "sigmoid") {
            Linear_sigmoid(output[i]);
        }
        else if (actfun[i - 1] == "relu") {
            Linear_relu(output[i]);
        }
        else if(actfun[i - 1] == "tanh"){
            Linear_tanh(output[i]);
        }
        else {
            ;
        }
    }
    return output[netDepth];
}

void Net::backward(Tensor2D y_out, Tensor2D y_true, float learning_rate) {
    if (*have_grid == true) {
        freeGrid();
    }
    else {
        *have_grid = true;
    }
    grid[netDepth] = Linear_loseBack(output[netDepth], y_true);
    if (netDepth - 1 >= 0 && actfun[netDepth - 1] == "sigmoid") {
        Linear_sigmoid_back(grid[netDepth], output[netDepth]);
    }
    else if (netDepth - 1 >= 0 && actfun[netDepth - 1] == "relu") {
        Linear_relu_back(grid[netDepth], output[netDepth]);
    }
    else if (netDepth - 1 >= 0 && actfun[netDepth - 1] == "tanh") {
        Linear_tanh_back(grid[netDepth], output[netDepth]);
    }
    else {
        ;
    }

    //Tensor2D_display(grid[1]);

    //计算梯度
    for (int k = netDepth; k >= 1; k--) {
        grid[k - 1] = Linear_backward(grid[k], net[k - 1]);

        if (k - 2 >= 0 && actfun[k - 2] == "sigmoid") {
            Linear_sigmoid_back(grid[k - 1], output[k - 1]);
        }
        else if (k - 2 >= 0 && actfun[k - 2] == "relu") {
            Linear_relu_back(grid[k - 1], output[k - 1]);
        }
        else if (k - 2 >= 0 && actfun[k - 2] == "tanh") {
            Linear_tanh_back(grid[k - 1], output[k - 1]);
        }
        else {
            ;
        }
    }

    //更新梯度
    for (int k = 0; k < netDepth; k++) {
        Linear_update_grid(net[k], grid[k + 1], output[k], learning_rate);
    }
}