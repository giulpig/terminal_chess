#ifndef KING_H
#define KING_H

#include "ChessPiece.h"

class King : public ChessPiece{
public:
    King(int, int, Side);
    void setPosition(int _row, int _col) override;
    set<pair<int, int>> getLegalMoves(const shared_ptr<ChessPiece>[8][8]) const override;
    Moves moveType(int _row, int _col, const shared_ptr<ChessPiece>[8][8]) const override;
};

#endif