#ifndef QUEEN_H
#define QUEEN_H

#include "DirectionalPieces.h"

class Queen : public DirectionalPieces{

    public:

        /*
        ** Constructor will call the base class, DirectionalPieces
        ** passing the right role
        */
        Queen(int row, int column, Side sidePiece);

        /* 
        ** Return all the possible movements of the piece
        ** following his rules
        */
        std::set<std::pair<int, int>> getLegalMoves(const std::shared_ptr<ChessPiece>[8][8]) const override;
};

#endif
