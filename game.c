
//game.c
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "tinymt32.h"


tinymt32_t random;
uint32_t seed = 0;


void print_step(GameState *gameState){
    printf("############## STEP %d ###############\n",gameState->step);
    printf("Total score: %d\n",gameState->t_score);
    print_board(gameState);
    printf("Please enter swapping locations:\n");
}

void print_board(GameState *gameState){

    printf("    0 1 2 3 4 5 6 7 8 9\n");
    printf("   --------------------\n");
    for(int i=0;i<=9;i++) {
        printf("%d | ",i);
        for (int j = i*10; j <=i*10+9; j++) {
            if (gameState->board[j] == -1){
                printf("@ ");
            }
            else if(gameState->board[j] == -2){
                printf("C ");
            }
            else if(gameState->board[j] == -3){
                printf("! ");
            }
            else if(gameState->board[j] == -4){
                printf("B ");
            }
            else {
                printf("%d ", gameState->board[j]);
            }
        }
        printf("\n");
    }
    printf("\n");

}

void init_game(GameState *gameState){
    int ini_board[100]={
            3, 3, 1, 2, 4 ,4, 3, 3, 4, 1,
            2, 3, 1, 4, 3 ,3, 4, 2, 3 ,2,
            1, 1, 2, 3, 1 ,3, 2 ,1 ,3, 4,
            2, 3, 3, -1, -1, -1, 3, 3 ,2, 3,
            1, 2, 2, 1, 3 ,3 ,-1 ,1 ,3 ,2,
            1, 1, 2, 3, 2 ,3 ,1 ,4 ,3, 4,
            2, 2, 3, 3, 2 ,1, 2 ,2, 1, 4,
            1, 1, 2, 4, -4, 1, 1 ,3 ,3 ,1,
            1, 3, 1, 4, 1, 4, 2 ,2 ,4 ,4,
            4, 3, 2, 3 ,1 ,1, 2 ,1, 2, 2
    };
    for(int i=0;i<100;i++)
        gameState->board[i]=ini_board[i];
    gameState->step=0;
    gameState->t_score=0;

    tinymt32_init(&random, seed);

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

void swap_number(GameState *gameState, int a,int b,int c,int d){
    int error = 0, bomb = 0;
    if (gameState->board[c*10+d] == -1 || gameState->board[a*10+b] == -1){
        printf("You Cannot Move A Stone Block!\n");
        error = 1;
    }

    if (error){
        printf("\n");
        return;
    }

    if (gameState->board[c*10+d] == -4 || gameState->board[a*10+b] == -4){
        int temp_score = 0;
        bomb = 1;
        printf("Blocks Bombed!\n");
        temp_score += 100;
        for (int i = 0; i < 100; ++i) {
            if (gameState->board[i] < 0){
                gameState->board[i] = 0;
            }
        }
        print_board(gameState);
        pull_down(gameState);
        print_board(gameState);
        generate_new(gameState);
        print_board(gameState);
        while(check_if3(gameState)){
            //计算分数，消数字
            temp_score += crash_matrix(gameState);
        }
        printf("Score obtained in this step %d: %d\n", gameState->step, temp_score);
        gameState->t_score += temp_score;
        return;
    }

    int temp;
    temp=gameState->board[c*10+d];
    gameState->board[c*10+d]=gameState->board[a*10+b];
    gameState->board[a*10+b]=temp;
    gameState->step++;
    printf("Numbers at %d and %d are swapped.\n", a*10+b, c*10+d);
    int temp_score = 0;
    while(check_if3(gameState)==1){
        //计算分数，消数字
        temp_score += crash_matrix(gameState);
    }
    //（循环结束后）计算this step的总分数
    printf("Score obtained in this step %d: %d\n", gameState->step, temp_score);
    gameState->t_score += temp_score;
}

//返回一次的得分
int crash_matrix(GameState *gameState){
    int identical[100] = {0}, score = 0;
    for (int i=0;i<10;i++)
    {
        for(int j=i*10;j<=i*10+7;j++)
        {
            if(gameState->board[j]==gameState->board[j+1]
               &&gameState->board[j]==gameState->board[j+2]
               &&gameState->board[j+2]==gameState->board[j+1]
               &&gameState->board[j]>0) {
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
                if (j<=i*10+4 && gameState->board[j]==gameState->board[j+3] && gameState->board[j]==gameState->board[j+4]
                && gameState->board[j]==gameState->board[j+5]){
                    points = 36;
                    identical[j+5] = 1;
                }
                if (j<=i*10+3 && gameState->board[j]==gameState->board[j+3] && gameState->board[j]==gameState->board[j+4]
                    && gameState->board[j]==gameState->board[j+5] && gameState->board[j]==gameState->board[j+6]){
                    points = 49;
                    identical[j+6] = 1;
                }
                if (j<=i*10+2 && gameState->board[j]==gameState->board[j+3] && gameState->board[j]==gameState->board[j+4]
                    && gameState->board[j]==gameState->board[j+5] && gameState->board[j]==gameState->board[j+6]
                    && gameState->board[j]==gameState->board[j+7]){
                    points = 64;
                    identical[j+7] = 1;
                }
                if (j<=i*10+1 && gameState->board[j]==gameState->board[j+3] && gameState->board[j]==gameState->board[j+4]
                    && gameState->board[j]==gameState->board[j+5] && gameState->board[j]==gameState->board[j+6]
                    && gameState->board[j]==gameState->board[j+7] && gameState->board[j]==gameState->board[j+8]){
                    points = 81;
                    identical[j+8] = 1;
                }
                if (j==i*10 && gameState->board[j]==gameState->board[j+3] && gameState->board[j]==gameState->board[j+4]
                    && gameState->board[j]==gameState->board[j+5] && gameState->board[j]==gameState->board[j+6]
                    && gameState->board[j]==gameState->board[j+7] && gameState->board[j]==gameState->board[j+8]
                    && gameState->board[j]==gameState->board[j+9]){
                    points = 100;
                    identical[j+9] = 1;
                }
                switch (points) {
                    case 100:
                        j+=9;
                        printf("10 numbers are eliminated!\n");
                        break;
                    case 81:
                        j+=8;
                        printf("9 numbers are eliminated!\n");
                        break;
                    case 64:
                        j+=7;
                        printf("8 numbers are eliminated!\n");
                        break;
                    case 49:
                        j+=6;
                        printf("7 numbers are eliminated!\n");
                        break;
                    case 36:
                        j+=5;
                        printf("6 numbers are eliminated!\n");
                        break;
                    case 25:
                        j+=4;
                        printf("5 numbers are eliminated!\n");
                        break;
                    case 16:
                        j+=3;
                        printf("4 numbers are eliminated!\n");
                        break;
                    default:
                        j+=2;
                        printf("3 numbers are eliminated!\n");
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
               &&gameState->board[j+20]==gameState->board[j+10]
               &&gameState->board[j]>0) {
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
                if (j<=i+40 && gameState->board[j]==gameState->board[j+30] && gameState->board[j]==gameState->board[j+40]
                && gameState->board[j]==gameState->board[j+50]){
                    points = 36;
                    identical[j+50] = 1;
                }
                if (j<=i+30 && gameState->board[j]==gameState->board[j+30] && gameState->board[j]==gameState->board[j+40]
                && gameState->board[j]==gameState->board[j+50] && gameState->board[j]==gameState->board[j+60]){
                    points = 49;
                    identical[j+60] = 1;
                }
                if (j<=i+20 && gameState->board[j]==gameState->board[j+30] && gameState->board[j]==gameState->board[j+40]
                    && gameState->board[j]==gameState->board[j+50] && gameState->board[j]==gameState->board[j+60]
                    && gameState->board[j]==gameState->board[j+70]){
                    points = 64;
                    identical[j+70] = 1;
                }
                if (j<=i+10 && gameState->board[j]==gameState->board[j+30] && gameState->board[j]==gameState->board[j+40]
                    && gameState->board[j]==gameState->board[j+50] && gameState->board[j]==gameState->board[j+60]
                    && gameState->board[j]==gameState->board[j+70] && gameState->board[j]==gameState->board[j+80]){
                    points = 81;
                    identical[j+80] = 1;
                }
                if (j==i && gameState->board[j]==gameState->board[j+30] && gameState->board[j]==gameState->board[j+40]
                    && gameState->board[j]==gameState->board[j+50] && gameState->board[j]==gameState->board[j+60]
                    && gameState->board[j]==gameState->board[j+70] && gameState->board[j]==gameState->board[j+80]
                    && gameState->board[j]==gameState->board[j+90]){
                    points = 100;
                    identical[j+90] = 1;
                }
                switch (points) {
                    case 100:
                        j+=90;
                        printf("10 numbers are eliminated!\n");
                        break;
                    case 81:
                        j+=80;
                        printf("9 numbers are eliminated!\n");
                        break;
                    case 64:
                        j+=70;
                        printf("8 numbers are eliminated!\n");
                        break;
                    case 49:
                        j+=60;
                        printf("7 numbers are eliminated!\n");
                        break;
                    case 36:
                        j+=50;
                        printf("6 numbers are eliminated!\n");
                        break;
                    case 25:
                        j+=40;
                        printf("5 numbers are eliminated!\n");
                        break;
                    case 16:
                        j+=30;
                        printf("4 numbers are eliminated!\n");
                        break;
                    default:
                        j+=20;
                        printf("3 numbers are eliminated!\n");
                        break;
                }
                score += points;

            }
        }
    }

    printf("\n");
    //下落
    for (int i = 0; i < 100; ++i) {
        if (identical[i]) gameState->board[i] = 0;
    }
    print_board(gameState);
    pull_down(gameState);
    print_board(gameState);
    generate_new(gameState);

    return score;
}

void pull_down(GameState *gameState){
    int temp;
    for (int i = 0; i < 10; ++i) {
        for (int j = i*10; j < i*10+10; ++j) {
            if (i>0 && gameState->board[j]==0){
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
    for (int i = 0; i < 10; ++i) {
        for (int j = i*10; j < i*10+10; j++) {
            if (gameState->board[j]==0) gameState->board[j] = (int)(tinymt32_generate_uint32(&random)%4+1);
        }
    }
}