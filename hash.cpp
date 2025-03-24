


#include"hash.h"


uint64_t hashTable[BOARD_SIZE][BOARD_SIZE][2];

uint64_t rand64()
{
    //srand(time(0));
    //Sleep(20);

    return rand() ^ ((uint64_t)rand() << 15) ^ ((uint64_t)rand() << 30) ^
        ((uint64_t)rand() << 45) ^ ((uint64_t)rand() << 60);
}

//初始化哈希表存入文件
void initHashTable()
{
    int i, j, k;
    uint64_t hashValue;
    FILE* hashValueFPtr;

    //打开文件
    if ((hashValueFPtr = fopen("data\\hashTable.txt", "r+")) == NULL)
    {
        printf("Open hashTable TXT error!");
        exit(0);
    }
    else
    {
        int cou = 1;

        //存入初始化的哈希值
        for (i = 0; i < BOARD_SIZE; i++)
        {
            for (j = 0; j < BOARD_SIZE; j++)
            {
                for (k = 0; k < 2; k++)
                {
                    hashValue = 0;
                    hashValue = rand64();
                    //printf("%d.(%llu)\n",cou,hashValue);
                    fprintf(hashValueFPtr, "%llu ", hashValue);
                    cou++;
                }
            }
        }

        fclose(hashValueFPtr);
    }
}




//读入文件中的初始化的哈希表
void getHashTable()
{
    int i, j, k;
    FILE* hashTableFilePtr;

    //打开文件
    if ((hashTableFilePtr = fopen("data\\hashTable.txt", "r")) == NULL)
    {
        printf("Open hashTable TXT error!");
        exit(0);
    }
    else
    {

        if (fgetc(hashTableFilePtr) == EOF)
        {
            //关闭文件
            fclose(hashTableFilePtr);
            printf("\nHash Table is Empty\n");

            initHashTable();
            getHashTable();
            return;
        }
        rewind(hashTableFilePtr);

        //读入文件中的哈希值
        while (!feof(hashTableFilePtr))
        {
            for (i = 0; i < BOARD_SIZE; i++)
            {
                for (j = 0; j < BOARD_SIZE; j++)
                {
                    for (k = 0; k < 2; k++)
                    {

                        fscanf(hashTableFilePtr, "%llu ", &hashTable[i][j][k]);
                        //printf("%llu\n",hashTable[i][j][k]);
                    }
                }
            }

        }

        //检查hashTable

        /*int count = 0;
        for(i=0;i<11;i++)
        {
            for(j=0;j<11;j++)
            {
                for(k=0;k<2;k++)
                {
                    printf("%3d.(%llu)\n",count+1,hashTable[i][j][k]);
                    count++;
                }
            }
        }*/

        //关闭文件
        fclose(hashTableFilePtr);
    }

}



//计算当前局面哈希值
uint64_t calculateHash(int** board)
{
    int i, j;
    uint64_t tempHashValue = 0;

    //计算当前局面哈希值
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            //printf("hash[%d][%d] = {%llu][%llu}\n",i-1,j-1,hashTable[i-1][j-1][0],hashTable[i-1][j-1][1]);
            if (board[i][j] == RED_SIDE)
            {
                //printf("(R%llu,%llu,%llu)",tempHashValue,hashTable[i-1][j-1][0],tempHashValue^hashTable[i-1][j-1][0]);
                tempHashValue = tempHashValue ^ hashTable[i][j][0];
            }
            else if (board[i][j] == BLUE_SIDE)
            {
                //printf("(B%llu,%llu,%llu)",tempHashValue,hashTable[i-1][j-1][1],tempHashValue^hashTable[i-1][j-1][1]);
                tempHashValue = tempHashValue ^ hashTable[i][j][1];
            }
        }
    }

    return tempHashValue;
}




