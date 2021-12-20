#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

using std::unique_ptr;

class Knight : public ChessPiece{

public:
    void doPossibleMove(int _row, int _col, shared_ptr<ChessPiece>[8][8]) override;
    void undoPossibleMove() override;
    void move(int _row, int _col, shared_ptr<ChessPiece>[8][8]) override;
    vector<pair<int, int>> getLegalMoves(shared_ptr<ChessPiece>[8][8]) override;
    bool isLegalMove(int _row, int _col, shared_ptr<ChessPiece>[8][8]) override;
};

#endif