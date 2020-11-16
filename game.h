
//game.h

#ifndef NUMBERCRASH_GAME_H
#define NUMBERCRASH_GAME_H

typedef struct {
    int board[100] ;
    int step ; // how many steps we have done
    int t_score ;

} GameState ;
void print_board(GameState *gameState);
void init_game(GameState *gameState);
void swap_number(int a,int b,int c,int d,GameState *gameState);
int check_if3(GameState *gameState);
#endif //NUMBERCRASH_GAME_H
