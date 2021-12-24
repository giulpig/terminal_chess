#ifndef DUMMY_CPP
#define DUMMY_CPP
#include "Dummy.h"
void Dummy::setPosition(int _row, int _col){}
set<pair<int, int>> Dummy::getLegalMoves(shared_ptr<ChessPiece>[8][8]){
    set<pair<int,int>> s;
    return s;
}
move Dummy::moveType(int _row, int _col, shared_ptr<ChessPiece>[8][8]){
    return move::NaM;
}

#endif