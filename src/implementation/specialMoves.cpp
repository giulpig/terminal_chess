//Giulio Codutti 2008795

#ifndef SPECIALMOVES_CPP
#define SPECIALMOVES_CPP

#include "ChessBoard.h"

using std::shared_ptr;
using std::pair;


//does a promotion
Moves ChessBoard::promotion(Role role){

    if(_toPromote == nullptr){
        throw InvalidPromotion{};
    }
    
    int row = _toPromote->getRow();
    int col = _toPromote->getCol();
    Side side = _toPromote->getSide();

    removeFromPieceList(_toPromote);

    //Place new piece on chessBoard
    _chessBoard[row][col] = newPiece(row, col, side, role);

    addToPieceList(_chessBoard[row][col]);

    _toPromote = nullptr;

    //staleMate check
    if(isStaleMate(side))
        return Moves::staleMate;

    //checkMate check, do-undo strategy for all pieces and all moves
    if(isCheck(otherSide(side), _chessBoard) && !hasPossibleMoves(otherSide(side))){
        return Moves::checkMate;
    }

    return Moves::movement;
}


//removes the piece that is supposed to be eaten in enpassant
void ChessBoard::doEnpassant(const pair<int, int>& pos){
    const shared_ptr<ChessPiece> &piece = _chessBoard[pos.first][pos.second];

    switch(piece->getSide()){

        case(Side::black):
            removeFromPieceList(_chessBoard[pos.first+1][pos.second]);
            _chessBoard[pos.first+1][pos.second] = oneDummyToRuleThemAll;
            return;

        case(Side::white):
            removeFromPieceList(_chessBoard[pos.first-1][pos.second]);
            _chessBoard[pos.first-1][pos.second] = oneDummyToRuleThemAll;
            return;
    }
}


bool ChessBoard::doCastling(const pair<int, int> &rookPos){

    const int rookCol = rookPos.second;
    constexpr int kingCol = 4;              //king surely has not moved

    shared_ptr<ChessPiece> kingPiece = _chessBoard[rookPos.first][kingCol];
    shared_ptr<ChessPiece> rookPiece = _chessBoard[rookPos.first][rookPos.second];
    Side side = kingPiece->getSide();

    if(rookCol==0){     //left~long castling
        for(int i=1; i<=2; i++){
            //move king to the left one by one
            swapPieces({rookPos.first, kingCol-i+1}, {rookPos.first, kingCol-i});
            //check for check situation --> (invalid castling)
            if(isCheck(side, _chessBoard, {rookPos.first, kingCol-i})){
                //go back
                swapPieces({rookPos.first, kingCol}, {rookPos.first, kingCol-i});
                return false;
            }
        }

        //move rook
        swapPieces({rookPos.first, rookPos.second}, {rookPos.first, rookPos.second+3});

        //update piece information
        kingPiece->setPosition(rookPos.first, kingCol-2);
        rookPiece->setPosition(rookPos.first, rookPos.second+3);
        return true;
    }


    if(rookCol==7){     //right~short castling
        for(int i=1; i<=2; i++){
            //move king to the right one by one
            swapPieces({rookPos.first, kingCol+i-1}, {rookPos.first, kingCol+i});
            
            //check for check situation --> (invalid castling)
            if(isCheck(side, _chessBoard, {rookPos.first, kingCol+i})){
                //go back
                swapPieces({rookPos.first, kingCol}, {rookPos.first, kingCol+i});
                return false;
            }
        }

        //move rook
        swapPieces({rookPos.first, rookPos.second}, {rookPos.first, rookPos.second-2});

        //update piece information
        kingPiece->setPosition(rookPos.first, kingCol+2);
        rookPiece->setPosition(rookPos.first, rookPos.second-2);

        return true;
    }

    return false;
}

#endif