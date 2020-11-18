//main.c
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "tinymt32.h"
#include <string.h>
GameState gameState;
GameState *gameState_ptr=&gameState;
int main() {
    init_game(gameState_ptr);

    char input[10];
    int a, b, c, d;
    while (gameState_ptr->step < 100) {
        print_board(gameState_ptr);
        scanf("%s", input);
        a = input[0] - '0';
        b = input[1] - '0';
        c = input[2] - '0';
        d = input[3] - '0';
        if (strlen(input) != 4 ||
            !(((a == c) && ((b - d == 1) || (d - b == 1))) || ((b == d) && ((a - c == 1) || (c - a == 1))))) {

            printf("Please enter a valid commend\n");
            continue;
        }
        swap_number(a, b, c, d,gameState_ptr);



    }
    //打印得分函数
    printf("total score : %d\n",gameState_ptr->t_score);
    printf("mean score : %f", (float)gameState_ptr->t_score);



    return 0;

}