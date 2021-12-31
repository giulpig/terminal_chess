#ifndef CHECKS_CPP
#define CHECKS_CPP

#include "ChessBoard.h"
bool ChessBoard::isCheck(Side s, const shared_ptr<ChessPiece> mat[8][8], pair<int,int> p) const{
    shared_ptr<ChessPiece> k;
    vector<shared_ptr<ChessPiece>> v;
    if(s == Side::white){
        v = black;
        for(int i = 0; i < white.size(); i ++){
            if(white[i]->getRole() == Role::king){
                k = white[i];
                break;
            }
        }
    }
    if(s == Side::black){
        v = white;
        for(int i = 0; i < black.size(); i ++){
            if(black[i]->getRole() == Role::king){
                k = black[i];
                break;
            }
        }
    }
    int r = k->getRow();
    int c = k->getCol();
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
    else if(threeRep || finalCountDown >= 50){
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