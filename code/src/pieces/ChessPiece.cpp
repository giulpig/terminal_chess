//Artico Giovanni n.matr. 200178
#ifndef CHESSPIECE_CPP
#define CHESSPIECE_CPP

#include "ChessPiece.h"

ChessPiece::ChessPiece(int _row, int _col, Side s){
    location.first = _row;
    location.second = _col;
    color = s;
}

int ChessPiece::getRow() const{
        return location.first;
    }

int ChessPiece::getCol() const{
    return location.second;
}

std::pair<int, int> ChessPiece::getPosition() const{
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
bool ChessPiece::checkBoundaries(std::pair<int, int> pos) const{
    return pos.first < 8 && pos.first >= 0 && pos.second < 8 && pos.second >= 0;
}
bool ChessPiece::isDummy(const std::shared_ptr<ChessPiece> mat[8][8], int a, int b) const{
    return mat[a][b]->getRole() == Role::dummy;
}
bool ChessPiece::isOppositeSide(const std::shared_ptr<ChessPiece> mat[8][8], int a, int b) const{
    return mat[a][b]->getSide() != getSide();
}
#endif