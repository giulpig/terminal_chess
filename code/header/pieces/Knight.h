//Artico Giovanni n.matr. 2000178
#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight : public ChessPiece{

public:
    Knight(int, int, Side);
    void setPosition(int _row, int _col) override;
    std::set<std::pair<int, int>> getLegalMoves(const std::shared_ptr<ChessPiece>[8][8]) const override;
    Moves moveType(int _row, int _col, const std::shared_ptr<ChessPiece>[8][8]) const override;
};

#endif