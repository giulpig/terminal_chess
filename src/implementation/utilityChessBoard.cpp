#ifndef UTILITYCHESSBOARD_CPP
#define UTILITYCHESSBOARD_CPP

#include "ChessBoard.h"

/*
    Index of contents:

        ~ getPossiblemovementsByIndex()
        ~ addToPieceList()      [private]
        ~ removeFromPieceList() [private]
        ~ getPieceList()        [private]
        ~ nOfPieces()
        ~ notToString()
        ~ getPosition()
        ~ copyPiece()      [static][private]
        ~ newPiece()       [static][private]
        ~ swapPieces()     [static][private]
        ~ otherSide()      [static]

*/

using std::shared_ptr;
using std::pair;



//returns possible movements for a specific chesspiece in the position of the list of pieces chosen by side,
//the returned set is empty if there isn't any piece or if there are no possible moves
std::set<pair<int, int>> ChessBoard::getPossiblemovementsByIndex(int index, Side side){
    switch(side){
        case Side::black:
            return getPossiblemovements(_black[index]->getRow(), _black[index]->getCol());
        break;
        case Side::white:
            return getPossiblemovements(_white[index]->getRow(), _white[index]->getCol());
        break;
    }
    return std::set<pair<int, int>>{};
}


//adds piece at the end of the corresponding (black or white) list of pieces
void ChessBoard::addToPieceList(const shared_ptr<ChessPiece>& piece){
    getPieceList(piece->getSide()).push_back(piece);
    return;
}


//remove piece from the corresponding (black or white) list of pieces
void ChessBoard::removeFromPieceList(const shared_ptr<ChessPiece>& piece){

    std::vector<shared_ptr<ChessPiece>>& pieceList = getPieceList(piece->getSide());
    for(auto it=pieceList.begin(); it!=pieceList.end(); it++){
        if(*it == piece){
            pieceList.erase(it);
            return;
        }
    }
}


std::vector<shared_ptr<ChessPiece>>& ChessBoard::getPieceList(Side s){
    if(s == Side::black)
        return _black;
    if(s == Side::white)
        return _white;

    throw NoSideException{};
}


//returns the number of piece on the chessboard
int ChessBoard::nOfPieces(Side s) const{
    if(s == Side::black)
        return _black.size();
    if(s == Side::white)
        return _white.size();
    
    throw NoSideException{};
}


//get position of the piece with index in the piece list of specific side
pair<int, int> ChessBoard::getPosition(int index, Side side) const{
    switch(side){
        case Side::black:
            //invalid index
            if(index >= _black.size())
                return {-1, -1};

            return {_black[index]->getRow(), _black[index]->getCol()};
        break;

        case Side::white:
            //invalid index
            if(index >= _white.size())
                return {-1, -1};
    
            return {_white[index]->getRow(), _white[index]->getCol()};
        break;
    }

    throw NoSideException{};
}


//returns a string containing the board disposition
std::string ChessBoard::notToString() const{
    std::string res;

    for(int i=0; i<SIZE; i++){
        res += std::to_string(SIZE-i) + " ";
        for(int j=0; j<SIZE; j++){
            if(_chessBoard[i][j]->getSide() == Side::black)
                res += static_cast<char>(_chessBoard[i][j]->getRole());
            else
                res += std::tolower(static_cast<char>(_chessBoard[i][j]->getRole()));

        }
        res += "\n";
    }
    
    res += "\n  ";
    for(int i=0; i<SIZE; i++){
        res += 'A'+i;
    }
    res += "\n";
    return res;
}


#endif