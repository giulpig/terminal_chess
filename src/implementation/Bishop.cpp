#ifndef BISHOP_CPP
#define BISHOP_CPP

#include "Bishop.h"

using std::make_pair;

Bishop::Bishop(int row, int column, Side sidePiece) : ChessPiece{row, column, sidePiece} {
    rol = Role::bishop;
}

std::set<std::pair<int, int>> Bishop::getLegalMoves(const std::shared_ptr<ChessPiece> board[8][8]) const {

    std::set<std::pair<int, int>> legalMoves {};
    
    //dir up - right - 1
    //dir down - right - 2
    //dir down - left - 3
    //dir up - left - 4
    
    for(int i = 1; i < 5; ++i)
        addLegalMoves(i, legalMoves, board);

    return legalMoves;
}

void Bishop::addLegalMoves(int dir, std::set<std::pair<int, int>>& legalMoves, const std::shared_ptr<ChessPiece> board[8][8]) const {
    std::pair<int, int> pos = std::make_pair(getRow(), getCol());
    std::pair<int, int> additiveMovemnt;

    switch(dir) {
        case 1:
            additiveMovemnt = make_pair(-1, 1);
            break;
        case 2:
            additiveMovemnt = make_pair(1, 1);
            break;
        case 3:
            additiveMovemnt = make_pair(1, -1);
            break;
        case 4:
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
        if(!checkBoundaries(pos)){
            isPossibleMove = false;
            continue;
        }

        bool empty = false;
        if(board[pos.first][pos.second] -> getRole() != Role::dummy) 
            isPossibleMove = false;
        else
            empty = true;

        //Add the control to the side of the player
        if(empty || getSide() != board[pos.first][pos.second] -> getSide())
            legalMoves.insert(pos);
    }

}

//MAYBE is not to override in this case, is better find a solution fot the PEDONE 
//(non so come si dice in inglese)

void Bishop::setPosition(int _row, int _column) {
    //do not know if this is correct
    ChessPiece::setPosition(_row, _column);
}

Moves Bishop::moveType(int _row, int _col, const std::shared_ptr<ChessPiece> board [8][8]) const {

    std::set<std::pair<int, int>> legalMoves = getLegalMoves(board);
    if(legalMoves.find({_row, _col}) != legalMoves.end()) {
        //we find the pair in the legalMoves
        return Moves::movement;
    } else
        return Moves::NaM;

}
#endif