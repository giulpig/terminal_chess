#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"

using std::unique_ptr;

class Queen : public ChessPiece{
private:
    //Maybe usefull
    //But for now seems a good think to simplify the code
    void addLegalMoves(int dir, set<pair<int, int>>& legalMoves, const shared_ptr<ChessPiece>[8][8]) const;
    bool checkBounds(pair<int, int>) const;
public:
    Queen(int row, int column, side sidePiece);
    //Queen(Queen&);
    void setPosition(int _row, int _col) override;
    //wht not &?
    set<pair<int, int>> getLegalMoves(const shared_ptr<ChessPiece>[8][8]) const override;
    move moveType(int _row, int _col, const shared_ptr<ChessPiece>[8][8]) const override;
};

#endif
