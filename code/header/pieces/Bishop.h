/**
 * Gabriele Miotti
 * 
 * N. Matricola : 2000165
 */

#ifndef BISHOP_H
#define BISHOP_H

#include "DirectionalPieces.h"

class Bishop : public DirectionalPieces{

    public:

        /*
        ** Constructor will call the base class, DirectionalPieces
        ** passing the right role
        */
        Bishop(int row, int column, Side sidePiece);

        /* 
        ** Return all the possible movements of the piece
        ** following his rules
        */
        std::set<std::pair<int, int>> getLegalMoves(const std::shared_ptr<ChessPiece>[8][8]) const override;
};

#endif