#ifndef CHESSPIECE_CPP
#define CHESSPIECE_CPP

#include "ChessPiece.h"

//temp
#include <iostream>

ChessPiece::ChessPiece(int _row, int _col, Side s){
    location.first = _row;
    location.second = _col;
    color = s;
}

ChessPiece::ChessPiece(const ChessPiece& o){
    
}

int ChessPiece::getRow() const{
        return location.first;
    }

int ChessPiece::getCol() const{
    return location.second;
}

pair<int, int> ChessPiece::getPosition() const{
    return {location.first, location.second};
}

void ChessPiece::setPosition(int _row, int _col){
    location.first = _row;
    location.second = _col;
    moved = true;
}
Role ChessPiece::getRole() const{
    return rol;
}

bool ChessPiece::isMoved() const{
    return moved;
}

Side ChessPiece::getSide() const{
    return color;
}
bool ChessPiece::checkBoundaries(int a, int b) const{
    return a < 8 && a >= 0 && b < 8 && b >= 0;
}
bool ChessPiece::isDummy(const shared_ptr<ChessPiece> mat[8][8], int a, int b) const{
    return mat[a][b]->getRole() == Role::dummy;
}
bool ChessPiece::isOppositeSide(const shared_ptr<ChessPiece> mat[8][8], int a, int b) const{
    return mat[a][b]->getSide() != getSide();
}
#endif