
//

#include "aiplayer.h"
#include <string.h>
#include <stdio.h>

int step_score = 0;

int make_cmd(int a, int b, int c, int d){
    return a*1000 + b*100 + c*10 + d;
}

int check(const int * board){
    for (int i=0;i<10;i++)
    {
        for(int j=i*10;j<=i*10+7;j++)
        {
            if(board[j]==board[j+1]&&board[j]==board[j+2]&&board[j]!=-1)
                return 1;
        }
    }
    for (int i=0;i<10;i++)
    {
        for(int j=i;j<=i+70;j=j+10)
        {
            if(board[j]==board[j+10]&&board[j]==board[j+20]&&board[j]!=-1)
                return 1;
        }
    }
    return 0;
}

void pull(int *board){
    int temp;
    for (int i = 0; i < 10; ++i) {
        for (int j = i*10; j < i*10+10; ++j) {
            if (i>0 && board[j]==-1){
                for (int k = j; k >= 10; k-= 10) {
                    temp = board[k];
                    board[k] = board[k-10];
                    board[k-10] = temp;
                }
            }
        }
    }
}

int crash_board(int * board){
    int identical[100] = {0}, score = 0;
    for (int i=0;i<10;i++)
    {
        for(int j=i*10;j<=i*10+7;j++)
        {
            if(board[j]==board[j+1] && board[j]==board[j+2] && board[j]!= -1) {
                int points = 9;
                identical[j] = 1;
                identical[j+1] = 1;
                identical[j+2] = 1;
                if (j<=i*10+6 && board[j]==board[j+3]){
                    points = 16;
                    identical[j+3] = 1;
                }
                if (j<=i*10+5 && board[j]==board[j+3] && board[j]==board[j+4]){
                    points = 25;
                    identical[j+4] = 1;
                }
                if (j<=i*10+4 && board[j]==board[j+3] && board[j]==board[j+4]
                    && board[j]==board[j+5]){
                    points = 36;
                    identical[j+5] = 1;
                }
                if (j<=i*10+3 && board[j]==board[j+3] && board[j]==board[j+4]
                    && board[j]==board[j+5] && board[j]==board[j+6]){
                    points = 49;
                    identical[j+6] = 1;
                }
                if (j<=i*10+2 && board[j]==board[j+3] && board[j]==board[j+4]
                    && board[j]==board[j+5] && board[j]==board[j+6]  && board[j]==board[j+7]){
                    points = 64;
                    identical[j+7] = 1;
                }
                if (j<=i*10+1 && board[j]==board[j+3] && board[j]==board[j+4]
                    && board[j]==board[j+5] && board[j]==board[j+6]
                    && board[j]==board[j+7] && board[j]==board[j+8]){
                    points = 81;
                    identical[j+8] = 1;
                }
                if (j==i*10 && board[j]==board[j+3] && board[j]==board[j+4]
                    && board[j]==board[j+5] && board[j]==board[j+6]
                    && board[j]==board[j+7] && board[j]==board[j+8]
                    && board[j]==board[j+9]){
                    points = 100;
                    identical[j+9] = 1;
                }
                switch (points) {
                    case 100:
                        j+=9;
                        break;
                    case 81:
                        j+=8;
                        break;
                    case 64:
                        j+=7;
                        break;
                    case 49:
                        j+=6;
                        break;
                    case 36:
                        j+=5;
                        break;
                    case 25:
                        j+=4;
                        break;
                    case 16:
                        j+=3;
                        break;
                    default:
                        j+=2;
                        break;
                }
                score += points;
            }
        }
    }
    for (int i=0;i<10;i++)
    {
        for(int j=i;j<=i+70;j=j+10)
        {
            if(board[j]==board[j+10] && board[j]==board[j+20] && board[j] != -1) {
                int points = 9;
                identical[j] = 1;
                identical[j+10] = 1;
                identical[j+20] = 1;
                if (j<=i+60 && board[j]==board[j+30]){
                    points = 16;
                    identical[j+30] = 1;
                }
                if (j<=i+50 && board[j]==board[j+30] && board[j]==board[j+40]){
                    points = 25;
                    identical[j+40] = 1;
                }
                if (j<=i+40 && board[j]==board[j+30] && board[j]==board[j+40]
                    && board[j]==board[j+50]){
                    points = 36;
                    identical[j+50] = 1;
                }
                if (j<=i+30 && board[j]==board[j+30] && board[j]==board[j+40]
                    && board[j]==board[j+50] && board[j]==board[j+60]){
                    points = 49;
                    identical[j+60] = 1;
                }
                if (j<=i+20 && board[j]==board[j+30] && board[j]==board[j+40]
                    && board[j]==board[j+50] && board[j]==board[j+60]
                    && board[j]==board[j+70]){
                    points = 64;
                    identical[j+70] = 1;
                }
                if (j<=i+10 && board[j]==board[j+30] && board[j]==board[j+40]
                    && board[j]==board[j+50] && board[j]==board[j+60]
                    && board[j]==board[j+70] && board[j]==board[j+80]){
                    points = 81;
                    identical[j+80] = 1;
                }
                if (j==i && board[j]==board[j+30] && board[j]==board[j+40]
                    && board[j]==board[j+50] && board[j]==board[j+60]
                    && board[j]==board[j+70] && board[j]==board[j+80]
                    && board[j]==board[j+90]){
                    points = 100;
                    identical[j+90] = 1;
                }
                switch (points) {
                    case 100:
                        j+=90;
                        break;
                    case 81:
                        j+=80;
                        break;
                    case 64:
                        j+=70;
                        break;
                    case 49:
                        j+=60;
                        break;
                    case 36:
                        j+=50;
                        break;
                    case 25:
                        j+=40;
                        break;
                    case 16:
                        j+=30;
                        break;
                    default:
                        j+=20;
                        break;
                }
                score += points;
            }
        }
    }
    for (int i = 0; i < 100; ++i) {
        if (identical[i]) board[i] = -1;
    }

    pull(board);

    return score;
}

