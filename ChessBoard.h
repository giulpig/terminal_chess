#ifndef BOARD_H
#define BOARD_H

#include "Enums.h"
#include "Exceptions.h"
#include "ChessPiece.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Tower.h"
#include "Pawn.h"
#include "Dummy.h"


#include <vector>
#include <list>
#include <memory>
#include <utility>

using std::vector;
using std::list;
using std::shared_ptr;
using std::pair;


constexpr int SIZE = 8;

constexpr char initial_roles[8][8] = {

    {'T','C','A','D','R','A','C','T'},
    {'P','P','P','P','P','P','P','P'},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {'P','P','P','P','P','P','P','P'},
    {'T','C','A','D','R','A','C','T'}
};


constexpr bool intial_color[8][8] = {             //dummy chesspieces are black by convenction

    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
};



//add inclusion of other chessPieces
class ChessBoard{

private:
    shared_ptr<ChessPiece> chessBoard[SIZE][SIZE];
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