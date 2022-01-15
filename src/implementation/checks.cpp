#ifndef CHECKS_CPP
#define CHECKS_CPP

#include "ChessBoard.h"

bool ChessBoard::isCheck(Side s, const std::shared_ptr<ChessPiece> mat[8][8], std::pair<int,int> p) const{
    if(!mat){
        mat = _chessBoard;
    }
    std::shared_ptr<ChessPiece> k;
    std::vector<std::shared_ptr<ChessPiece>> v;
    if(s == Side::white){
        v = _black;
    }
    if(s == Side::black){
        v = _white;
    }
    //position of the king
    int r, c;
    //in the case of possible moves the king might not be in the position given by the object, this isn't important as the pieces of the opposite party only have to know the disposition of the chessBoard
    for(int i = 0; i < 8; i ++){
        for(int j = 0; j < 8; j ++){
            if(mat[i][j]->getRole() == Role::king && mat[i][j]->getSide() == s){
                r = i;
                c = j;
            }
        }
    }
    //for every piece of the opposing side checks if it threatens the king
    for(std::shared_ptr<ChessPiece> i : v){
        if(i->getRow() == p.first && i->getCol() == p.second){
            continue;
        }
        if(i->moveType(r, c, mat) != Moves::NaM){
            return true;
        }
    }
    return false;
}

bool ChessBoard::hasPossibleMoves(Side s){
    std::vector<std::shared_ptr<ChessPiece>> v;
    if(s == Side::white){
        v = _white;
    }
    else{
        v = _black;
    }
    //checks if any of the piece has any legal moves
    for(std::shared_ptr<ChessPiece> i : v){
        if(!getPossiblemovements(i->getRow(), i->getCol()).empty()){
            return true;
        }
    }
    return false;
}

bool ChessBoard::isStaleMate(Side s){
    if(!isCheck(s, _chessBoard) && !hasPossibleMoves(s)){
        return true;
    }
    //if there are three repetitions of the same board or more than 50 moves where made
    //without moving a pawn or a piece was eaten
    else if(_threeRep || _finalCountUp >= 50){
        return true;
    }
    //only the kings are left
    else if(_white.size() == 1 && _black.size() == 1){
        return true;
    }
    //if the only pieces left are the kings and knight or a bishop
    else if(_white.size() == 1 && _black.size() == 2){
        for(std::shared_ptr<ChessPiece> c : _black){
            Role r = c->getRole();
            if(r != Role::king && (r == Role::bishop ||  r == Role::knight)){
                return true;
            }
        }
    }
    else if(_white.size() == 2 && _black.size() == 1){
        for(std::shared_ptr<ChessPiece> c : _white){
            Role r = c->getRole();
            if(r != Role::king && (r == Role::bishop ||  r == Role::knight)){
                return true;
            }
        }
    }
    return false;
}
#endif