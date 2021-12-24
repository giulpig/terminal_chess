#ifndef TOWER_H
#define TOWER_H

#include "ChessPiece.h"

class Tower : public ChessPiece{

private:
    role rol = role::tower;

public:
    void setPosition(int _row, int _col) override;
    set<pair<int, int>> getLegalMoves(shared_ptr<ChessPiece>[8][8]) const override;
    move moveType(int _row, int _col, shared_ptr<ChessPiece>[8][8]) const override;
};

#endif