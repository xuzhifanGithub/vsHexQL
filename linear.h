#pragma once
#include"base.h"


struct Tensor2D {
    int h;
    int w;
    float** data;
};
struct FC {
    Tensor2D W;
    Tensor2D B;
    int in_features;
    int out_features;
};

std::mt19937& get_generator();

Tensor2D Tensor2D_init(int h, int w);
void Tensor2D_init(int h, int w,Tensor2D tensor);
Tensor2D Tensor2D_init(int h, int w, float value);
void Tensor2D_display(Tensor2D tensor);
Tensor2D Tensor2D_copy(Tensor2D tensor);
void Tensor2D_copy(Tensor2D tensor1, Tensor2D tensor2);
void Tensor2D_init_copy(Tensor2D tensor, Tensor2D tensor2);
void Tensor2D_setzero(Tensor2D tensor);
void freeTensor(Tensor2D tensor);

class Linear {
public:
    
    FC Linear_init(int in_features, int out_features);//��ʼ��
    FC Linear_init(int in_features, int out_features, float value);
    void Linear_display(FC fc, bool bias = true);//��ӡȨ�ؾ���
    Tensor2D Linear_forward(Tensor2D tensor_in, FC fc_w, bool bias = true);//ǰ�򴫲�
    FC Linear_copy(FC fc);//����FC
    Tensor2D Linear_backward(Tensor2D pre_det, FC fc_w);//���򴫲�
    void Linear_update_grid(FC fc_w, Tensor2D grid, Tensor2D input, float learning_rate = 0.01);//�����ݶ�
    float Linear_loss(Tensor2D y_out, Tensor2D y_true); //������ʧSGD
    Tensor2D Linear_loseBack(Tensor2D y_out, Tensor2D y_true);//���㷴�򴫲���һ����ݶ�
    float Linear_sigmoid(float a);
    void Linear_sigmoid(Tensor2D tensor);
    float Linear_sigmoid_back(float a);
    void Linear_sigmoid_back(Tensor2D grid, Tensor2D tensor_out);

    float Linear_relu(float a);
    void Linear_relu(Tensor2D tensor);
    float Linear_relu_back(float a);
    void Linear_relu_back(Tensor2D grid, Tensor2D tensor_out);

    float Linear_tanh(float a);
    void Linear_tanh(Tensor2D tensor);
    float Linear_tanh_back(float a);
    void Linear_tanh_back(Tensor2D grid, Tensor2D tensor_out);


};