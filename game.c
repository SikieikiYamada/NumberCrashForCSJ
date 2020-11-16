
//game.c
#include <string.h>
#include <stdio.h>
#include "game.h"
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


}

int check_if3(GameState *gameState){
    for (int i=0;i<10;i++)
    {
        for(int j=i*10;j<=i*10+7;j++)
        {
            if(gameState->board[j]==gameState->board[j+1]&&gameState->board[j]
                                                           ==gameState->board[j+2]&&gameState->board[j+2]==gameState->board[j+1])
                return 1;
        }
    }
    for (int i=0;i<10;i++)
    {
        for(int j=i;j<=i+70;j=j+10)
        {
            if(gameState->board[j]==gameState->board[j+10]&&gameState->board[j]
                                                            ==gameState->board[j+20]&&gameState->board[j+20]==gameState->board[j+10])
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
    while(check_if3(gameState)==1)
    {
        //打标记函数
        //更新函数
        //check——if3
        //。。（有点像循环但不知道怎么写
        //（循环结束后）计算this step的总分数
    }


}
