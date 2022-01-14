#ifndef KNIGHT_CPP
#define KNIGHT_CPP

#include "Knight.h"

Knight::Knight(int _row, int _col, Side s) : ChessPiece(_row, _col, s){
    rol = Role::knight;
}

void Knight::setPosition(int _row, int _col){
    ChessPiece::setPosition(_row, _col);
}

std::set<std::pair<int, int>> Knight::getLegalMoves(const std::shared_ptr<ChessPiece> mat[8][8]) const{
    std::set<std::pair<int, int>> s;
    for(int i = -2; i <= 2; i ++){
        for(int j = -2; j <= 2; j ++){
            if(i != 0 && j != 0){
                //the move can be done only if it moves by two positions in one direction and one in the other
                if(((i == -2 || i == 2) && (j == - 1 || j == 1)) || ((j == -2 || j == 2) && (i == - 1 || i == 1))){
                    if(checkBoundaries(getRow() + i, getCol() + j)){
                        if(isOppositeSide(mat, getRow() + i, getCol() + j) || isDummy(mat, getRow() + i, getCol() + j)){
                            s.insert({getRow() + i, getCol() + j});
                        }
                    }
                }
            }
        }
    }
    return s;
}

Moves Knight::moveType(int _row, int _col, const std::shared_ptr<ChessPiece> mat[8][8]) const{
    std::set<std::pair<int, int>> s = getLegalMoves(mat);
    if(s.find({_row, _col}) == s.end()){
        return Moves::NaM;
    }
    else{
        return Moves::movement;
    }
}
#endif