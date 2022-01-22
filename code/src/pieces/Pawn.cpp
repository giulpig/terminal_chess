//Artico Giovanni n.matr. 2000178
#ifndef PAWN_CPP
#define PAWN_CPP

#include "Pawn.h"

Pawn::Pawn(int _row, int _col, Side s) : ChessPiece{_row, _col, s}{
    rol = Role::pawn;
    enpassant = false;
}

void Pawn::setPosition(int _row, int _col){
    if(_row == getRow() + 2 || _row == getRow() - 2){
        enpassant = true;
    }
    ChessPiece::setPosition(_row, _col);
}

std::set<std::pair<int, int>> Pawn::getLegalMoves(const std::shared_ptr<ChessPiece> mat[8][8]) const{
    std::set<std::pair<int, int>> m;
    int dir;
    //choosing the direction based off the side
    if(getSide() == Side::black){
        dir = 1;
    }
    else{
        dir = -1;
    }
    //normal one move in the right direction
    if(checkBoundaries({getRow() + dir, getCol()}) && isDummy(mat, getRow() + dir, getCol())){
        m.insert({getRow() + dir, getCol()});
        //double first move
        if(!isMoved()){
            if(isDummy(mat, getRow() + 2 * dir, getCol())){
                m.insert({getRow() + 2 * dir, getCol()});
            }
        }
    }
    //eating
    for(int i = -1; i <= 1; i += 2){
        if(checkBoundaries({getRow() + dir, getCol() + i}) && !isDummy(mat, getRow() + dir, getCol() + i)){
            if(isOppositeSide(mat, getRow() + dir, getCol() + i)){
                m.insert({getRow() + dir, getCol() + i});
            }
        }
    }
    //enpassant
    for(int i = -1; i <= 1; i += 2){
        if(checkBoundaries({getRow() + dir, getCol() + i}) && mat[getRow()][getCol() + i]->getRole() == Role::pawn){
            Pawn p = dynamic_cast<Pawn&>(*(mat[getRow()][getCol() + i]));
            if(p.getEnpassant()){
                if(isDummy(mat, getRow() + dir, getCol() + i)){
                    m.insert({getRow() + dir, getCol() + i});
                }
            }
        }
    }
    return m;
}

Moves Pawn::moveType(int _row, int _col, const std::shared_ptr<ChessPiece> mat[8][8]) const{
    int dir;
    if(getSide() == Side::black){
        dir = 1;
    }
    else{
        dir = -1;
    }
    std::set<std::pair<int, int>> s = getLegalMoves(mat);
    if(s.find({_row, _col}) == s.end()){
        return Moves::NaM;
    }
    else{
        //enpassant
        for(int i = - 1; i <= 1; i += 2){
            if(_row == getRow() + dir && _col == getCol() + i && mat[getRow()][getCol() + i]->getRole() == Role::pawn && isDummy(mat, getRow() + dir, getCol() + i)){
                return Moves::enpassant;
            }
        }
        //it got to the last row
        if(_row == 7 || _row == 0){
            return Moves::promotion;
        }
        //double move
        else if(_row == getRow() + 2*dir){
            return Moves::doublePawn;
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