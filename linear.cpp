#include"linear.h"

std::mt19937& get_generator() {
    thread_local std::mt19937 gen(std::random_device{}());
    return gen;
}

void freeTensor(Tensor2D tensor) {
    //Tensor2D_display(tensor);
    for (int i = 0; i < tensor.h; ++i) {
        //printf("(%d)", i);
        free(tensor.data[i]);
    }
    free(tensor.data);
    //printf("end");
}

Tensor2D Tensor2D_init(int h, int w) {
    Tensor2D tensor;
    tensor.h = h;
    tensor.w = w;
    tensor.data = (float**)malloc(sizeof(float*) * h);
    std::mt19937& gen = get_generator();

    // 生成标准正态分布的随机数，mean为均值，stddev为标准差  
    std::normal_distribution<> d(0.0, 1.0); // 标准正态分布，均值为0，标准差为1  

    for (int i = 0; i < h; ++i) {
        tensor.data[i] = (float*)malloc(sizeof(float) * w);
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            tensor.data[i][j] = d(gen);//(float)(rand()%100000) / 100000;
        }
    }
    return tensor;
}
void Tensor2D_init(int h, int w, Tensor2D tensor) {
    tensor.h = h;
    tensor.w = w;
    tensor.data = (float**)malloc(sizeof(float*) * h);
    std::mt19937& gen = get_generator();

    // 生成标准正态分布的随机数，mean为均值，stddev为标准差  
    std::normal_distribution<> d(0.0, 1.0); // 标准正态分布，均值为0，标准差为1  

    for (int i = 0; i < h; ++i) {
        tensor.data[i] = (float*)malloc(sizeof(float) * w);
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            tensor.data[i][j] = d(gen);//(float)(rand()%100000) / 100000;
        }
    }
}

Tensor2D Tensor2D_init(int h, int w, float value) {
    Tensor2D tensor;
    tensor.h = h;
    tensor.w = w;
    tensor.data = (float**)malloc(sizeof(float*) * h);
    for (int i = 0; i < h; ++i) {
        tensor.data[i] = (float*)malloc(sizeof(float) * w);
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            tensor.data[i][j] = value;//(float)(rand()%100000) / 100000;
        }
    }
    return tensor;
}

void Tensor2D_setzero(Tensor2D tensor) {
    for (int i = 0; i < tensor.h; ++i) {
        for (int j = 0; j < tensor.w; ++j) {
            tensor.data[i][j] = 0;
        }
    }
}

void Tensor2D_display(Tensor2D tensor) {
    int m = tensor.h;
    int n = tensor.w;
    printf("\Tensor size:[%d,%d]\n", m, n);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%f,", tensor.data[i][j]);
        }
        printf("\n");
    }


}

Tensor2D Tensor2D_copy(Tensor2D tensor) {
    Tensor2D temp = Tensor2D_init(tensor.h, tensor.w);
    for (int i = 0; i < tensor.h; ++i) {
        for (int j = 0; j < tensor.w; ++j) {
            temp.data[i][j] = tensor.data[i][j];
        }
    }
    return temp;
}

void Tensor2D_init_copy(Tensor2D tensor, Tensor2D tensorinit) {
    int h = tensorinit.h;
    int w = tensorinit.w;
    tensor.h = h;
    tensor.w = w;
    tensor.data = (float**)malloc(sizeof(float*) * h);

    for (int i = 0; i < h; ++i) {
        tensor.data[i] = (float*)malloc(sizeof(float) * w);
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            tensor.data[i][j] = tensorinit.data[i][j];//(float)(rand()%100000) / 100000;
        }
    }
}

void Tensor2D_copy(Tensor2D tensor1,Tensor2D tensor2) {
    tensor1.h = tensor2.h;
    tensor1.w = tensor2.w;
    for (int i = 0; i < tensor1.h; ++i) {
        for (int j = 0; j < tensor1.w; ++j) {
            tensor1.data[i][j] = tensor2.data[i][j];
        }
    }
}

//记得改里面内容
FC Linear::Linear_init(int in_features, int out_features) {
    FC fc_init;
    fc_init.in_features = in_features;
    fc_init.out_features = out_features;
    fc_init.W = Tensor2D_init(in_features, out_features);
    fc_init.B = Tensor2D_init(1, out_features,0.0);

    return fc_init;
}

FC Linear::Linear_init(int in_features, int out_features, float value) {
    FC fc_init;
    fc_init.in_features = in_features;
    fc_init.out_features = out_features;
    fc_init.W = Tensor2D_init(in_features, out_features, value);
    fc_init.B = Tensor2D_init(1, out_features, value);//printf("{%f}", fc_init.B.data[0][0]);
    return fc_init;
}

void Linear::Linear_display(FC fc, bool bias) {
    int m = fc.in_features;
    int n = fc.out_features;
    printf("\nLinear size:[%d,%d]\nweight tensor:\n", m, n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%f ", fc.W.data[i][j]);
        }
        printf("\n");
    }

    if (bias == true) {
        printf("bias:\n");
        for (int j = 0; j < n; ++j) {
            printf("%f ", fc.B.data[0][j]);
        }
        printf("\n");
    }
}