int * swap_board(const int * board, int a, int b, int c, int d){
    step_score = 0;
    int res[100];
    for (int i = 0; i < 100; ++i) {
        if (i == a*10+b){
            res[i] = board[c*10+d];
        } else if (i == c*10+d){
            res[i] = board[a*10+b];
        } else{
            res[i] = board[i];
        }
    }

    while (check(res)){
        step_score += crash_board(res);
    }
    return res;
}

int find_best(int * board, int depth){
    int best_score = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i*10+j] == board[i*10+j+1]){
                continue;
            }
            step_score = 0;
            int *res = swap_board(board, i, j, i, j + 1);
            int temp_score = step_score;
            if (depth < MAX_DEPTH) {
                temp_score += find_best(res, depth + 1);
            }
            if (temp_score > best_score){
                best_score = temp_score;
            }
        }
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (board[i*10+j] == board[i*10+j+10]){
                continue;
            }
            step_score = 0;
            int *res = swap_board(board, i, j, i + 1, j);
            int temp_score = step_score;
            if (depth < MAX_DEPTH) {
                temp_score += find_best(res, depth + 1);
            }
            if (temp_score > best_score){
                best_score = temp_score;
            }
        }
    }
    return best_score;
}

void make_tree(GameTree *gameTree){
    //制造叶子结点
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            GameTree *leaf = (GameTree*)malloc(sizeof(GameTree));
            leaf->cmd = make_cmd(i, j, i, j+1);
            int *res = swap_board(gameTree->board, i, j, i, j+1);
            memcpy(leaf->board, res, 100*sizeof(int));
            leaf->temp_score = step_score;
            leaf->total_score = leaf->temp_score;
            if (gameTree->board[i*10+j] == gameTree->board[i*10+j+1]){
                leaf->total_score = -1000;
            }
            gameTree->tree[i+j*10] = leaf;
//            if (depth==2) printf("d2 succ\n");
        }
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 10; ++j) {
            GameTree *leaf = (GameTree*)malloc(sizeof(GameTree));
            leaf->cmd = make_cmd(i, j, i+1, j);
            int *res = swap_board(gameTree->board, i, j, i+1, j);
            memcpy(leaf->board, res, 100*sizeof(int));
            leaf->temp_score = step_score;
            leaf->total_score = leaf->temp_score;
            if (gameTree->board[i*10+j] == gameTree->board[i*10+j+1]){
                leaf->total_score = -1000;
            }
            gameTree->tree[i*10+j+90] = leaf;
//            if (leaf->depth==2) printf("d2 succ\n");
        }
    }

    for (int i = 0; i < 180; ++i) {
        gameTree->tree[i]->total_score += find_best(gameTree->tree[i]->board, 0);
    }

//    //计算最高分
//    if (gameTree->depth<MAX_DEPTH){
//        int max_score = 0;
//        for (int i = 0; i < 180; ++i) {
//            if (gameTree->tree[i]->total_score > max_score){
//                max_score = gameTree->tree[i]->total_score;
//            }
//            free(gameTree->tree[i]);
//        }
//        gameTree->total_score += max_score;
//    }
}