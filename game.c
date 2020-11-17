
//game.c
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "tinymt32.h"

tinymt32_t tinymt32;
tinymt32_t *random = &tinymt32;
uint32_t seed = 0;

void print_board(GameState *gameState){
    printf("############## STEP %d ###############\n",gameState->step);
    printf("Total score: %d\n",gameState->t_score);
    printf("    0 1 2 3 4 5 6 7 8 9\n");
    printf("   --------------------\n");
    for(int i=0;i<=9;i++) {
        printf("%d | ",i);
        for (int j = i*10; j <=i*10+9; j++)
            printf("%d ", gameState->board[j]);
        printf("\n");
    }
    printf("\n");
    printf("Please enter swapping locations:\n");
}

void init_game(GameState *gameState){
    int ini_board[100]={1,2,3,4,3,2,3,2,3,4,
                        2,3,4,2,3,4,1,4,1,1,
                        4,2,3,2,1,1,4,1,4,1,
                        2,3,4,3,3,4,1,2,1,4,
                        4,3,3,2,3,1,2,3,2,2,
                        2,1,4,3,4,1,4,1,2,4,
                        2,1,1,2,1,4,2,4,3,3,
                        4,2,4,3,3,1,2,1,1,3,
                        2,1,1,4,4,2,1,1,4,1,
                        1,3,4,2,1,2,4,2,1,3};
    for(int i=0;i<100;i++)
        gameState->board[i]=ini_board[i];
    gameState->step=0;
    gameState->t_score=0;
    gameState->random = &gameState->tinymt32;
    gameState->seed = 0;
    tinymt32_init(gameState->random, gameState->seed);

}

//return 0:消除完毕； return 1:继续消除
int check_if3(GameState *gameState){
    for (int i=0;i<10;i++)
    {
        for(int j=i*10;j<=i*10+7;j++)
        {
            if(gameState->board[j]==gameState->board[j+1]
            &&gameState->board[j]==gameState->board[j+2]
            &&gameState->board[j+2]==gameState->board[j+1])
                return 1;
        }
    }
    for (int i=0;i<10;i++)
    {
        for(int j=i;j<=i+70;j=j+10)
        {
            if(gameState->board[j]==gameState->board[j+10]
            &&gameState->board[j]==gameState->board[j+20]
            &&gameState->board[j+20]==gameState->board[j+10])
                return 1;
        }
    }
    return 0;

}

void swap_number(int a,int b,int c,int d,GameState *gameState){
    int temp;
    int this_step_score=0;
    temp=gameState->board[c*10+d];
    gameState->board[c*10+d]=gameState->board[a*10+b];
    gameState->board[a*10+b]=temp;
    gameState->step++;
    ///////////check=0还没写/////////////
    int temp_score = 0;
    while(check_if3(gameState)==1){
        //计算分数，消数字
        temp_score += crash_matrix(gameState);
    }
    //（循环结束后）计算this step的总分数
    printf("Score obtained in this step: %d\n", temp_score);
    gameState->t_score += temp_score;
    print_board(gameState);
}

//返回一次的得分
int crash_matrix(GameState *gameState){
    int identical[100] = {0}, eliminated = 0, score = 0;
    for (int i=0;i<10;i++)
    {
        for(int j=i*10;j<=i*10+7;j++)
        {
            if(gameState->board[j]==gameState->board[j+1]
               &&gameState->board[j]==gameState->board[j+2]
               &&gameState->board[j+2]==gameState->board[j+1]) {
                int points = 9;
                identical[j] = 1;
                identical[j+1] = 1;
                identical[j+2] = 1;
                if (j<=i*10+6 && gameState->board[j]==gameState->board[j+3]){
                    points = 16;
                    identical[j+3] = 1;
                }
                if (j<=i*10+5 && gameState->board[j]==gameState->board[j+3] && gameState->board[j]==gameState->board[j+4]){
                    points = 25;
                    identical[j+4] = 1;
                }
                switch (points) {
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
            if(gameState->board[j]==gameState->board[j+10]
               &&gameState->board[j]==gameState->board[j+20]
               &&gameState->board[j+20]==gameState->board[j+10]) {
                int points = 9;
                identical[j] = 1;
                identical[j+10] = 1;
                identical[j+20] = 1;
                if (j<=i+60 && gameState->board[j]==gameState->board[j+30]){
                    points = 16;
                    identical[j+30] = 1;
                }
                if (j<=i+50 && gameState->board[j]==gameState->board[j+30] && gameState->board[j]==gameState->board[j+40]){
                    points = 25;
                    identical[j+40] = 1;
                }
                switch (points) {
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

    //计算消掉的数量
    for (int i = 0; i < 100; ++i) {
        if (identical[i]) eliminated++;
    }
    printf("%d numbers are eliminated!\n", eliminated);

    //下落
    for (int i = 0; i < 100; ++i) {
        if (identical[i]) gameState->board[i] = -1;
    }
    pull_down(gameState);
    generate_new(gameState);

    return score;
}

void pull_down(GameState *gameState){
    int temp;
    for (int i = 0; i < 10; ++i) {
        for (int j = i*10; j < i*10+10; ++j) {
            if (i>0 && gameState->board[j]==-1){
                for (int k = j; k >= 10; k-= 10) {
                    temp = gameState->board[k];
                    gameState->board[k] = gameState->board[k-10];
                    gameState->board[k-10] = temp;
                }
            }
        }
    }
}

void generate_new(GameState *gameState){
    for (int i = 0; i < 100; ++i) {
        if (gameState->board[i]==-1) gameState->board[i] = (int)(tinymt32_generate_uint32(gameState->random)%4+1);
    }
}