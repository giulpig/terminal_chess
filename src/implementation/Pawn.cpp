#ifndef PAWN_CPP
#define PAWN_CPP

#include "Pawn.h"

Pawn::Pawn(int _row, int _col, Side s) : ChessPiece{_row, _col, s}{
    rol = Role::pawn;
    enpassant = false;
}

void Pawn::setPosition(int _row, int _col){
    ChessPiece::setPosition(_row, _col);
    if(_row == getRow() + 2 || _row == getRow() - 2){
        enpassant = true;
    }
    //if the en passant wasn't done
    if(enpassant){
        enpassant = false;
    }
}

set<pair<int, int>> Pawn::getLegalMoves(const shared_ptr<ChessPiece> mat[8][8]) const{
    set<pair<int, int>> m;
    int dir;

    if(getSide() == Side::black){
        dir = 1;
    }
    else{
        dir = -1;
    }
    //normal one move in the right direction
    if(getRow() + dir >= 0 && getRow() + dir < 8 && ((*(mat[getRow() + dir][getCol()])).getRole() == Role::dummy)){
        m.insert({getRow() + dir, getCol()});
        //double first move
        if(!isMoved()){
            if((*(mat[getRow() + 2 * dir][getCol()])).getRole() == Role::dummy){
                m.insert({getRow() + 2 * dir, getCol()});
            }
        }
    }
    /*
    //eating to the right
    if(getRow() + dir >= 0 && getRow() + dir < 8 && getCol() + 1 < 8 && ((*(mat[getRow() + dir][getCol() + 1])).getRole() != Role::dummy)){
        if((*(mat[getRow() + dir][getCol() + 1])).getSide() != getSide()){
            m.insert({getRow() + dir, getCol() + 1});
        }
    }
    //eating to the left
    if(getRow() + dir >= 0 && getRow() + dir < 8 && getCol() - 1 >= 0 && ((*(mat[getRow() + dir][getCol() - 1])).getRole() != Role::dummy)){
        if((*(mat[getRow() + dir][getCol() - 1])).getSide() != getSide()){
            m.insert({getRow() + dir, getCol() - 1});
        }
    */
    //eating
    for(int i = -1; i <= 1; i += 2){
        if(getRow() + dir >= 0 && getRow() + dir < 8 && getCol() + i >= 0 && getCol() + 1 < 8 && ((*(mat[getRow() + dir][getCol() - i])).getRole() != Role::dummy)){
            if((*(mat[getRow() + dir][getCol() + i])).getSide() != getSide()){
                m.insert({getRow() + dir, getCol() + i});
            }
        }
    }
    /*
    //enpassant right
    if(getCol() + 1 < 8 && ((*(mat[getRow()][getCol() + 1])).getRole() == Role::pawn)){
        Pawn p = dynamic_cast<Pawn&>(*(mat[getRow()][getCol() + 1]));
        if(p.getEnpassant()){
            if((*(mat[getRow() + dir][getCol() + 1])).getRole() == Role::dummy){
                m.insert({getRow() + dir, getCol() + 1});
            }
        }
    }
    //enpassant left
    if(getCol() - 1 >= 0 && ((*(mat[getRow()][getCol() - 1])).getRole() == Role::pawn)){
        Pawn p = dynamic_cast<Pawn&>(*(mat[getRow()][getCol() - 1]));
        if(p.getEnpassant()){
            if((*(mat[getRow() + dir][getCol() - 1])).getRole() == Role::dummy){
                m.insert({getRow() + dir, getCol() - 1});
            }
        }
    }*/
    //enpassant
    for(int i = -1; i <= 1; i += 2){
        if(getCol() + i >= 0 && getCol() + i < 8 && ((*(mat[getRow()][getCol() + i])).getRole() == Role::pawn)){
            Pawn p = dynamic_cast<Pawn&>(*(mat[getRow()][getCol() + i]));
            if(p.getEnpassant()){
                if((*(mat[getRow() + dir][getCol() + i])).getRole() == Role::dummy){
                    m.insert({getRow() + dir, getCol() + i});
                }
            }
        }
    }
    return m;
}

Moves Pawn::moveType(int _row, int _col, const shared_ptr<ChessPiece> mat[8][8]) const{
    int dir;
    if(getSide() == Side::black){
        dir = 1;
    }
    else{
        dir = -1;
    }
    set<pair<int, int>> s = getLegalMoves(mat);
    if(s.find({_row, _col}) == s.end()){
        return Moves::NaM;
    }
    else{
        /*
        //enpassant right
        if(_row == getRow() + dir && _col == getCol() + 1 && ((*(mat[getRow()][getCol() + 1])).getRole() == Role::pawn)){
            Pawn p = dynamic_cast<Pawn&>(*(mat[getRow()][getCol() + 1]));
            if(p.getEnpassant()){
                if((*(mat[_row][_col])).getRole() == Role::dummy){
                    return Moves::enpassant;
                }
            }
        }
        //enpassant left
        else if(_row == getRow() + dir && _col == getCol() - 1 && ((*(mat[getRow()][getCol() - 1])).getRole() == Role::pawn)){
            Pawn p = dynamic_cast<Pawn&>(*(mat[getRow()][getCol() - 1]));
            if(p.getEnpassant()){
                if((*(mat[_row][_col])).getRole() == Role::dummy){
                    return Moves::enpassant;
                }
            }
        }*/
        //enpassant
        for(int i = - 1; i <= 1; i += 2){
            if(_row == getRow() + dir && _col == getCol() + i && (*(mat[getRow()][getCol() + i])).getRole() == Role::pawn && ((*(mat[getRow() + dir][getCol() + i])).getRole() == Role::dummy)){
                return Moves::enpassant;
            }
        }
        if(_row == 7 || _row == 0){
            return Moves::promotion;
        }
        return Moves::movement;
    }
}
void Pawn::cancelEnpassant(){
    enpassant = false;
}
bool Pawn::getEnpassant() const{
    return enpassant;
}
#endif