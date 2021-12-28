#ifndef KING_CPP
#define KING_CPP

#include "../header/King.h"

King::King(int _row, int _col, Side s) : ChessPiece(_row, _col, s) {
    rol = Role::king;
}

void King::setPosition(int _row, int _col){
    ChessPiece::setPosition(_row, _col);
}
set<pair<int, int>> King::getLegalMoves(const shared_ptr<ChessPiece> mat[8][8]) const{
    set<pair<int, int>> s;
    //around the king
    for(int i = -1; i <= 1; i ++){
        for(int j = -1; j <= 1; j ++){
            if((j == 0 && i == 0) || getCol() + j < 0 || getCol() + j >= 8 || getRow() + i < 0 || getRow() + i >= 8){
                continue;
            }
            else{
                if((*(mat[getRow() + i][getCol() + j])).getSide() != getSide() || (*(mat[getRow() + i][getCol() + j])).getRole() == Role::dummy){
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
                if((*(mat[getRow()][i])).getRole() != Role::dummy){
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
                if((*(mat[getRow()][i])).getRole() != Role::dummy){
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
Moves King::moveType(int _row, int _col, const shared_ptr<ChessPiece> mat[8][8]) const{
    set<pair<int, int>> s = getLegalMoves(mat);
    if(s.find({_row, _col}) == s.end()){
        return Moves::NaM;
    }
    else{
        if(_row == getRow() && (_col == getCol() + 2 || _col == getCol() - 2)){
            return Moves::castling;
        }
        else{
            return Moves::movement;
        }
    }
}
#endif