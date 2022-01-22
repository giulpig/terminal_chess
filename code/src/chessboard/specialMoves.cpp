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
void ChessBoard::doEnpassant(const pair<int, int>& from, const pair<int, int>& to){
    const shared_ptr<ChessPiece> &fromPiece = _chessBoard[from.first][from.second];
    const shared_ptr<ChessPiece> &toPiece   = _chessBoard[to.first][to.second];

    removeFromPieceList(_chessBoard[from.first][to.second]);
    _chessBoard[from.first][to.second] = oneDummyToRuleThemAll;
    
    return;
}


bool ChessBoard::doCastling(const pair<int, int> &finalKingPos){

    const int rookCol = finalKingPos.second==2 ? 0 : 7;
    constexpr int kingCol = 4;  //king surely has not moved

    const int commonRow = finalKingPos.first;    

    shared_ptr<ChessPiece> kingPiece = _chessBoard[finalKingPos.first][kingCol];
    shared_ptr<ChessPiece> rookPiece = _chessBoard[finalKingPos.first][commonRow];
    Side side = kingPiece->getSide();

    if(rookCol==0){     //left~long castling
        for(int i=1; i<=2; i++){
            //move king to the left one by one
            swapPieces({commonRow, kingCol-i+1}, {commonRow, kingCol-i});
            //check for check situation --> (invalid castling)
            if(isCheck(side, _chessBoard, {commonRow, kingCol-i})){
                //go back
                swapPieces({commonRow, kingCol}, {commonRow, kingCol-i});
                return false;
            }
        }

        //move rook
        swapPieces({commonRow, rookCol}, {commonRow, rookCol+3});

        //update piece information
        kingPiece->setPosition(commonRow, kingCol-2);
        rookPiece->setPosition(commonRow, rookCol+3);
        return true;
    }


    if(rookCol==7){     //right~short castling
        for(int i=1; i<=2; i++){
            //move king to the right one by one
            swapPieces({commonRow, kingCol+i-1}, {commonRow, kingCol+i});
            
            //check for check situation --> (invalid castling)
            if(isCheck(side, _chessBoard, {commonRow, kingCol+i})){
                //go back
                swapPieces({commonRow, kingCol}, {commonRow, kingCol+i});
                return false;
            }
        }

        //move rook
        swapPieces({commonRow, rookCol}, {commonRow, rookCol-2});

        //update piece information
        kingPiece->setPosition(commonRow, kingCol+2);
        rookPiece->setPosition(commonRow, rookCol-2);

        return true;
    }

    return false;
}

#endif