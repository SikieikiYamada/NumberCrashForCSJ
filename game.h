//
// Created by Yamada Youkai on 2020/11/11.
//

#ifndef NUMBERCRASH_GAME_H
#define NUMBERCRASH_GAME_H

typedef struct {
    int board[100] ;
    int step ; // how many steps we have done
    int t_score ;

} GameState ;
void print_board(GameState *gameState);
void init_game(GameState *gameState);

#endif //NUMBERCRASH_GAME_H
