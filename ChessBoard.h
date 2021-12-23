#ifndef BOARD_H
#define BOARD_H

#include "Enums.h"
#include "Exceptions.h"
#include "ChessPiece.h"
#include "Pawn.h"

#include <vector>
#include <list>
#include <memory>
#include <utility>

using std::vector;
using std::list;
using std::shared_ptr;
using std::pair;

//add inclusion of other chessPieces
class ChessBoard{

private:
    shared_ptr<ChessPiece> chessBoard[8][8];
    list<shared_ptr<ChessPiece>> black, white;//le liste e la matrice devono puntare agli stessi oggetti, questa è la soluzione meno peggiore che mi è venuta in mente ma si può fare di meglio
    Pawn p{-1, -1, side::black};//pawn to promove
public:
    ChessBoard();
    ChessBoard(ChessBoard&);
    ChessBoard(ChessBoard&&);

    ChessBoard operator=(ChessBoard&);

    bool isCheck();
    bool isCheckMate();
    bool isStaleMate();
    //returns possible movements from a specific chesspiece. the returned set is empty if there isn't any piece or if there aren't any possible moves
    set<std::pair<int, int>> getPossiblemovements(int _row, int _col);
    //returns possible movements for a specific chesspiece in the position of the list of pieces chosen by side
    set<std::pair<int, int>> getPossiblemovementsByIndex(int index, side c);
    //returns the type of move that was done
    move move(pair<int, int>, pair<int, int>);
    //returns a string containing the board disposition
    std::string notToString();
    int nOfPieces(side c);
    //does a promotion
    void promotion(role r);
};
#endif