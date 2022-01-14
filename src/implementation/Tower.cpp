#ifndef TOWER_CPP
#define TOWER_CPP

#include "Tower.h"

using std::make_pair;

Tower::Tower(int row, int column, Side sidePiece) : ChessPiece{row, column, sidePiece} {
    rol = Role::tower;
}

std::set<std::pair<int, int>> Tower::getLegalMoves(const std::shared_ptr<ChessPiece> board[8][8]) const {

    std::set<std::pair<int, int>> legalMoves {};
    
    //dir up - 1
    //dir right - 2
    //dir down - 3
    //dir left - 4
    
    for(int i = 1; i < 5; ++i)
        addLegalMoves(i, legalMoves, board);

    return legalMoves;
}

void Tower::addLegalMoves(int dir, std::set<std::pair<int, int>>& legalMoves, const std::shared_ptr<ChessPiece> board[8][8]) const {
    std::pair<int, int> pos = make_pair(getRow(), getCol());
    std::pair<int, int> additiveMovemnt;

    switch(dir) {
        case 1:
            additiveMovemnt = make_pair(-1, 0);
            break;
        case 2:
            additiveMovemnt = make_pair(0, 1);
            break;
        case 3:
            additiveMovemnt = make_pair(1, 0);
            break;
        case 4:
            additiveMovemnt = make_pair(0, -1);
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
        if(board[pos.first][pos.second] -> getRole() != Role::dummy) 
            isPossibleMove = false;
        else
            empty = true;

        //Add the control to the side of the player
        if(empty || getSide() != board[pos.first][pos.second] -> getSide())
            legalMoves.insert(pos);
    }

}

bool Tower::checkBounds(std::pair<int, int> pos) const {
    if(pos.first < 0 || pos.first >= 8 || pos.second < 0 || pos.second >= 8)
        return true;
    return false;
}

//MAYBE is not to override in this case, is better find a solution fot the PEDONE 
//(non so come si dice in inglese)

void Tower::setPosition(int _row, int _column) {
    //do not know if this is correct
    ChessPiece::setPosition(_row, _column);
}

Moves Tower::moveType(int _row, int _col, const std::shared_ptr<ChessPiece> board [8][8]) const {

    std::set<std::pair<int, int>> legalMoves = getLegalMoves(board);
    if(legalMoves.find({_row, _col}) != legalMoves.end()) {
        //we find the pair in the legalMoves
        return Moves::movement;
    } else
        return Moves::NaM;

}
#endif