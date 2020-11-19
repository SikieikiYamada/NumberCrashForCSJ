//main.c
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "tinymt32.h"
#include <string.h>

int main() {
    init_game();

    char input[10];
    int a, b, c, d;
    while (call_step() < 100) {
        print_board();
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
        swap_number(a, b, c, d);



    }
    //打印得分函数
    printf("total score : %d\n", call_score());
    printf("mean score : %f", (float)call_score());



    return 0;

}