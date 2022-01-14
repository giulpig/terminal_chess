#ifndef TOWER_H
#define TOWER_H

#include "ChessPiece.h"

class Tower : public ChessPiece{

private:
    //Role rol = Role::tower;

    void addLegalMoves(int dir, std::set<std::pair<int, int>>& legalMoves, const std::shared_ptr<ChessPiece>[8][8]) const;
    bool checkBounds(std::pair<int, int>) const;
public:
    Tower(int, int, Side);
    void setPosition(int _row, int _col) override;
    std::set<std::pair<int, int>> getLegalMoves(const std::shared_ptr<ChessPiece>[8][8]) const override;
    Moves moveType(int _row, int _col, const std::shared_ptr<ChessPiece>[8][8]) const override;
};

#endif