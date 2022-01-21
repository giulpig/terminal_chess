/**
 * Gabriele Miotti
 * 
 * N. Matricola : 2000165
 */

#ifndef BISHOP_CPP
#define BISHOP_CPP

#include "Bishop.h"

using std::make_pair;

Bishop::Bishop(int row, int column, Side sidePiece) : DirectionalPieces{row, column, sidePiece, Role::bishop} {}

std::set<std::pair<int, int>> Bishop::getLegalMoves(const std::shared_ptr<ChessPiece> board[8][8]) const {

    std::set<std::pair<int, int>> legalMoves {};
    std::pair<int, int> dir;
    int i;
    
    // Iterate through each possible direction and
    // foreach add all the possible moves that could be done to a set
    // For each direction the movement is create adding always the same increment to a starting position
    for(i = 1; i < 5; ++i) {
        // Depends on the selected dir this switch would select an appropiate increment
        switch(i) {
            case 1:
                dir = make_pair(-1, 1);
                break;
            case 2:
                dir = make_pair(1, 1);
                break;
            case 3:
                dir = make_pair(1, -1);
                break;
            case 4:
                dir = make_pair(-1, -1);
                break;
        }

        addLegalMoves(dir, legalMoves, board);

    }

    //now the set contains all the possible movements of the piece
    return legalMoves;
}

#endif