Tensor2D Linear::Linear_forward(Tensor2D tensor_in, FC fc_w, bool bias) {
    Tensor2D tensor = Tensor2D_init(tensor_in.h, fc_w.out_features);
    //Linear_display(fc_out);
    //矩阵乘法
    if (tensor_in.w != fc_w.in_features) {
        printf("\nforward size error!\n");
    }
    for (int i = 0; i < tensor.h; ++i) {
        for (int j = 0; j < tensor.w; ++j) {
            float sum = 0;
            //相同边
            for (int m = 0; m < tensor_in.w; ++m) {
                //printf("(%f,%f)", fc_in.w[i][m], fc_w.w[m][j]);
                sum += tensor_in.data[i][m] * fc_w.W.data[m][j];
            }
            //printf("**%f",sum);
            if (bias == true)tensor.data[i][j] = sum + fc_w.B.data[0][j];
            else tensor.data[i][j] = sum;
        }
    }

    return tensor;
}


FC Linear::Linear_copy(FC fc) {
    FC fc_init = Linear_init(fc.in_features, fc.out_features);
    fc_init.W = Tensor2D_copy(fc.W);
    fc_init.B = Tensor2D_copy(fc.B);
    return fc_init;
}

Tensor2D Linear::Linear_backward(Tensor2D pre_det, FC fc_w) {
    //Tensor2D cur_det = Tensor2D_init(1, fc_w.in_features,0.0);
    Tensor2D ret_det = Tensor2D_init(1, fc_w.in_features, 0.0);

    for (int i = 0; i < fc_w.in_features; i++) {
        for (int k = 0; k < pre_det.w; ++k) {
            //cur_det.data[0][i] += fc_w.W.data[i][k] * pre_det.data[0][k];
            ret_det.data[0][i] += fc_w.W.data[i][k] * pre_det.data[0][k];
        }
        //cur_det.data[0][i] *= cur_in.data[0][i];
    }


    return ret_det;
}

void Linear::Linear_update_grid(FC fc_w, Tensor2D grid, Tensor2D input, float learning_rate) {
    for (int i = 0; i < fc_w.W.h; ++i) {
        for (int j = 0; j < fc_w.W.w; ++j) {
            fc_w.W.data[i][j] -= learning_rate * (input.data[0][i] * grid.data[0][j]);
        }
    }
    //更新b
    for (int j = 0; j < fc_w.W.w; ++j) {
        fc_w.B.data[0][j] -= learning_rate * (grid.data[0][j]);
    }

}


float Linear::Linear_loss(Tensor2D y_out, Tensor2D y_true) {
    float loss = 0;
    for (int i = 0; i < y_out.w; ++i) {
        loss += pow(y_out.data[0][i] - y_true.data[0][i], 2);
    }
    loss /= y_true.w;
    return loss;

}

Tensor2D Linear::Linear_loseBack(Tensor2D y_out, Tensor2D y_true) {
    Tensor2D tensor = Tensor2D_init(1, y_out.w, 0.0);

    for (int i = 0; i < y_out.w; ++i) {
        tensor.data[0][i] += 2 * (y_out.data[0][i] - y_true.data[0][i]) / y_out.w;
    }

    return tensor;
}

float Linear::Linear_sigmoid(float a) {
    return 1 / (1 + exp(-a));
}

void Linear::Linear_sigmoid(Tensor2D tensor) {
    for (int i = 0; i < tensor.h; ++i) {
        for (int j = 0; j < tensor.w; ++j) {
            tensor.data[i][j] = 1 / (1 + exp(-tensor.data[i][j]));
        }
    }
}

float Linear::Linear_sigmoid_back(float a) {
    return a * (1 - a);
}

void Linear::Linear_sigmoid_back(Tensor2D grid, Tensor2D tensor_out) {
    for (int i = 0; i < grid.h; ++i) {
        for (int j = 0; j < grid.w; ++j) {
            grid.data[i][j] *= (tensor_out.data[i][j]) * (1 - tensor_out.data[i][j]);
        }
    }
}

float Linear::Linear_relu(float a) {
    return a > 0 ? a : 0;
}
void Linear::Linear_relu(Tensor2D tensor) {
    for (int i = 0; i < tensor.h; ++i) {
        for (int j = 0; j < tensor.w; ++j) {
            if (tensor.data[i][j] < 0)tensor.data[i][j] = 0;
        }
    }
}

float Linear::Linear_relu_back(float a) {
    return a > 0 ? 1 : 0;
}

void Linear::Linear_relu_back(Tensor2D grid, Tensor2D tensor_out) {
    for (int i = 0; i < grid.h; ++i) {
        for (int j = 0; j < grid.w; ++j) {
            if (tensor_out.data[i][j] <= 0) {
                grid.data[i][j] *= 0;
            }
        }
    }
}

float Linear::Linear_tanh(float a) {
    return (exp(a)- exp(-a)) / (exp(a) + exp(-a));
}
void Linear::Linear_tanh(Tensor2D tensor) {
    for (int i = 0; i < tensor.h; ++i) {
        for (int j = 0; j < tensor.w; ++j) {
            tensor.data[i][j] = (exp(tensor.data[i][j]) - exp(-tensor.data[i][j])) 
                / (exp(tensor.data[i][j]) + exp(-tensor.data[i][j]));
        }
    }
}
float Linear::Linear_tanh_back(float a) {
    return (1 - a*a);
}
void Linear::Linear_tanh_back(Tensor2D grid, Tensor2D tensor_out) {
    for (int i = 0; i < grid.h; ++i) {
        for (int j = 0; j < grid.w; ++j) {
            grid.data[i][j] *=  (1 - tensor_out.data[i][j] * tensor_out.data[i][j]);
        }
    }
}