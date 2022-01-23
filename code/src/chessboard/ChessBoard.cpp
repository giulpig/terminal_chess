//Giulio Codutti 2008795

#ifndef CHESSBOARD_CPP
#define CHESSBOARD_CPP

#include "ChessBoard.h"

/*
    Index of contents:
        > Section 1 - Utility methods---------------
            ~ move()
            ~ doMove()          [private]
            ~ isPossibleMove()
            ~ getPossiblemovements()

        > Section 2 - Constructors & operators------
            ~ ChessBoard()  [constructor]
            ~ ChessBoard()  [copy constructor]
            ~ ChessBoard()  [move constructor]
            ~ operator=()
*/


using std::shared_ptr;
using std::pair;


/*--------------------------- Section 1 - Utility methods ----------------------------------------*/

Move ChessBoard::move(const pair<int, int>& from, const pair<int, int>& to, Side side){

    shared_ptr<ChessPiece>& fromPiece = _chessBoard[from.first][from.second];    //reference just to not modify...
    shared_ptr<ChessPiece>& toPiece = _chessBoard[to.first][to.second];          //...internal shared_ptr counter
    Side opponent = otherSide(fromPiece->getSide());
    Move moveType = fromPiece->moveType(to.first, to.second, _chessBoard);
    shared_ptr<ChessPiece> newDoubleMoved = nullptr;
    bool enpassed = false;
    
    if(!isPossibleMove(from, to, side)){
        return Move::NaM;
    }

    //Check for special moves
    switch(moveType){

        case Move::castling:
            if(!doCastling(to))
                return Move::NaM;
            
            if(isStaleMate(opponent))
                return Move::staleMate;

            //checkMate check
            if(isCheck(opponent) && !hasPossibleMoves(opponent)){
                return Move::checkMate;
            }

            return Move::castling;

        case Move::promotion:
            _toPromote = _chessBoard[from.first][from.second];
        break;

        case Move::enpassant:
            doEnpassant(from, to);  //doEmpassant just removes the other pawn, the move is done in doMove
            enpassed = true;
        break;

        case Move::doublePawn:
            newDoubleMoved = fromPiece;
        break;

    }

    //actual board-changing method
    doMove(from, to);

    if(isStaleMate(opponent))
        return Move::staleMate;

    if(isCheck(opponent) && !hasPossibleMoves(opponent)){
        return Move::checkMate;
    }

    //overwrite previous double-moved pawn
    if(side == Side::black){
        if(_enpassedBlack != nullptr)
            std::dynamic_pointer_cast<Pawn>(_enpassedBlack)->cancelEnpassant();
        _enpassedBlack = newDoubleMoved;
    }
    else{
        if(_enpassedWhite != nullptr)
            std::dynamic_pointer_cast<Pawn>(_enpassedWhite)->cancelEnpassant();
        _enpassedWhite = newDoubleMoved;
    }

    if(enpassed)
        return Move::enpassant;

    if(_toPromote != nullptr)
        return Move::promotion;

    return Move::movement;
}



//Does the move by swapping pointers and updating all information
void ChessBoard::doMove(const pair<int, int>& from, const pair<int, int>& to){

    shared_ptr<ChessPiece>& fromPiece = _chessBoard[from.first][from.second];    //reference just to not modify...
    shared_ptr<ChessPiece>& toPiece = _chessBoard[to.first][to.second];          //...internal shared_ptr counter

    //if there's a capture or you move a pawn, you can't go back
    if(fromPiece->getRole() == Role::pawn || toPiece->getRole() != Role::dummy){        
        _finalCountUp = 0;
        _repeatedBoards.clear();
    }

    //update repeated board history
    std::string key = this->notToString();
    if(_repeatedBoards.find(key) != _repeatedBoards.end())
        _repeatedBoards[key]++;
    else
        _repeatedBoards[key] = 1;

    _finalCountUp++;   //repeatable moves counter

    //for staleMate by repeated moves (finalCountUp and threeRep are checked by isStaleMate)
    if(_repeatedBoards[key]>=3)
        _threeRep = true;


    //remove from piece list
    if(toPiece->getRole() != Role::dummy){
        removeFromPieceList(toPiece);
        _chessBoard[to.first][to.second] = oneDummyToRuleThemAll;
    }

    //update piece information
    fromPiece->setPosition(to.first, to.second);

    //actually swap pointers
    swapPieces(from, to);

}



