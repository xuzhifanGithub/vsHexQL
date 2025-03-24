
#include"board.h"



void initBoard(int** board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        memset(board[i], 0, sizeof(int) * BOARD_SIZE);
    }



}

void displayBoard(int** board)
{
    /*int x = 6, y=6;
    board[x][y] = RED_SIDE;
    for(int i=0;i<11;i++)
    {

        board[ 4][i ] = BLUE_SIDE;
    }*/



    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == RED_SIDE)
            {
                //printf("\033[1;31mR   ");
                //system("color 4");
                printf("R   ");
            }
            else if (board[i][j] == BLUE_SIDE)
            {
                //system("color 1");
                printf("B   ");
                //printf("\033[1;34mB   ");
            }
            else
            {

                //system("color 3");
                printf("0   ");
                //printf("\033[1;36m0   ");
            }

        }
        printf("\n\n");
        for (int k = i; k >= 0; k--)
        {
            printf("  ");
        }

    }

    //printf("\033[0m");
}


void displayVecInt(vector<int> vecInt)
{
    printf("\nvecInt:\n");
    //int i=0;
    for (auto it = vecInt.begin(); it != vecInt.end(); it++)
    {
        //i++;
        printf("(%d,%d) ", (*it) / BOARD_SIZE, (*it) % BOARD_SIZE);
    }
    printf("\n");

}

