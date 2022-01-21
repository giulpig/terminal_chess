/**
 * Gabriele Miotti
 * 
 * N. Matricola : 2000165
 */

#ifndef PCPLAYER_CPP
#define PCPLAYER_CPP

#include"PcPlayer.h"

using std::pair;

PcPlayer::PcPlayer(ChessBoard& _board, Side _side) : board{_board}, Player{_side, PlayerType::pc} {}

pair<pair<int, int>, pair<int, int>> PcPlayer::getMove() {
    bool findAMove = false;
    pair<pair<int, int>, pair<int, int>> movement;

    // Get the number of remaining pieces of the side
    int remainPiece = board.nOfPieces(side);

    do {

        // Select a random piece
        int indexPlayer = rand() % remainPiece;

        // Get all the possible movements of the random piece
        std::set<pair<int, int>> possMovement = board.getPossiblemovementsByIndex(indexPlayer, side);

        //if there is a possible movement for this player
        if(!possMovement.empty()) {

            //get the now position of the selected piece
            movement.first = board.getPosition(indexPlayer, side);

            //select one random movement from the set
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
