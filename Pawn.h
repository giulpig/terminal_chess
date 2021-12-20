#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

using std::unique_ptr;

class Pawn : public ChessPiece{

private:
    bool enpasse = false;
    bool notMoved = true;

public:
    void doPossibleMove(int _row, int _col, shared_ptr<ChessPiece>[8][8]) override;
    void undoPossibleMove() override;
    void move(int _row, int _col, shared_ptr<ChessPiece>[8][8]) override;
    vector<pair<int, int>> getLegalMoves(shared_ptr<ChessPiece>[8][8]) override;
    bool isLegalMove(int _row, int _col, shared_ptr<ChessPiece>[8][8]) override;
    unique_ptr<ChessPiece> upgrade(role);//non si può restituire un oggetto di classe virtuale pure ma un puntatore sì
};

#endif