bool isRedWin(int** board)
{
    bool isUpRed = false;
    bool isDownRed = false;

    for (int j = 0; j < BOARD_SIZE; j++)
    {
        if (board[0][j] == RED_SIDE)
        {
            isUpRed = true;
            break;
        }
    }

    if (!isUpRed)
    {
        return false;
    }

    for (int j = 0; j < BOARD_SIZE; j++)
    {
        if (board[BOARD_SIZE - 1][j] == RED_SIDE)
        {
            isDownRed = true;
            break;
        }
    }

    if (!isDownRed)
    {
        return false;
    }

    bool** used = (bool**)malloc(sizeof(bool*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        used[i] = (bool*)malloc(sizeof(bool) * BOARD_SIZE);
        memset(used[i], false, sizeof(bool) * BOARD_SIZE);
    }

    bool isWin = false;
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        if (board[0][j] == RED_SIDE)
        {
            isWin = isRedWinCheck(board, 0, j, used);
            if (isWin)
            {
                for (int i = 0; i < BOARD_SIZE; i++)
                {
                    free(used[i]);
                }
                free(used);
                return isWin;
            }
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        free(used[i]);
    }
    free(used);
    return isWin;
}

bool isRedWinCheck(int** board, int lastX, int lastY, bool** used)
{
    if (lastX == BOARD_SIZE - 1)
    {
        return true;
    }

    bool isWin = false;
    used[lastX][lastY] = true;
    int x[6];
    int y[6];


    for (int i = 0; i < 6; i++)
    {
        x[i] = lastX + dx6[i];
        y[i] = lastY + dy6[i];
    }


    if (y[2] >= 0 && board[x[2]][y[2]] == RED_SIDE && !used[x[2]][y[2]])//left
    {
        isWin = isRedWinCheck(board, x[2], y[2], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (y[3] < BOARD_SIZE && board[x[3]][y[3]] == RED_SIDE && !used[x[3]][y[3]])//right
    {
        isWin = isRedWinCheck(board, x[3], y[3], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (x[4] < BOARD_SIZE && y[4] >= 0 && board[x[4]][y[4]] == RED_SIDE && !used[x[4]][y[4]])//down left
    {
        isWin = isRedWinCheck(board, x[4], y[4], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (x[5] < BOARD_SIZE && board[x[5]][y[5]] == RED_SIDE && !used[x[5]][y[5]])//down right
    {
        isWin = isRedWinCheck(board, x[5], y[5], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (x[0] >= 0 && board[x[0]][y[0]] == RED_SIDE && !used[x[0]][y[0]])//up left
    {
        isWin = isRedWinCheck(board, x[0], y[0], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }


    if (x[1] >= 0 && y[1] < BOARD_SIZE && board[x[1]][y[1]] == RED_SIDE && !used[x[1]][y[1]])//up right
    {
        isWin = isRedWinCheck(board, x[1], y[1], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }


    used[lastX][lastY] = true;
    return false;
}




bool isBlueWin(int** board)
{
    bool isLeftBlue = false;
    bool isRightBlue = false;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][0] == BLUE_SIDE)
        {
            isLeftBlue = true;
            break;
        }
    }

    if (!isLeftBlue)
    {
        return false;
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][BOARD_SIZE - 1] == BLUE_SIDE)
        {
            isRightBlue = true;
            break;
        }
    }

    if (!isRightBlue)
    {
        return false;
    }

    bool** used = (bool**)malloc(sizeof(bool*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        used[i] = (bool*)malloc(sizeof(bool) * BOARD_SIZE);
        memset(used[i], false, sizeof(bool) * BOARD_SIZE);
    }

    bool isWin = false;
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        if (board[j][0] == BLUE_SIDE)
        {
            isWin = isBlueWinCheck(board, j, 0, used);
            if (isWin)
            {
                for (int i = 0; i < BOARD_SIZE; i++)
                {
                    free(used[i]);
                }
                free(used);
                return isWin;
            }
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        free(used[i]);
    }
    free(used);
    return isWin;
}


bool isBlueWinCheck(int** board, int lastX, int lastY, bool** used)
{
    if (lastY == BOARD_SIZE - 1)
    {
        return true;
    }

    bool isWin = false;
    used[lastX][lastY] = true;
    int x[6];
    int y[6];


    for (int i = 0; i < 6; i++)
    {
        x[i] = lastX + dx6[i];
        y[i] = lastY + dy6[i];
    }


    if (y[2] >= 0 && board[x[2]][y[2]] == BLUE_SIDE && !used[x[2]][y[2]])//left
    {
        isWin = isBlueWinCheck(board, x[2], y[2], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (y[3] < BOARD_SIZE && board[x[3]][y[3]] == BLUE_SIDE && !used[x[3]][y[3]])//right
    {
        isWin = isBlueWinCheck(board, x[3], y[3], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (x[4] < BOARD_SIZE && y[4] >= 0 && board[x[4]][y[4]] == BLUE_SIDE && !used[x[4]][y[4]])//down left
    {
        isWin = isBlueWinCheck(board, x[4], y[4], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (x[5] < BOARD_SIZE && board[x[5]][y[5]] == BLUE_SIDE && !used[x[5]][y[5]])//down right
    {
        isWin = isBlueWinCheck(board, x[5], y[5], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (x[0] >= 0 && board[x[0]][y[0]] == BLUE_SIDE && !used[x[0]][y[0]])//up left
    {
        isWin = isBlueWinCheck(board, x[0], y[0], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }


    if (x[1] >= 0 && y[1] < BOARD_SIZE && board[x[1]][y[1]] == BLUE_SIDE && !used[x[1]][y[1]])//up right
    {
        isWin = isBlueWinCheck(board, x[1], y[1], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }


    used[lastX][lastY] = true;
    return false;
}

bool isSideWin(int** board, int moveSide)
{
    if (moveSide == RED_SIDE)
        return isRedWin(board);
    else
        return isBlueWin(board);
}

vector<int> generateSideMovePos(int** board)
{
    vector<int> vecEmptyPos;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == EMPTY_POS)
            {
                vecEmptyPos.push_back(i * BOARD_SIZE + j);
            }
        }
    }
    return vecEmptyPos;
}




//////////////////////////////////////



void initBoard(int board[][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        memset(board[i], 0, sizeof(int) * BOARD_SIZE);
    }



}

void displayBoard(int board[][BOARD_SIZE])
{
    /*int x = 6, y=6;
    board[x][y] = RED_SIDE;
    for(int i=0;i<11;i++)
    {

        board[ 4][i ] = BLUE_SIDE;
    }*/



    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == RED_SIDE)
            {
                //printf("\033[1;31mR   ");
                //system("color 4");
                printf("R   ");
            }
            else if (board[i][j] == BLUE_SIDE)
            {
                //system("color 1");
                printf("B   ");
                //printf("\033[1;34mB   ");
            }
            else
            {

                //system("color 3");
                printf("0   ");
                //printf("\033[1;36m0   ");
            }

        }
        printf("\n\n");
        for (int k = i; k >= 0; k--)
        {
            printf("  ");
        }

    }

    //printf("\033[0m");
}


bool isRedWin(int board[][BOARD_SIZE])
{
    bool isUpRed = false;
    bool isDownRed = false;

    for (int j = 0; j < BOARD_SIZE; j++)
    {
        if (board[0][j] == RED_SIDE)
        {
            isUpRed = true;
            break;
        }
    }

    if (!isUpRed)
    {
        return false;
    }

    for (int j = 0; j < BOARD_SIZE; j++)
    {
        if (board[BOARD_SIZE - 1][j] == RED_SIDE)
        {
            isDownRed = true;
            break;
        }
    }

    if (!isDownRed)
    {
        return false;
    }

    bool** used = (bool**)malloc(sizeof(bool*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        used[i] = (bool*)malloc(sizeof(bool) * BOARD_SIZE);
        memset(used[i], false, sizeof(bool) * BOARD_SIZE);
    }

    bool isWin = false;
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        if (board[0][j] == RED_SIDE)
        {
            isWin = isRedWinCheck(board, 0, j, used);
            if (isWin)
            {
                return isWin;
            }
        }
    }

    return isWin;
}

bool isRedWinCheck(int board[][BOARD_SIZE], int lastX, int lastY, bool** used)
{
    if (lastX == BOARD_SIZE - 1)
    {
        return true;
    }

    bool isWin = false;
    used[lastX][lastY] = true;
    int x[6];
    int y[6];


    for (int i = 0; i < 6; i++)
    {
        x[i] = lastX + dx6[i];
        y[i] = lastY + dy6[i];
    }


    if (y[2] >= 0 && board[x[2]][y[2]] == RED_SIDE && !used[x[2]][y[2]])//left
    {
        isWin = isRedWinCheck(board, x[2], y[2], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (y[3] < BOARD_SIZE && board[x[3]][y[3]] == RED_SIDE && !used[x[3]][y[3]])//right
    {
        isWin = isRedWinCheck(board, x[3], y[3], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (x[4] < BOARD_SIZE && y[4] >= 0 && board[x[4]][y[4]] == RED_SIDE && !used[x[4]][y[4]])//down left
    {
        isWin = isRedWinCheck(board, x[4], y[4], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (x[5] < BOARD_SIZE && board[x[5]][y[5]] == RED_SIDE && !used[x[5]][y[5]])//down right
    {
        isWin = isRedWinCheck(board, x[5], y[5], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (x[0] >= 0 && board[x[0]][y[0]] == RED_SIDE && !used[x[0]][y[0]])//up left
    {
        isWin = isRedWinCheck(board, x[0], y[0], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }


    if (x[1] >= 0 && y[1] < BOARD_SIZE && board[x[1]][y[1]] == RED_SIDE && !used[x[1]][y[1]])//up right
    {
        isWin = isRedWinCheck(board, x[1], y[1], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }


    used[lastX][lastY] = true;
    return false;
}




bool isBlueWin(int board[][BOARD_SIZE])
{
    bool isLeftBlue = false;
    bool isRightBlue = false;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][0] == BLUE_SIDE)
        {
            isLeftBlue = true;
            break;
        }
    }

    if (!isLeftBlue)
    {
        return false;
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][BOARD_SIZE - 1] == BLUE_SIDE)
        {
            isRightBlue = true;
            break;
        }
    }

    if (!isRightBlue)
    {
        return false;
    }

    bool** used = (bool**)malloc(sizeof(bool*) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        used[i] = (bool*)malloc(sizeof(bool) * BOARD_SIZE);
        memset(used[i], false, sizeof(bool) * BOARD_SIZE);
    }

    bool isWin = false;
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        if (board[j][0] == BLUE_SIDE)
        {
            isWin = isBlueWinCheck(board, j, 0, used);
            if (isWin)
            {
                return isWin;
            }
        }
    }

    return isWin;
}


bool isBlueWinCheck(int board[][BOARD_SIZE], int lastX, int lastY, bool** used)
{
    if (lastY == BOARD_SIZE - 1)
    {
        return true;
    }

    bool isWin = false;
    used[lastX][lastY] = true;
    int x[6];
    int y[6];


    for (int i = 0; i < 6; i++)
    {
        x[i] = lastX + dx6[i];
        y[i] = lastY + dy6[i];
    }


    if (y[2] >= 0 && board[x[2]][y[2]] == BLUE_SIDE && !used[x[2]][y[2]])//left
    {
        isWin = isBlueWinCheck(board, x[2], y[2], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (y[3] < BOARD_SIZE && board[x[3]][y[3]] == BLUE_SIDE && !used[x[3]][y[3]])//right
    {
        isWin = isBlueWinCheck(board, x[3], y[3], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (x[4] < BOARD_SIZE && y[4] >= 0 && board[x[4]][y[4]] == BLUE_SIDE && !used[x[4]][y[4]])//down left
    {
        isWin = isBlueWinCheck(board, x[4], y[4], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (x[5] < BOARD_SIZE && board[x[5]][y[5]] == BLUE_SIDE && !used[x[5]][y[5]])//down right
    {
        isWin = isBlueWinCheck(board, x[5], y[5], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }

    if (x[0] >= 0 && board[x[0]][y[0]] == BLUE_SIDE && !used[x[0]][y[0]])//up left
    {
        isWin = isBlueWinCheck(board, x[0], y[0], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }


    if (x[1] >= 0 && y[1] < BOARD_SIZE && board[x[1]][y[1]] == BLUE_SIDE && !used[x[1]][y[1]])//up right
    {
        isWin = isBlueWinCheck(board, x[1], y[1], used);
        if (isWin == true)
        {
            used[lastX][lastY] = false;
            return true;
        }
    }


    used[lastX][lastY] = true;
    return false;
}

bool isSideWin(int board[][BOARD_SIZE], int moveSide)
{
    if (moveSide == RED_SIDE)
        return isRedWin(board);
    else
        return isBlueWin(board);
}

vector<int> generateSideMovePos(int board[][BOARD_SIZE])
{
    vector<int> vecEmptyPos;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == EMPTY_POS)
            {
                vecEmptyPos.push_back(i * BOARD_SIZE + j);
            }
        }
    }
    return vecEmptyPos;
}

