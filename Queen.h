#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"

using std::unique_ptr;

class Queen : public ChessPiece{
private:
    role rol = role::queen;
    //Maybe usefull
    //But for now seems a good think to simplify the code
    void addLegalMoves(int dir, set<pair<int, int>>& legalMoves, shared_ptr<ChessPiece>[8][8]) const;
    bool checkBounds(pair<int, int>) const;
public:
    void setPosition(int _row, int _col) override;
    //wht not &?
    set<pair<int, int>> getLegalMoves(shared_ptr<ChessPiece>[8][8]) const override;
    move moveType(int _row, int _col, shared_ptr<ChessPiece>[8][8]) const override;
};

#endif
