#ifndef PCPLAYER_CPP
#define PCPLAYER_CPP

#include"PcPlayer.h"
//only for testing
//#include<iostream>

using std::pair;

PcPlayer::PcPlayer(ChessBoard& _board, Side _side) : board{_board}, Player{_side, PlayerType::pc} {}

pair<pair<int, int>, pair<int, int>> PcPlayer::getMove() {
    bool findAMove = false;
    pair<pair<int, int>, pair<int, int>> movement;

    int remainPiece = board.nOfPieces(side);
    //std::cout << "pezzi rimanenti: " << remainPiece <<std::endl;

    do {

        int indexPlayer = rand() % remainPiece;

        //TODO get a set of possible movements for the player

        set<pair<int, int>> possMovement = board.getPossiblemovementsByIndex(indexPlayer, side);

        //if there is a possible movement for this player
        if(!possMovement.empty()) {

            //get the now position of the selected piece
            movement.first = board.getPosition(indexPlayer, side);

            //std::cout << "From piece" << movement.first.first << " " <<movement.first.second <<std::endl;
            //std::cout << "Possibili movimenti";
            //for(auto i : possMovement)
                //std::cout << i.first <<" " << i.second << " ";
            //std::cout <<std::endl;
            
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

char PcPlayer::getPromotion() const {
    char c = possPromotion[rand() % 4];
    return c;
}

#endif 
