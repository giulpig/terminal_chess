#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

using std::unique_ptr;

class Bishop : public ChessPiece{
private:
    role rol = role::bishop;
    void addLegalMoves(int dir, set<pair<int, int>>& legalMoves, const shared_ptr<ChessPiece>[8][8]) const;
    bool checkBounds(pair<int, int>) const;
public:
    void setPosition(int _row, int _col) override;
    set<pair<int, int>> getLegalMoves(const shared_ptr<ChessPiece>[8][8]) const override;
    move moveType(int _row, int _col, const shared_ptr<ChessPiece>[8][8]) const override;
};
#endif