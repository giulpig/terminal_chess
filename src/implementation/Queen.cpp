#ifndef QUEEN_CPP
#define QUEEN_CPP

#include "Queen.h"

using std::make_pair;

Queen::Queen(int row, int column, side sidePiece) : ChessPiece{row, column, sidePiece} {
    rol = role::queen;
}
/*
Queen::Queen(Queen& piece) : ChessPiece{piece.getRow(), piece.getCol(), piece.getSide()} {
    rol = role::queen;
}
*/

set<pair<int, int>> Queen::getLegalMoves(const shared_ptr<ChessPiece> board[8][8]) const {

    set<pair<int, int>> legalMoves {};
    
    //dir up - 1
    //dir up - right - 2
    //dir right - 3
    //dir down - right - 4
    //dir down - 5
    //dir down - left - 6
    //dir left - 7 
    //dir up - left - 8
    
    for(int i = 1; i < 9; ++i)
        addLegalMoves(i, legalMoves, board);

    return legalMoves;
}

void Queen::addLegalMoves(int dir, set<pair<int, int>>& legalMoves, const shared_ptr<ChessPiece> board[8][8]) const {
    pair<int, int> pos = make_pair(getRow(), getCol());
    pair<int, int> additiveMovemnt;


    switch(dir) {
        case 1:
            additiveMovemnt = make_pair(-1, 0);
            break;
        case 2:
            additiveMovemnt = make_pair(-1, 1);
            break;
        case 3:
            additiveMovemnt = make_pair(0, 1);
            break;
        case 4:
            additiveMovemnt = make_pair(1, 1);
            break;
        case 5:
            additiveMovemnt = make_pair(1, 0);
            break;
        case 6:
            additiveMovemnt = make_pair(1, -1);
            break;
        case 7:
            additiveMovemnt = make_pair(0, -1);
            break;
        case 8:
            additiveMovemnt = make_pair(-1, -1);
            break;
    }


    bool isPossibleMove = true;

    while(isPossibleMove) {

        //do not know id this work
        //otherwise have to sum 1 and 2
        pos.first += additiveMovemnt.first;
        pos.second += additiveMovemnt.second;
        // WE HAVE TO MODIFY THE STD LIBRARY AND ADD THIS THING
        //pos += additiveMovemnt;

        //check if the player has finished the board
        if(checkBounds(pos)){
            isPossibleMove = false;
            continue;
        }

        bool empty = false;
        if(board[pos.first][pos.second] -> getRole() != role::dummy) 
            isPossibleMove = false;
        else
            empty = true;

        //Add the control to the side of the player
        if(empty || getSide() != board[pos.first][pos.second] -> getSide())
            legalMoves.insert(pos);
    }

}

bool Queen::checkBounds(pair<int, int> pos) const {
    if(pos.first < 0 || pos.first >= 8 || pos.second < 0 || pos.second >= 8)
        return false;
    return true;
}

//MAYBE is not to override in this case, is better find a solution fot the PEDONE 
//(non so come si dice in inglese)

void Queen::setPosition(int _row, int _column) {
    //do not know if this is correct
    ChessPiece::setPosition(_row, _column);
}

move Queen::moveType(int _row, int _col, const shared_ptr<ChessPiece> board [8][8]) const {

    set<pair<int, int>> legalMoves = getLegalMoves(board);
    if(legalMoves.find({_row, _col}) != legalMoves.end()) {
        //we find the pair in the legalMoves
        return move::movement;
    } else
        return move::NaM;

}


#endif
