#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<memory>
#include"Enums.h"
#include"Player.h"
#include"HumanPlayer.h"
#include"PcPlayer.h"
#include"ChessBoard.h"

class Game {
    private:
        GameType gType;
        vector<std::unique_ptr<Player>> players{2};
        ChessBoard board;
        void printChessBoard();
        int maxMovesPc = 1;

    public:
        Game(GameType);

        // do not know if I have to return something for the main
        void play();

};

#endif

// formato upgrade
/*
 * A2 A4
 * 
 * -promotion k B3 B7
 * -castling
 * -enpassant 
 */

/*
 * Classe log 
 *
 *  private:
 *      nameFile;
 *
 *  public:
 *      log()
 *      log(stirng)
 *
 *      stampo questo nel GAME
 *      "Inserisci nome log (lascia vuoto per nome standard = 'logGame.txt')"
 *
 *      logMov(stirng);
 *
 */
