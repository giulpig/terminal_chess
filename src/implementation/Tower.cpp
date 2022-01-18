#ifndef TOWER_CPP
#define TOWER_CPP

#include "Tower.h"

using std::make_pair;

Tower::Tower(int row, int column, Side sidePiece) : DirectionalPieces{row, column, sidePiece, Role::tower} {}

std::set<std::pair<int, int>> Tower::getLegalMoves(const std::shared_ptr<ChessPiece> board[8][8]) const {

    std::set<std::pair<int, int>> legalMoves {};
    std::pair<int, int> dir;
    int i;
    
    // Iterate through each possible direction and foreach
    // add all the possible moves that could be done to a set
    for(i = 1; i < 9; ++i) {
        // Depends on the selected dir this switch would select an appropiate increment
        switch(i) {
            case 1:
                dir = make_pair(-1, 0);
                break;
            case 2:
                dir = make_pair(0, 1);
                break;
            case 3:
                dir = make_pair(1, 0);
                break;
            case 4:
                dir = make_pair(0, -1);
                break;
        }

        addLegalMoves(dir, legalMoves, board);

    }

    //now the set contains all the possible movements of the piece
    return legalMoves;
}

#endif