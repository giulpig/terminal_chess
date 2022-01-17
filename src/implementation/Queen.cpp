#ifndef QUEEN_CPP
#define QUEEN_CPP

#include "Queen.h"

using std::make_pair;

Queen::Queen(int row, int column, Side sidePiece) : ChessPiece{row, column, sidePiece} {
    // Set the role of the piece
    rol = Role::queen;
}


std::set<std::pair<int, int>> Queen::getLegalMoves(const std::shared_ptr<ChessPiece> board[8][8]) const {

    std::set<std::pair<int, int>> legalMoves {};

    
    // Iterate through each possible direction and foreach
    // add all the possible moves that could be done to a set
    for(int i = 1; i < 9; ++i)
        addLegalMoves(i, legalMoves, board);

    //now the set contains all the possible movements of the piece
    return legalMoves;
}

void Queen::addLegalMoves(int dir, std::set<std::pair<int, int>>& legalMoves, const std::shared_ptr<ChessPiece> board[8][8]) const {
    // Create a pair that is used to move in the board
    // initially the position is where the piece is on the current board
    std::pair<int, int> pos = make_pair(getRow(), getCol());

    // For each direction the movement is create adding always the same increment
    std::pair<int, int> additiveMovemnt;

    // Depends on the selected dir this switch would select an appropiate increment
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

    // Now start a loop and check all the boxes in the selected direction
    while(isPossibleMove) {

        // Add the increment to the position
        pos.first += additiveMovemnt.first;
        pos.second += additiveMovemnt.second;

        //check if the player has finished the board
        if(!checkBoundaries(pos)){
            isPossibleMove = false;
            continue;
        }

        // Verity if the box is empty or not
        // if it is the movement is ok
        // otherwise in any case the piece can't go any further
        bool empty = false;
        if(board[pos.first][pos.second] -> getRole() != Role::dummy) 
            isPossibleMove = false;
        else
            empty = true;

        // If the box is empty the movement is surely possible
        // If the box contain a player there are two possibilities: 
        //  - it contains a piece of the same side, i can't go on that
        //  - the box contains an opposite side player, that's a possible movement
        if(empty || getSide() != board[pos.first][pos.second] -> getSide())
            legalMoves.insert(pos);
    }

}

//MAYBE is not to override in this case, is better find a solution fot the PEDONE 
//(non so come si dice in inglese)

void Queen::setPosition(int _row, int _column) {
    //do not know if this is correct
    ChessPiece::setPosition(_row, _column);
}

Moves Queen::moveType(int _row, int _col, const std::shared_ptr<ChessPiece> board [8][8]) const {

    std::set<std::pair<int, int>> legalMoves = getLegalMoves(board);
    if(legalMoves.find({_row, _col}) != legalMoves.end()) {
        //we find the pair in the legalMoves
        return Moves::movement;
    } else
        return Moves::NaM;

}


#endif
