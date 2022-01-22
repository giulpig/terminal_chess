//Artico Giovanni n. matr. 2000178
#ifndef KING_H
#define KING_H

#include "ChessPiece.h"

class King : public ChessPiece{
public:
    King(int, int, Side);
    void setPosition(int _row, int _col) override;
    std::set<std::pair<int, int>> getLegalMoves(const std::shared_ptr<ChessPiece>[8][8]) const override;
    Moves moveType(int _row, int _col, const std::shared_ptr<ChessPiece>[8][8]) const override;
};

#endif