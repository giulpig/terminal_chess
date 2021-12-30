#ifndef PCPLAYER_CPP
#define PCPLAYER_CPP

#include"PcPlayer.h"

using std::pair;

PcPlayer::PcPlayer(const ChessBoard& _board, Side _side) : board{_board}, side{_side} {}

pair<pair<int, int>, pair<int, int>> PcPlayer::getMove() const {
    bool findAMove = false;
    pair<pair<int, int>, pair<int, int>> movement;

    do {

        int indexPlayer = rand() % 20;

        //TODO get a set of possible movements for the player

        set<pair<int, int>> possMovement = board.getPossiblemovementsByIndex(indexPlayer, side);

        //if there is a possible movement for this player
        if(!possMovement.empty()) {

            //get the now position of the selected piece
            movement.first = getPosition(indexPlayer, side);
            
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

