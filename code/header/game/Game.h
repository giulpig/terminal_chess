/**
 * Gabriele Miotti
 * 
 * N. Matricola : 2000165
 */

#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<memory>
#include<vector>
#include <sys/time.h>
#include"Enums.h"
#include"Player.h"
#include"HumanPlayer.h"
#include"PcPlayer.h"
#include"ChessBoard.h"
#include"Log.h"

class Game {
    private:
        // Type of the game, used to undertand the type of the players
        GameType gType;

        // Store a pointer to the base class of the players
        std::vector<std::unique_ptr<Player>> players{2};

        ChessBoard board;
        Log log;

        /*
        ** Print on screen the status of the board
        ** with some spaces before and after
        */
        void printChessBoard();

        // Max moves in a pc vs pc game
        int maxMovesPc = 1;

        /*
        ** Get a desired name for the log, if empty use a default one
        */
        std::string getFileLogName();

        /*
        ** Get the max number of moves that a cc game could do 
        */
        void setMaxMoves();

    public:

        // Constructor specifing the type of the game
        Game(GameType);

        //Game(Game&) = delete;
        //Game& operator=(const Game& g) = delete;

        /* 
        ** Main method that will manage an entire game between the player
        ** specified in the constructor
        */
        void play();
 
};

#endif


