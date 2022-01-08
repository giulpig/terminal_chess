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
#include <unordered_map>

using std::list;
using std::pair;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

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
    {'T', 'C', 'A', 'D', 'R', 'A', 'C', 'T'}};

constexpr char initial_colors[8][8] = {

    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
};

const static shared_ptr<Dummy> _oneDummyToRuleThemAll = std::make_shared<Dummy>();



//--------------------ChessBoard class----------------------

//add inclusion of other chessPieces
class ChessBoard
{

private:
    //---attributes---
    shared_ptr<ChessPiece> _chessBoard[SIZE][SIZE]; //actual board
    vector<shared_ptr<ChessPiece>> _black, _white;  //piece lists
    shared_ptr<ChessPiece> _toPromote = nullptr;    //pawn to promote
    shared_ptr<ChessPiece> _empassed = nullptr;     //last pawn that moves by two


    //counts moves since last capture or movement of a pawn
    int _finalCountUp = 0;
    //string representing the chessBoard and the number of times it has been repeated
    unordered_map<string, int> _repeatedBoards;
    //true if a single configuration has been repeated three times
    bool _threeRep = false;

    //----utility methods----
    static shared_ptr<ChessPiece> newPiece(int row, int col, Side, Role);
    static shared_ptr<ChessPiece> copyPiece(const shared_ptr<ChessPiece> &);
    static Side otherSide(Side);
    void addToPieceList(const shared_ptr<ChessPiece> &);
    void removeFromPieceList(const shared_ptr<ChessPiece> &);
    vector<shared_ptr<ChessPiece>>& getPieceList(Side);
    //forced moves (called from public move function)
    void doMove(const pair<int, int> &, const pair<int, int> &);
    void doEnpassant(const pair<int, int> &);
    void swapPieces(const pair<int, int> &, const pair<int, int> &);


public:
    //----constructors----
    ChessBoard();
    ChessBoard(const ChessBoard &); //copy
    ChessBoard(ChessBoard &&);      //move

    //----operators----
    ChessBoard &operator=(const ChessBoard &); //does a copy

    //----methods----
    //returns a string containing the board disposition
    std::string notToString() const;

    //returns the number of pices on the chessboard
    int nOfPieces(Side) const;

    //get position of the piece with index in the piece list of specific side (-1, -1 if invalid)
    pair<int, int> getPosition(int index, Side) const;

    //returns possible movements from a specific chesspiece,
    //the returned set is empty if there isn't any piece or if there are no possible moves
    set<std::pair<int, int>> getPossiblemovements(int row, int col);

    //returns possible movements for a specific chesspiece in the position of the list of pieces chosen by side,
    //the returned set is empty if there isn't any piece or if there are no possible moves
    set<std::pair<int, int>> getPossiblemovementsByIndex(int index, Side);

    //checks if a legal move is actually possible to do
    bool isPossibleMove(const pair<int, int> &, const pair<int, int> &, Side);

    //checks the move, calls doMove and returns the type of move that was done
    Moves move(const pair<int, int> &, const pair<int, int> &, Side);

    //does a promotion
    void promotion(Role);

    //argument 1: which side to check if the king is in check
    //argument 2: chessboard to use for the check, if not given it's the class member board
    //argument 3: needed if the board is a possible board and it signals where's the piece that was moved.
    //            used for check for possible moves
    bool isCheck(Side, const shared_ptr<ChessPiece>[8][8] = nullptr, pair<int, int> p = pair<int, int>{-1, -1}) const;
    //argument: which side to check if it has possible moves
    bool arePossibleMoves(Side);
    //argument: which side to check if it's in stalemate
    bool isStaleMate(Side);
};
#endif