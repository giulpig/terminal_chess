#ifndef PCPLAYER_CPP
#define PCPLAYER_CPP

#include"PcPlayer.h"
//only for testing
#include<iostream>

using std::pair;

PcPlayer::PcPlayer(const ChessBoard& _board, Side _side) : board{_board}, Player{_side} {}

pair<pair<int, int>, pair<int, int>> PcPlayer::getMove() const {
    bool findAMove = false;
    pair<pair<int, int>, pair<int, int>> movement;

    int remainPiece = board.nOfPieces(side);
    std::cout << "pezzi rimanenti: " << remainPiece <<std::endl;

    do {

        int indexPlayer = rand() % remainPiece;

        //TODO get a set of possible movements for the player

        set<pair<int, int>> possMovement = board.getPossiblemovementsByIndex(indexPlayer, side);

        //if there is a possible movement for this player
        if(!possMovement.empty()) {

            //get the now position of the selected piece
            movement.first = board.getPosition(indexPlayer, side);
            
            //select one movement from the set
            int randMov = rand() % possMovement.size();
            std::set<pair<int, int>>::iterator it = possMovement.begin();
            std::advance(it, randMov);

            movement.second = *it;

            findAMove = true;
            
        }


    } while(!findAMove);

    return movement;
}

#endif 

