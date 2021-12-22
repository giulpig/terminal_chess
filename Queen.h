#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"

using std::unique_ptr;

class Queen : public ChessPiece{
private:
    role rol = role::queen;
public:
    void setPosition(int _row, int _col) override;
    set<pair<int, int>> getLegalMoves(shared_ptr<ChessPiece>[8][8]) override;
    move moveType(int _row, int _col, shared_ptr<ChessPiece>[8][8]) override;
};

#endif