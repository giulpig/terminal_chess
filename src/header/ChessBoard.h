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
#include <map>

using std::list;
using std::pair;
using std::shared_ptr;
using std::vector;
using std::string;
using std::map;


//--------------------constants----------------------

constexpr int SIZE = 8;

constexpr char initial_roles[8][8] = {

    {'T', 'C', 'A', 'D', 'R', 'A', 'C', 'T'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'T', 'C', 'A', 'D', 'R', 'A', 'C', 'T'}
};


constexpr char initial_colors[8][8] = {
    
    //dummy chesspieces are black
    {0,   0,  0,  0,  0,  0,  0,  0},
    {0,   0,  0,  0,  0,  0,  0,  0},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {1,   1,  1,  1,  1,  1,  1,  1},
    {1,   1,  1,  1,  1,  1,  1,  1},
};




//--------------------ChessBoard class----------------------

//add inclusion of other chessPieces
class ChessBoard
{

private:
    //attributes
    shared_ptr<ChessPiece> chessBoard[SIZE][SIZE];
    //why list?? because yes
    vector<shared_ptr<ChessPiece>> black, white; //le liste e la matrice devono puntare agli stessi oggetti, questa è la soluzione meno peggiore che mi è venuta in mente ma si può fare di meglio
    shared_ptr<ChessPiece> toPromote;                  //pawn to promote
    shared_ptr<Dummy> oneDummyToRuleThemAll = std::make_shared<Dummy>();

    //utility functions
    static shared_ptr<ChessPiece> newPiece(int row, int col, Side, Role);
    void addToPieceList(const shared_ptr<ChessPiece>);
    void removeFromPieceList(const shared_ptr<ChessPiece>);
    static shared_ptr<ChessPiece> copyPiece(const shared_ptr<ChessPiece>);

    //TODO Giulio:
    //counts moves since last capture or movement of a pawn
    int finalCountDown = 0;
    //string representing the chessBoard and the number of times it has been repeated
    map<string, int> chessBoards;
    //true if a single configuration has been repeated three times
    bool threeRep = false;

public:
    ChessBoard();
    ChessBoard(const ChessBoard &); //copy
    ChessBoard(ChessBoard &&);      //move

    ChessBoard& operator=(const ChessBoard &); //does a copy


    //returns a string containing the board disposition
    std::string notToString() const;

    //returns the number of pices on the chessboard
    int nOfPieces(Side) const;

    //get position of the piece with index in the piece list of specific side (-1, -1 if invalid)
    pair<int, int> getPosition(int index, Side) const;

    //returns possible movements from a specific chesspiece,
    //the returned set is empty if there isn't any piece or if there are no possible moves
    set<std::pair<int, int>> getPossiblemovements(int row, int col) const;

    //returns possible movements for a specific chesspiece in the position of the list of pieces chosen by side,
    //the returned set is empty if there isn't any piece or if there are no possible moves
    set<std::pair<int, int>> getPossiblemovementsByIndex(int index, Side) const;

    //changes pointers and returns the type of move that was done
    Moves doMove(pair<int, int>, pair<int, int>);

    //argument 1: which side to check if the king is in check
    //argument 2: chessboard to use for the check
    //argument 3: needed if the board is a possible board and it signals where's the piece that was moved.
    //            used for check for possible moves
    bool isCheck(Side, const shared_ptr<ChessPiece>[8][8], pair<int,int> p = pair<int,int>{-1, -1}) const;
    //argument: which side to check if it has possible moves
    bool ArePossibleMoves(Side) const;
    //argument: which side to check if it's in stalemate
    bool isStaleMate(Side) const;

    //does a promotion
    void promotion(Role);

};
#endif