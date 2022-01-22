/**
 * Gabriele Miotti
 * 
 * N. Matricola : 2000165
 */

#ifndef DIRECTIONALPIECES_CPP
#define DIRECTIONALPIECES_CPP

#include "DirectionalPieces.h"

DirectionalPieces::DirectionalPieces(int row, int column, Side sidePiece, Role role) : ChessPiece{row, column, sidePiece} {
    // Set the role of the piece
    rol = role;
}

void DirectionalPieces::addLegalMoves(std::pair<int, int> dir, std::set<std::pair<int, int>>& legalMoves, const std::shared_ptr<ChessPiece> board[8][8]) const {
    // Create a pair that is used to move in the board
    // initially the position is where the piece is on the current board
    std::pair<int, int> pos = std::make_pair(getRow(), getCol());

    bool isPossibleMove = true;

    // Now start a loop and check all the boxes in the selected direction
    while(isPossibleMove) {

        // Add the increment to the position
        pos.first += dir.first;
        pos.second += dir.second;

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

void DirectionalPieces::setPosition(int _row, int _column) {
    ChessPiece::setPosition(_row, _column);
}


Move DirectionalPieces::moveType(int _row, int _col, const std::shared_ptr<ChessPiece> board [8][8]) const {

    std::set<std::pair<int, int>> legalMoves = getLegalMoves(board);
    if(legalMoves.find({_row, _col}) != legalMoves.end()) {
        //we find the pair in the legalMoves
        return Move::movement;
    } else
        return Move::NaM;

}

#endif