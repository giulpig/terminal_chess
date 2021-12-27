#ifndef DUMMY_H
#define DUMMY_H
#include "ChessPiece.h"
//class used to check for empty spaces, has no other use. like my condoms in the wallet
class Dummy : public ChessPiece{
    public:
    Dummy() : ChessPiece{-1, -1, side::white}{rol = role::dummy;}
    void setPosition(int _row, int _col) override;
    set<pair<int, int>> getLegalMoves(const shared_ptr<ChessPiece>[8][8]) const override;
    move moveType(int _row, int _col, const shared_ptr<ChessPiece>[8][8]) const override;
};
#endif