#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

using std::unique_ptr;

class Bishop : public ChessPiece{
private:
    //Role rol = Role::bishop;
    void addLegalMoves(int dir, std::set<std::pair<int, int>>& legalMoves, const std::shared_ptr<ChessPiece>[8][8]) const;
    bool checkBounds(std::pair<int, int>) const;
public:
    Bishop(int row, int column, Side sidePiece);
    void setPosition(int _row, int _col) override;
    std::set<std::pair<int, int>> getLegalMoves(const std::shared_ptr<ChessPiece>[8][8]) const override;
    Moves moveType(int _row, int _col, const std::shared_ptr<ChessPiece>[8][8]) const override;
};
#endif