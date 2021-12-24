#ifndef KING_CPP
#define KING_CPP

#include "King.h"

King::King(int _row, int _col, side s) : ChessPiece(_row, _col, s) {
    rol = role::king;
}

void King::setPosition(int _row, int _col){
    ChessPiece::setPosition(_row, _col);
}
set<pair<int, int>> King::getLegalMoves(shared_ptr<ChessPiece> mat[8][8]) const{
    set<pair<int, int>> s;
    //around the king
    for(int i = -1; i <= 1; i ++){
        for(int j = -1; j <= 1; j ++){
            if((j == 0 && i == 0) || getCol() + j < 0 || getCol() + j >= 8 || getRow() + i < 0 || getRow() + i >= 8){
                continue;
            }
            else{
                if((*(mat[getRow() + i][getCol() + j])).getSide() != getSide()){
                    s.insert({getRow() + i, getCol() + j});
                }
            }
        }
    }
    //left castling
    if(!isMoved()){
        if(!(*(mat[getRow()][0])).isMoved()){
            bool free = true;
            for(int i = getCol() - 1; i > 0; i --){
                if((*(mat[getRow()][i])).getRole() != role::dummy){
                    free = false;
                    break;
                }
            }
            if(free){
                s.insert({getRow(), getCol() - 2});
            }
        }
    }
    //right castling
    if(!isMoved()){
        if(!(*(mat[getRow()][7])).isMoved()){
            bool free = true;
            for(int i = getCol() + 1; i < 7; i ++){
                if((*(mat[getRow()][i])).getRole() != role::dummy){
                    free = false;
                    break;
                }
            }
            if(free){
                s.insert({getRow(), getCol() + 2});
            }
        }
    }
    return s;
}
move King::moveType(int _row, int _col, shared_ptr<ChessPiece> mat[8][8]) const{
    if(_row < 0 || _row >= 8 || _col < 0 || _col >= 8){
        return move::NaM;
    }
    else if((_row != getRow() || _col != getCol()) && ((_row == getRow() - 1 || _row == getRow() + 1) || (_col == getCol() - 1 || _col == getCol() + 1))){
        if((*(mat[_row][_col])).getSide() != getSide()){
            return move::movement;
        }
    }
    //not around it, so castling
    else if(getRow() == _row){
        //right castling
        if(_col == getCol() + 2){
            bool free = true;
            for(int i = getCol() + 1; i < 7; i ++){
                if((*(mat[getRow()][i])).getRole() != role::dummy){
                    free = false;
                    break;
                }
            }
            if(free && !(*(mat[getRow()][7])).isMoved()){
                return move::castling;
            }
        }
        //left castling
        else if(_col == getCol() - 2){
            bool free = true;
            for(int i = getCol() - 1; i > 0; i --){
                if((*(mat[getRow()][i])).getRole() != role::dummy){
                    free = false;
                    break;
                }
            }
            if(free && !(*(mat[getRow()][0])).isMoved()){
                return move::castling;
            }
        }
    }
    else{
        return move::NaM;
    }
}
#endif