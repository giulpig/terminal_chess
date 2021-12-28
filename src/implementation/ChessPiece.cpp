#ifndef CHESSPIECE_CPP
#define CHESSPIECE_CPP

#include "../header/ChessPiece.h"

ChessPiece::ChessPiece(int _row, int _col, side s){
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

void ChessPiece::setPosition(int _row, int _col){
    location.first = _row;
    location.second = _col;
    moved = true;
}
role ChessPiece::getRole() const{
    return rol;
}

bool ChessPiece::isMoved() const{
    return moved;
}

side ChessPiece::getSide() const{
    return color;
}

#endif