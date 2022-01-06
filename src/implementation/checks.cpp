#ifndef CHECKS_CPP
#define CHECKS_CPP

#include "ChessBoard.h"

bool ChessBoard::isCheck(Side s, const shared_ptr<ChessPiece> mat[8][8], pair<int,int> p) const{
    if(!mat){
        mat = chessBoard;
    }
    shared_ptr<ChessPiece> k;
    vector<shared_ptr<ChessPiece>> v;
    if(s == Side::white){
        v = black;
    }
    if(s == Side::black){
        v = white;
    }
    int r, c;
    //in the case of possible moves the king might not be in the position given by the object, this isn't important as the pieces of the opposite party only have to know the disposition of the chessBoard
    for(int i = 0; i < 8; i ++){
        for(int j = 0; j < 8; j ++){
            if(mat[i][j]->getRole() == Role::king && mat[i][j]->getSide() == s){
                r = i;
                j = j;
            }
        }
    }
    for(shared_ptr<ChessPiece> i : v){
        if(i->getRow() == p.first && i->getCol() == p.second){
            continue;
        }
        if(i->moveType(r, c, mat) != Moves::NaM){
            return true;
        }
    }
    return false;
}

bool ChessBoard::ArePossibleMoves(Side s) const{
    vector<shared_ptr<ChessPiece>> v;
    if(s == Side::white){
        v = white;
    }
    else{
        v = black;
    }
    for(shared_ptr<ChessPiece> i : v){
        if(!getPossiblemovements(i->getRow(), i->getCol()).empty()){
            return true;
        }
    }
    return false;
}

bool ChessBoard::isStaleMate(Side s) const{
    if(!isCheck(s, chessBoard) && !ArePossibleMoves(s)){
        return true;
    }
    else if(threeRep || finalCountUp >= 50){
        return true;
    }
    else if(white.size() == 1 && black.size() == 1){
        return true;
    }
    else if(white.size() == 1 && black.size() == 2){
        for(shared_ptr<ChessPiece> c : black){
            Role r = c->getRole();
            if(r != Role::king && (r == Role::bishop ||  r == Role::knight)){
                return true;
            }
        }
    }
    else if(white.size() == 2 && black.size() == 1){
        for(shared_ptr<ChessPiece> c : white){
            Role r = c->getRole();
            if(r != Role::king && (r == Role::bishop ||  r == Role::knight)){
                return true;
            }
        }
    }
    return false;
}
#endif