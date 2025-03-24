#pragma once
#include"base.h"
#include"linear.h"

class Net :public Linear {
    //Net();
public:
    int netDepth;
    FC* net;
    std::vector<std::string> actfun;
    //std::string *actfun;
    Tensor2D* output;
    Tensor2D* grid;
    bool* have_grid;
    bool* have_output;

    void init();

    void save_mode();
    void save_mode(std::string path);
    void load_mode();
    void load_mode(std::string path);
    void display(bool printWB);

    bool isSame(Net net1, Net net2);

    Tensor2D forward(Tensor2D input, bool bias = true);
    void freeOutput();
    void freeGrid();
    void backward(Tensor2D y_out, Tensor2D y_true, float learning_rate = 0.01);
};