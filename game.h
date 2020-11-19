
//game.h
#include "tinymt32.h"

#ifndef NUMBERCRASH_GAME_H
#define NUMBERCRASH_GAME_H

typedef struct {
    int board[100] ;
    int step ; // how many steps we have done
    int t_score ;

} GameState ;

int call_step();
int call_score();
void print_board();
void init_game();
void swap_number(int a,int b,int c,int d);
int check_if3();
int crash_matrix();
void pull_down();
void generate_new();
#endif //NUMBERCRASH_GAME_H
