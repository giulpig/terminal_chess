#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

using std::unique_ptr;

class Bishop : public ChessPiece{
private:
    //Role rol = Role::bishop;
    void addLegalMoves(int dir, set<pair<int, int>>& legalMoves, const shared_ptr<ChessPiece>[8][8]) const;
    bool checkBounds(pair<int, int>) const;
public:
    Bishop(int row, int column, Side sidePiece);
    void setPosition(int _row, int _col) override;
    set<pair<int, int>> getLegalMoves(const shared_ptr<ChessPiece>[8][8]) const override;
    Moves moveType(int _row, int _col, const shared_ptr<ChessPiece>[8][8]) const override;
};
#endif