#ifndef CHESSPIECE_CPP
#define CHESSPIECE_CPP

#include "ChessPiece.h"

ChessPiece::ChessPiece(int _row, int _col, side s){
    location.first = _row;
    location.second = _col;
    color = s;
}

int ChessPiece::getRow(){
        return location.first;
    }

int ChessPiece::getCol(){
    return location.second;
}

void ChessPiece::setPosition(int _row, int _col){
    location.first = _row;
    location.second = _col;
    moved = true;
}
role ChessPiece::getRole(){
    return rol;
}

bool ChessPiece::isMoved(){
    return moved;
}
#endif