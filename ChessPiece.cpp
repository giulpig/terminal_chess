#ifndef CHESSPIECE_CPP
#define CHESSPIECE_CPP
#include "ChessPiece.h"
ChessPiece::ChessPiece(int _row, int _col, side s, role r){
    location.first = _row;
    location.second = _col;
    color = s;
    rol = r;
}
int ChessPiece::getRow(){
        return location.first;
    }
int ChessPiece::getCol(){
    return location.second;
}
void ChessPiece::move(int _row, int _col, shared_ptr<ChessPiece> s[8][8]){
    if(isLegalMove(_row, _col, s)){
        location.first = _row;
        location.second = _col;
    }
    else{
        throw IllegalMove{};
    }
}
void ChessPiece::doPossibleMove(int _row, int _col, shared_ptr<ChessPiece> s[8][8]){
    precmove.first = location.first;
    precmove.second = location.second;
    move(_row, _col, s);
}
void ChessPiece::undoPossibleMove(){
    if(precmove.first < 0){
        throw NoPossibleMoveSet{};
    }
    location.first = precmove.first;
    location.second = precmove.second;
    precmove.first = -1;
    precmove.second = -1;
}
role ChessPiece::getRole(){
    return rol;
}
#endif