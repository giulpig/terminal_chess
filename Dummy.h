#ifndef DUMMY_H
#define DUMMY_H
#include "ChessPiece.h"
//class used to check for empty spaces, has no other use. like my condoms in the wallet
class Dummy : public ChessPiece{
    private:
    role rol = role::dummy;

    public:
    void setPosition(int _row, int _col) override;
    set<pair<int, int>> getLegalMoves(shared_ptr<ChessPiece>[8][8]) override;
    move moveType(int _row, int _col, shared_ptr<ChessPiece>[8][8]) override;
};
#endif