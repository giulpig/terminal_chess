#ifndef GAME_H
#define GAME_H

#include<iostream>
#include"Enums.h"
#include"Player.h"
#include"HumanPlayer.h"
#include"PcPlayer.h"
#include"ChessBoard.h"

class Game {
    private:
        vector<Player*> players{2};
        ChessBoard* board;
        void printChessBoard();

    public:
        Game(GameType);

        // do not know if I have to return something for the main
        void play();

};

#endif
