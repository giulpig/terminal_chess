#ifndef KNIGHT_CPP
#define KNIGHT_CPP

#include "Knight.h"

Knight::Knight(int _row, int _col, Side s) : ChessPiece(_row, _col, s){
    rol = Role::knight;
}
void Knight::setPosition(int _row, int _col){
    ChessPiece::setPosition(_row, _col);
}
set<pair<int, int>> Knight::getLegalMoves(const shared_ptr<ChessPiece> mat[8][8]) const{
    set<pair<int, int>> s;
    for(int i = -2; i <= 2; i ++){
        for(int j = -2; j <= 2; j ++){
            if(i != 0 && j != 0){
                if(((i == -2 || i == 2) && (j == - 1 || j == 1)) || ((j == -2 || j == 2) && (i == - 1 || i == 1))){
                    if(getRow() + i < 8 && getRow() + i >= 0 && getCol() + j < 8 && getCol() + j >= 0){
                        if((*(mat[getRow() + i][getCol() + j])).getSide() != getSide() || (*(mat[getRow() + i][getCol() + j])).getRole() == Role::dummy){
                            s.insert({getRow() + i, getCol() + j});
                        }
                    }
                }
            }
        }
    }
    return s;
}
Moves Knight::moveType(int _row, int _col, const shared_ptr<ChessPiece> mat[8][8]) const{
    set<pair<int, int>> s = getLegalMoves(mat);
    if(s.find({_row, _col}) == s.end()){
        return Moves::NaM;
    }
    else{
        return Moves::movement;
    }
}
#endif