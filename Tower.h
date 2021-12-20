#ifndef TOWER_H
#define TOWER_H

#include "ChessPiece.h"

class Tower : public ChessPiece{

private:
    bool notMoved = true;

public:
    void doPossibleMove(int _row, int _col, shared_ptr<ChessPiece>[8][8]) override;
    void undoPossibleMove() override;
    void move(int _row, int _col, shared_ptr<ChessPiece>[8][8]) override;
    vector<pair<int, int>> getLegalMoves(shared_ptr<ChessPiece>[8][8]) override;
    bool isLegalMove(int _row, int _col, shared_ptr<ChessPiece>[8][8]) override;
    bool IsMoved();
};

#endif