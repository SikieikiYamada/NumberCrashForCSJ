
//game.h
#include "tinymt32.h"

#ifndef NUMBERCRASH_GAME_H
#define NUMBERCRASH_GAME_H

typedef struct {
    int board[100] ;
    int step ; // how many steps we have done
    int t_score ;

} GameState ;

void print_step(GameState *gameState);
void print_board(GameState *gameState);
void init_game(GameState *gameState);
void swap_number(GameState *gameState, int a,int b,int c,int d);
int check_if3(GameState *gameState);
int crash_matrix(GameState *gameState);
void pull_down(GameState *gameState);
void generate_new(GameState *gameState);
#endif //NUMBERCRASH_GAME_H
