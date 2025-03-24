#pragma once
#include"base.h"
#include"board.h"



uint64_t rand64();
void initHashTable();//初始化哈希表存入文件
void getHashTable();//读入文件中的初始化的哈希表
uint64_t calculateHash(int** board);//计算当前局面哈希值
