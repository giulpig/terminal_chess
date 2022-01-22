//Artico Giovanni n.matr. 2000178
#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece{

private:
    bool enpassant = false;

public:
    Pawn(int _row, int _col, Side s);
    void setPosition(int _row, int _col) override;
    std::set<std::pair<int, int>> getLegalMoves(const std::shared_ptr<ChessPiece>[8][8]) const override;
    Move moveType(int _row, int _col, const std::shared_ptr<ChessPiece>[8][8]) const override;
    void cancelEnpassant();
    bool getEnpassant() const;
};

#endif