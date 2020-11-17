
//game.h
#include "tinymt32.h"

#ifndef NUMBERCRASH_GAME_H
#define NUMBERCRASH_GAME_H

typedef struct {
    int board[100] ;
    int step ; // how many steps we have done
    int t_score ;
    tinymt32_t tinymt32;
    tinymt32_t *random;
    uint32_t seed;

} GameState ;
void print_board(GameState *gameState);
void init_game(GameState *gameState);
void swap_number(int a,int b,int c,int d,GameState *gameState);
int check_if3(GameState *gameState);
int crash_matrix(GameState *gameState);
void pull_down(GameState *gameState);
void generate_new(GameState *gameState);
#endif //NUMBERCRASH_GAME_H
