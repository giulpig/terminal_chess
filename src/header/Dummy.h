#ifndef DUMMY_H
#define DUMMY_H
#include "ChessPiece.h"
//class used to check for empty spaces, has no other use. like my condoms in the wallet
class Dummy : public ChessPiece{
    public:
    Dummy();
    void setPosition(int _row, int _col) override;
    std::set<std::pair<int, int>> getLegalMoves(const std::shared_ptr<ChessPiece>[8][8]) const override;
    Moves moveType(int _row, int _col, const std::shared_ptr<ChessPiece>[8][8]) const override;
};
#endif