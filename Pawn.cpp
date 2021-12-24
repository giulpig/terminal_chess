#ifndef PAWN_CPP
#define PAWN_CPP

#include "Pawn.h"

Pawn::Pawn(int _row, int _col, side s) : ChessPiece{_row, _col, s}{}
void Pawn::setPosition(int _row, int _col){
    ChessPiece::setPosition(_row, _col);
    if(_row == getRow() + 2 || _row == getRow() - 2){
        enpassant = true;
    }
    if(enpassant){
        enpassant = false;
    }
}
set<pair<int, int>> Pawn::getLegalMoves(shared_ptr<ChessPiece> mat[8][8]) const{
    set<pair<int, int>> m;
    int dir;

    if(getSide() == side::black){
        dir = 1;
    }
    else{
        dir = -1;
    }
    //double first move
    if(!isMoved()){
        if((*(mat[getRow() + 2 * dir][getCol()])).getRole() == role::dummy){
            m.insert({getRow() + 2 * dir, getCol()});
        }
    }
    //normal one move in the right direction
    if(getRow() + dir >= 0 && getRow() + dir < 8 && ((*(mat[getRow() + dir][getCol()])).getRole() == role::dummy)){
            m.insert({getRow() + dir, getCol()});
    }
    //eating to the right
    if(getRow() + dir >= 0 && getRow() + dir < 8 && getCol() + 1 < 8 && ((*(mat[getRow() + dir][getCol() + 1])).getRole() != role::dummy)){
        m.insert({getRow() + dir, getCol() + 1});
    }
    //eating to the left
    if(getRow() + dir >= 0 && getRow() + dir < 8 && getCol() - 1 >= 0 && ((*(mat[getRow() + dir][getCol() - 1])).getRole() != role::dummy)){
        m.insert({getRow() + dir, getCol() - 1});
    }
    //enpassant right
    if(getCol() + 1 < 8 && ((*(mat[getRow()][getCol() + 1])).getRole() == role::pawn)){
        Pawn p = dynamic_cast<Pawn&>(*(mat[getRow()][getCol() + 1]));
        if(p.getEnpassant()){
            m.insert({getRow() + dir, getCol() + 1});
        }
    }
    //enpassant left
    if(getCol() - 1 >= 0 && ((*(mat[getRow()][getCol() - 1])).getRole() == role::pawn)){
        Pawn p = dynamic_cast<Pawn&>(*(mat[getRow()][getCol() - 1]));
        if(p.getEnpassant()){
            m.insert({getRow() + dir, getCol() - 1});
        }
    }

    return m;
}
move Pawn::moveType(int _row, int _col, shared_ptr<ChessPiece> mat[8][8]) const{
    if(_row < 0 || _row >= 8 || _col < 0 || _col >= 8){
        return move::NaM;
    }
    int dir;
    if(getSide() == side::black){
        dir = 1;
    }
    else{
        dir = -1;
    }
    //normal one move in the direction
    if(_col == getCol() &&  _row == getRow() + dir && (*(mat[_row + dir][_col])).getRole() == role::dummy){
        return move::movement;
    }
    //eating to the right
    else if(_row = getRow() + dir && _col == getCol() + 1 && (*(mat[_row + dir][_col + 1])).getRole() != role::dummy){
        return move::movement;
    }
    //eating to the left
    else if(_row = getRow() + dir && _col == getCol() - 1 && (*(mat[_row + dir][_col - 1])).getRole() != role::dummy){
        return move::movement;
    }
    //enpassant right
    else if(_row == getRow() + dir && _col == getCol() + 1 && ((*(mat[getRow()][getCol() + 1])).getRole() == role::pawn)){
            Pawn p = dynamic_cast<Pawn&>(*(mat[getRow()][getCol() + 1]));
            if(p.getEnpassant()){
                return move::enpassant;
            }
    }
    //enpassant left
    else if(_row == getRow() + dir && _col == getCol() - 1 && ((*(mat[getRow()][getCol() - 1])).getRole() == role::pawn)){
        Pawn p = dynamic_cast<Pawn&>(*(mat[getRow()][getCol() - 1]));
            if(p.getEnpassant()){
               return move::enpassant;
            }
    }

    else{
        return move::NaM;
    }
}
void Pawn::cancelEnpassant(){
    enpassant = false;
}
bool Pawn::getEnpassant() const{
    return enpassant;
}
#endif