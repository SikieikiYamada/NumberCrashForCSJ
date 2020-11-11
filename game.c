//
// Created by Yamada Youkai on 2020/11/11.
//

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
            printf("%d", gameState->board[j]);
        printf("\n");
    }
    printf("\n");
    printf("Please enter swapping locations:\n");
}

void init_game(GameState *gameState){

}