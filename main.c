//main.c
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "aiplayer.h"

int main() {
    int cmd;
    GameState *gameState = (GameState*)malloc(sizeof(GameState));
    init_game(gameState);

    char input[10];
    int a, b, c, d;
    while (gameState->step < 100) {
        print_step(gameState);
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
        swap_number(gameState, a, b, c, d);



    }
//    int i = 0;
//    while (i<39){
//        cmd = ai_player_studentID(4, gameState->board);
//        if (cmd == 1){
//            cmd = (rand()%99)*101 + 1;
//        }
//        printf("%04d\n", cmd);
//        int *move = make_swap(cmd);
//        swap_number(gameState, move[0], move[1], move[2], move[3]);
//        i++;
//    }
    print_board(gameState);

    //打印得分函数
    printf("total score : %d\n", gameState->t_score);
    printf("mean score : %f", (float)gameState->t_score);



    return 0;

}