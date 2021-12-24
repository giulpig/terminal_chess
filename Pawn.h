#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

using std::unique_ptr;

class Pawn : public ChessPiece{

private:
    bool enpassant = false;
    role rol = role::pawn;

public:
    Pawn(int _row, int _col, side s);
    void setPosition(int _row, int _col) override;
    set<pair<int, int>> getLegalMoves(shared_ptr<ChessPiece>[8][8]) const override;
    move moveType(int _row, int _col, shared_ptr<ChessPiece>[8][8]) const override;
    void cancelEnpassant();
    bool getEnpassant() const;
};

#endif