//checks if a legal move is actually possible to do
bool ChessBoard::isPossibleMove(const pair<int, int> &from, const pair<int, int> &to, Side s){
    
    const shared_ptr<ChessPiece>& fromPiece = _chessBoard[from.first][from.second];    //reference just to not touch...
    const shared_ptr<ChessPiece>& toPiece = _chessBoard[to.first][to.second];          //...internal shared_ptr counter

    //You can't do castling under check
    if(fromPiece->moveType(to.first, to.second, _chessBoard) == Move::castling && isCheck(s))
        return false;

    //You can't move other player's pieces
    if(fromPiece->getSide() != s)
        return false;

    //You can't eat a king
    if(toPiece->getRole() == Role::king)
        return false;

    //Check for legal moves
    std::set<pair<int,int>> legalMoves = fromPiece->getLegalMoves(_chessBoard);
    if(legalMoves.find(to) == legalMoves.end())
        return false;

    //You can't check yourself...
    shared_ptr<ChessPiece> temp = _chessBoard[to.first][to.second];
    _chessBoard[to.first][to.second] = oneDummyToRuleThemAll;
    
    //...do-undo move strategy
    swapPieces(from, to);
    if(isCheck(s, _chessBoard, to)){
        swapPieces(from, to); //go back
        _chessBoard[to.first][to.second] = temp;
        return false;
    }
    swapPieces(from, to);   //go back
    _chessBoard[to.first][to.second] = temp;

    return true;
}



//returns possible movements from a specific chesspiece,
//the returned set is empty if there isn't any piece or if there are no possible moves
std::set<pair<int, int>> ChessBoard::getPossiblemovements(int row, int col){

    shared_ptr<ChessPiece> &piece = _chessBoard[row][col];

    std::set<pair<int, int>> ret = piece->getLegalMoves(_chessBoard);

    //delete moves that are not possible to do
    for(auto it = ret.begin(); it!=ret.end(); ){
        if(!isPossibleMove({row,col}, *it, piece->getSide()))
            it = ret.erase(it);
        else{
            ++it;
        }
    }

    return ret;
}




/*--------------------------- Section 2 - Constructors & operators --------------------------------------*/

//constructor
ChessBoard::ChessBoard(){

    //initialize chessboard and pieces lists based on constants
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            Side side = static_cast<Side>(initial_colors[i][j]);
            Role role = static_cast<Role>(initial_roles[i][j]);
            shared_ptr<ChessPiece> toAdd = newPiece(i, j, side, role);
            _chessBoard[i][j] = toAdd;
            if(toAdd->getRole() != Role::dummy)
                addToPieceList(toAdd);
        }
    }
}


//copy constructor
ChessBoard::ChessBoard(const ChessBoard& o){
    
    operator=(o); //call assignment operator
}


//move constructor
ChessBoard::ChessBoard(ChessBoard&& o){

    //copy matrix and invalidate old one
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            _chessBoard[i][j] = o._chessBoard[i][j];
            o._chessBoard[i][j] = nullptr;
        }
    }

    for(auto &i: o._black){      //copy pieces lists and clear old ones
        _black.push_back(i);
    }
    o._black.clear();

    for(auto &i: o._white){
        _white.push_back(i);
    }
    o._white.clear();
}


//assignment operator, does a copy of the chessPiece objects
ChessBoard& ChessBoard::operator=(const ChessBoard& o){
    
    //self-copy check
    if(this == &o)
        return *this;

    //copy local variables
    _toPromote = o._toPromote;
    _enpassedBlack = o._enpassedBlack;
    _enpassedWhite = o._enpassedWhite;
    _finalCountUp = o._finalCountUp;
    _repeatedBoards = o._repeatedBoards;
    _threeRep = o._threeRep;
    
    //initalize chessboard
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            _chessBoard[i][j] = oneDummyToRuleThemAll;
        }
    }

    //copy chessboard and lists
    for(const auto &i: o._black){
        _chessBoard[i->getRow()][i->getCol()] = copyPiece(i);
        _black.push_back(_chessBoard[i->getRow()][i->getCol()]);
    }
    for(const auto &i: o._white){
        _chessBoard[i->getRow()][i->getCol()] = copyPiece(i);
        _white.push_back(_chessBoard[i->getRow()][i->getCol()]);
    }

    return *this;
}


#endif