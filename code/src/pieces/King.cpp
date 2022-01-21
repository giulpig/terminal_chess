//Artico Giovanni n.matr. 2000178
#ifndef KING_CPP
#define KING_CPP

#include "King.h"

King::King(int _row, int _col, Side s) : ChessPiece(_row, _col, s) {
    rol = Role::king;
}

void King::setPosition(int _row, int _col){
    ChessPiece::setPosition(_row, _col);
}
std::set<std::pair<int, int>> King::getLegalMoves(const std::shared_ptr<ChessPiece> mat[8][8]) const{
    std::set<std::pair<int, int>> s;
    //move by onw position
    for(int i = -1; i <= 1; i ++){
        for(int j = -1; j <= 1; j ++){
            if((j == 0 && i == 0) || !checkBoundaries({getRow() + i, getCol() + j})){
                continue;
            }
            else{
                if(isOppositeSide(mat, getRow() + i, getCol() + j) || isDummy(mat, getRow() + i, getCol() + j)){
                    s.insert({getRow() + i, getCol() + j});
                }
            }
        }
    }
    //left castling
    if(!isMoved()){
        if(!mat[getRow()][0]->isMoved() && mat[getRow()][0]->getRole() == Role::tower){
            bool free = true;
            for(int i = getCol() - 1; i > 0; i --){
                if(!isDummy(mat, getRow(), i)){
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
        if(!mat[getRow()][7]->isMoved() && mat[getRow()][7]->getRole() == Role::tower){
            bool free = true;
            for(int i = getCol() + 1; i < 7; i ++){
                if(!isDummy(mat, getRow(), i)){
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
Moves King::moveType(int _row, int _col, const std::shared_ptr<ChessPiece> mat[8][8]) const{
    std::set<std::pair<int, int>> s = getLegalMoves(mat);
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