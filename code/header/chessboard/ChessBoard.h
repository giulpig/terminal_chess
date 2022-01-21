//Giulio Codutti 2008795

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


constexpr char initial_colors[8][8] = {     //1 for white, 0 for black and -1 for no side

    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    { 1,  1,  1,  1,  1,  1,  1,  1},
    { 1,  1,  1,  1,  1,  1,  1,  1},
};

const static std::shared_ptr<Dummy> oneDummyToRuleThemAll = std::make_shared<Dummy>();



//--------------------ChessBoard class----------------------

//add inclusion of other chessPieces
class ChessBoard
{

private:

//-----------attributes-----------

    std::shared_ptr<ChessPiece> _chessBoard[SIZE][SIZE];         //actual board

    std::vector<std::shared_ptr<ChessPiece>> _black, _white;     //piece lists

    std::shared_ptr<ChessPiece> _toPromote = nullptr;            //pawn to promote

    std::shared_ptr<ChessPiece> _enpassedWhite = nullptr;        //last pawns that moved by two
    std::shared_ptr<ChessPiece> _enpassedBlack = nullptr;

    //counts unrepeatable moves (moves since last capture or movement of a pawn)
    int _finalCountUp = 0;

    //string rapresentation of the chessBoard and number of times it has been repeated
    std::unordered_map<std::string, int> _repeatedBoards;

    //true if a single configuration has been repeated three times
    bool _threeRep = false;


//----------utility methods----------

    static std::shared_ptr<ChessPiece> newPiece(int row, int col, Side, Role); //can throw NoSideException
    static std::shared_ptr<ChessPiece> copyPiece(const std::shared_ptr<ChessPiece> &);
    static Side otherSide(Side);
    void addToPieceList(const std::shared_ptr<ChessPiece> &);
    void removeFromPieceList(const std::shared_ptr<ChessPiece> &);
    std::vector<std::shared_ptr<ChessPiece>> &getPieceList(Side); //can throw NoSideException

    //forced moves (called from public move function)
    void doMove(const std::pair<int, int> &, const std::pair<int, int> &);
    void doEnpassant(const std::pair<int, int> &);
    bool doCastling(const std::pair<int, int> &); //returns false if not legal castling
    void swapPieces(const std::pair<int, int> &, const std::pair<int, int> &);

public:
//--  --constructors----
    ChessBoard();
    ChessBoard(const ChessBoard &);          //copy
    ChessBoard(ChessBoard &&);               //move

//------operators-------
    ChessBoard &operator=(const ChessBoard &); //does a copy

//------methods---------
    //returns a string containing the board disposition
    std::string notToString() const;

    //returns the number of pices on the chessboard, can throw NoSideException
    int nOfPieces(Side) const;

    //get position of the piece with index in the piece list of specific side, can throw NoSideException
    std::pair<int, int> getPosition(int index, Side) const;

    //returns possible movements from a specific chesspiece,
    //the returned set is empty if there isn't any piece or if there are no possible moves
    std::set<std::pair<int, int>> getPossiblemovements(int row, int col);

    //returns possible movements for a specific chesspiece in the position of the list of pieces chosen by side,
    //the returned set is empty if there isn't any piece or if there are no possible moves
    std::set<std::pair<int, int>> getPossiblemovementsByIndex(int index, Side);

    //checks if a legal move is actually possible to do
    bool isPossibleMove(const std::pair<int, int> &, const std::pair<int, int> &, Side);

    //checks the move, calls doMove and returns the type of move that was done
    Moves move(const std::pair<int, int> &, const std::pair<int, int> &, Side);

    //does a promotion, returns true if checkmate, can throw InvalidPromotion
    Moves promotion(Role);

    //argument 1: which side to check if the king is in check
    //argument 2: chessboard to use for the check, if not given it's the class member board
    //argument 3: where's the piece that was eaten => ignored in the check
    bool isCheck(Side, const std::shared_ptr<ChessPiece>[8][8] = nullptr, std::pair<int, int> p = std::pair<int, int>{-1, -1}) const;
    
    //argument: which side to check if it has possible moves
    bool hasPossibleMoves(Side);
    
    //argument: which side to check the stalemate for
    bool isStaleMate(Side);
};
#endif