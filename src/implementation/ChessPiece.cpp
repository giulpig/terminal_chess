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

#endif