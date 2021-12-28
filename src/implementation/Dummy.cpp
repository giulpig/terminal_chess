#ifndef DUMMY_CPP
#define DUMMY_CPP

#include "../header/Dummy.h"

void Dummy::setPosition(int _row, int _col){}

set<pair<int, int>> Dummy::getLegalMoves(const shared_ptr<ChessPiece>[8][8]) const{
    set<pair<int,int>> s;
    return s;
}

Moves Dummy::moveType(int _row, int _col, const shared_ptr<ChessPiece>[8][8]) const{
    return Moves::NaM;
}

#endif