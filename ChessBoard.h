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
#include <string>

using std::list;
using std::pair;
using std::shared_ptr;
using std::vector;

constexpr int SIZE = 8;

constexpr char initial_roles[8][8] = {

    {'T', 'C', 'A', 'D', 'R', 'A', 'C', 'T'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'T', 'C', 'A', 'D', 'R', 'A', 'C', 'T'}};

constexpr bool initial_colors[8][8] = {
    //dummy chesspieces are black by convenction

    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
};

//add inclusion of other chessPieces
class ChessBoard
{

private:
    shared_ptr<ChessPiece> chessBoard[SIZE][SIZE];
    list<shared_ptr<ChessPiece>> black, white; //le liste e la matrice devono puntare agli stessi oggetti, questa è la soluzione meno peggiore che mi è venuta in mente ma si può fare di meglio
    Pawn p{-1, -1, side::black};               //pawn to promove

    void addToPieceList(const shared_ptr<ChessPiece>, const side);

    shared_ptr<ChessPiece> copyPiece(const shared_ptr<ChessPiece>) const;


public:
    ChessBoard();
    ChessBoard(const ChessBoard &);  //copy
    ChessBoard(ChessBoard &&); //move

    ChessBoard& operator=(const ChessBoard &); //does a copy

    bool isCheck() const;
    bool isCheckMate() const;
    bool isStaleMate() const;

    //returns possible movements from a specific chesspiece. the returned set is empty if there isn't any piece or if there aren't any possible moves
    set<std::pair<int, int>> getPossiblemovements(int _row, int _col) const;

    //returns possible movements for a specific chesspiece in the position of the list of pieces chosen by side
    set<std::pair<int, int>> getPossiblemovementsByIndex(int index, side c) const;

    //returns the type of move that was done
    move move(pair<int, int>, pair<int, int>) const;

    //returns a string containing the board disposition
    std::string notToString() const;

    //returns the number of piece on the chessboard
    int nOfPieces(side c) const;

    //does a promotion
    void promotion(role r);
};
#endif