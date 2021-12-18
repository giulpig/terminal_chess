#ifndef BOARD_H
#define BOARD_H
#include "Enums.h"
#include "Exceptions.h"
#include "ChessPiece.h"
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
    public:
    ChessBoard();
    ChessBoard(ChessBoard&);
    ChessBoard(ChessBoard&&);
    ChessBoard operator=(ChessBoard&);
    bool isCheck();
    bool isCheckMate();
    bool isStaleMate();
    bool move(pair<int, int>, pair<int, int>);//returns true if the move is legal
};
#endif