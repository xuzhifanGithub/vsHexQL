#pragma once
#include"base.h"
#include"board.h"



uint64_t rand64();
void initHashTable();//��ʼ����ϣ������ļ�
void getHashTable();//�����ļ��еĳ�ʼ���Ĺ�ϣ��
uint64_t calculateHash(int** board);//���㵱ǰ�����ϣֵ
