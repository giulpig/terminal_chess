#ifndef CHECKS_CPP
#define CHECKS_CPP

#include "ChessBoard.h"
bool ChessBoard::isCheck(Side s, const shared_ptr<ChessPiece> mat[8][8], pair<int,int>) const{
    shared_ptr<ChessPiece> k;
    vector<shared_ptr<ChessPiece>> v;
    if(s == Side::black){
        v = black;
        for(int i = 0; i < white.size(); i ++){
            if(white[i]->getRole() == Role::king){
                k = white[i];
                break;
            }
        }
    }
    if(s == Side::white){
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
        for(pair<int,int> p : getPossiblemovements(i->getRow(), i->getCol())){
            shared_ptr<ChessPiece> temp[8][8];
            for(int ii = 0; ii < 8; ii ++){
                for(int jj = 0; jj < 8; jj ++){
                    if(ii == i->getRow() && jj == i->getCol()){
                        temp[ii][jj] = shared_ptr<Dummy>{};
                    }
                    else if(ii == p.first && jj == p.second){
                        temp[ii][jj] = i;
                    }
                    else{
                        temp[ii][jj] = chessBoard[ii][jj];
                    }
                }
            }
            if(!isCheck(s, temp, p)){
                return false;
            }
        }
    }
    return true;
}

bool ChessBoard::isStaleMate(Side s) const{
    if(!isCheck(s, chessBoard) && ArePossibleMoves(s)){
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
}
#endif