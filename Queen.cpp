#ifndef QUEEN_CPP
#define QUEEN_CPP

#include "Queen.h"




set<pair<int, int>>Queen::getLegalMoves(shared_ptr<ChessPiece>[8][8] board) const {

    set<pair<int, int>> legalMoves ();
    
    //dir up - 1
    //dir up - right - 2
    //dir right - 3
    //dir down - right - 4
    //dir down - 5
    //dir down - left - 6
    //dir left - 7 
    //dir up - left - 8
    
    for(int i=0; i < 9; ++i)
        addLegalMoves(i, legalMoves, board);

    return legalMoves;
}

void Queen::addLegalMoves(int dir, set<pair<int, int>>& legalMoves, shared_ptr<ChessPiece>[8][8]& board) {
    pair<int, int> pos = make_pair{getRow(), getCol()};
    pair<int, int> additiveMovemnt;


    switch(dir) {
        case 1:
            additiveMovemnt = make_pair{-1, 0};
            break;
        case 2:
            additiveMovemnt = make_pair{-1, 1};
            break;
        case 3:
            additiveMovemnt = make_pair{0, 1};
            break;
        case 4:
            additiveMovemnt = make_pair{1, 1};
            break;
        case 5:
            additiveMovemnt = make_pair{1, 0};
            break;
        case 6:
            additiveMovemnt = make_pair{1, -1};
            break;
        case 7:
            additiveMovemnt = make_pair{0, -1};
            break;
        case 8:
            additiveMovemnt = make_pair{-1, -1};
            break;
    }


    bool isPossibleMove = true;

    while(isPossibleMove) {

        //do not know id this work
        //otherwise have to sum 1 and 2
        pos += additiveMovemnt;

        if(board[pos.first][pos.second] -> getRole() != role::dummy) 
            isPossibleMove = false;
        legalMoves.insert(pos);
    }

}

#endif
