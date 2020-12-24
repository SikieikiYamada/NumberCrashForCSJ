//
// Created by Yamada Youkai on 2020/11/24.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef NUMBERCRASH_AIPLAYER_H
#define NUMBERCRASH_AIPLAYER_H

#define MAX_DEPTH 0

typedef struct GameNode{
    int board[100]; //这一步的棋盘
    struct GameNode *tree[180]; //子节点，即下一步
    int temp_score; //这一步的得分
    int total_score; //这一步和之后的总得分
    int cmd; //这一步的命令
} GameTree;

int make_cmd(int a, int b, int c, int d);
void make_tree(GameTree *gameTree);

static int ai_player_studentID( int K , const int * board ){
    int res;
    GameTree *root = (GameTree*)malloc(sizeof(GameTree));
    memcpy(root->board, board, 100*sizeof(int));
    root->temp_score = root->total_score = 0;
    make_tree(root);
    int max_pos = 0;
    for (int i=0; i<180; i++){
        printf("%d : %d\n", root->tree[i]->total_score, root->tree[i]->cmd);
        if (root->tree[i]->total_score > root->tree[max_pos]->total_score)
            max_pos = i;
    }

    res = root->tree[max_pos]->cmd;

    for (int i = 0; i < 180; ++i) {
        free(root->tree[i]);
    }
    free(root);
    return res;
}

static int * make_swap(int cmd){
    char str[5];
    sprintf(str, "%04d", cmd);
    int move[4];
    move[0] = str[0]-'0';
    move[1] = str[1]-'0';
    move[2] = str[2]-'0';
    move[3] = str[3]-'0';
    return move;
}

#endif //NUMBERCRASH_AIPLAYER_H
