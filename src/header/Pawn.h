#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

using std::unique_ptr;

class Pawn : public ChessPiece{

private:
    bool enpassant = false;

public:
    Pawn(int _row, int _col, Side s);
    void setPosition(int _row, int _col) override;
    set<pair<int, int>> getLegalMoves(const shared_ptr<ChessPiece>[8][8]) const override;
    Moves moveType(int _row, int _col, const shared_ptr<ChessPiece>[8][8]) const override;
    void cancelEnpassant();
    bool getEnpassant() const;
};

#endif