#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

using std::unique_ptr;

class Knight : public ChessPiece{

public:
    Knight(int, int, Side);
    void setPosition(int _row, int _col) override;
    set<pair<int, int>> getLegalMoves(const shared_ptr<ChessPiece>[8][8]) const override;
    Moves moveType(int _row, int _col, const shared_ptr<ChessPiece>[8][8]) const override;
};

#endif