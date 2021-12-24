#ifndef KING_H
#define KING_H

#include "ChessPiece.h"

class King : public ChessPiece{
public:
    King(int, int, side);
    void setPosition(int _row, int _col) override;
    set<pair<int, int>> getLegalMoves(shared_ptr<ChessPiece>[8][8]) const override;
    move moveType(int _row, int _col, shared_ptr<ChessPiece>[8][8]) const override;
};

#endif